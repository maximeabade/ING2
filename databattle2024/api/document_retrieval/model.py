import os
import torch
import numpy as np
import polars as pl
from codecarbon import track_emissions
from cleantext import clean
from sentence_transformers import util
# local imports
from utils import fetch_sql_from_db, load_sentence_model, load_keyword_model, load_stopwords, logger
from document_retrieval.create_solution_embeddings import fetch_solution_texts, create_embeddings

def create_technos(table):
    """Creates a list of technos and there sub-technos"""
    # Im not cleaning this. it works
    techno_list = ["Bâtiment",
                   "Cogénération",
                   "Déchets",
                   "Eau",
                   "Management (ISO 50 001)",
                   "Nouvelles énergies",
                   "Procédés",
                   "Technologies énergétiques",
                   "Utilités"]

    technos = {}
    for techno, tbl in table.group_by(["grandparenttechnotext"]):
        if techno[0] is None:
            for techno, tbl2 in tbl.group_by(["parenttechnotext"]):
                if techno[0] is None or techno[0] not in techno_list:
                    continue
                sub_technos = tbl2["technotext"].unique().to_list()
                if techno[0] in technos:
                    technos[techno[0]] = set(list(technos[techno[0]]) + sub_technos)
                else:
                    technos[techno[0]] = set(sub_technos)
        else:
            if techno[0] not in techno_list:
                continue
            sub_technos = tbl["parenttechnotext"].unique().to_list()
            if techno[0] in technos:
                technos[techno[0]] = set(list(technos[techno[0]]) + sub_technos)
            else:
                technos[techno[0]] = set(sub_technos)

    tech_sentences = []
    for key, tech in technos.items():
        tech_sentences.append(key + ". " + ". ".join(list(tech)) + ".")

    return tech_sentences

class RetrievalModel:

    def __init__(self, cursor=None, techno_file: str = "cache/technos.txt", techno_embeddings_file: str = "cache/techno_embeddings.pt", solution_file: str = "cache/solutions.csv", solutions_embeddings_file: str = "cache/solutions_vectors.pt"):
        # load models
        self.sentence_model = load_sentence_model()
        self.keyword_model = load_keyword_model(self.sentence_model)
        self.stopwords = load_stopwords()

        # load solutions
        if os.path.exists(solution_file):
            self.solutions_techno_table = pl.read_csv(solution_file)
        elif cursor is not None:
            logger.warn("Did not find saved solutions, re-fetching")
            self.solutions_techno_table = fetch_solution_texts(cursor)
            self.solutions_techno_table.write_csv(solution_file)
        else:
            raise NotImplementedError("RetrievalModel solution file not defined or needs connection to sql db")

        self.solutions_table = self.solutions_techno_table.with_columns((pl.col("soltext").map_elements(lambda r: '. '.join(r))).over("numsolution"))[["numsolution", "soltext"]].unique().sort("numsolution")

        # load solution embeddings
        if os.path.exists(solutions_embeddings_file):
            self.solutions_embeddings = torch.load(solutions_embeddings_file)
        else:
            logger.warn(f"RetrievalModel    solution embeddings file not defined {solutions_embeddings_file} - recalculating embeddings")
            self.solutions_embeddings = create_embeddings(self.solutions_techno_table, self.sentence_model)
            torch.save(self.solutions_embeddings, solutions_embeddings_file)

        # load technos
        if os.path.exists(techno_file):
            with open(techno_file, "r") as f:
                self.techno_texts = f.read().split('\n')
        elif cursor is not None:
            logger.warn("Did not find saved technos, re-fetching")
            self.techno_texts = create_technos(self.solutions_techno_table)
            with open(techno_file, "w") as f:
                f.write('\n'.join(self.techno_texts))
        else:
            raise NotImplementedError("RetrievalModel techno file not defined or needs connection to sql db")

        # load techno embeddings
        if os.path.exists(techno_embeddings_file):
            self.techno_embeddings = torch.load(techno_embeddings_file)
        else:
            logger.warn(f"RetrievalModel    techno embeddings file not defined {techno_embeddings_file} - recalculating embeddings")
            self.techno_embeddings = torch.tensor(self.sentence_model.encode(self.techno_texts))
            torch.save(self.techno_embeddings, techno_embeddings_file)

    def find_similar_queries(self, query: str = "", k: int = 1):
        logger.info(f"Querying {query}")
        # encode the query
        query_embeddings = self.sentence_model.encode(query, convert_to_tensor=True)

        if False:  # calculate the keywords to match with relevant technologies
            # extract the keywords
            keywords = self.keyword_model.extract_keywords(query, keyphrase_ngram_range=(1, 3), stop_words=self.stopwords)
            keyword_text = '. '.join([kw[0] for kw in keywords if kw[1] > 0.3])
            # encode the keywords
            keyword_embeddings = self.sentence_model.encode(keyword_text, convert_to_tensor=True)

            # calculate similarities with tech topics
            similarity_query = torch.nn.functional.cosine_similarity(self.techno_embeddings, keyword_embeddings.unsqueeze(0))
            similarity_keywords = torch.nn.functional.cosine_similarity(self.techno_embeddings, query_embeddings.unsqueeze(0))
            tech1_idxs = torch.topk(similarity_query, k=2)[1].tolist()
            tech2_idxs = torch.topk(similarity_keywords, k=2)[1].tolist()
            tech_idxs = list(set(tech1_idxs + tech2_idxs))

            logger.info(tech_idxs)

            # fetch relevant techno name
            rel_techno_name = []
            for tidx in tech_idxs:
                rel_techno_name.append(self.techno_texts[tidx].split(". ")[0])

            logger.info(f"Relevant technos:  {':'.join(rel_techno_name)}")

            # filter solutions to only in from the techno
            solutions_numbers = self.solutions_techno_table.filter(pl.col("grandparenttechnotext").is_in(rel_techno_name) | pl.col("parenttechnotext").is_in(rel_techno_name))["numsolution"].unique()

            solutions_index_mask = np.argwhere(np.isin(self.solutions_table["numsolution"].to_numpy(), solutions_numbers).astype(int)).ravel()

            solutions_embeddings = self.solutions_embeddings[solutions_index_mask]
        else:
            solutions_index_mask = list(range(len(self.solutions_embeddings)))
            solutions_embeddings = self.solutions_embeddings  # [solutions_index_mask]

        cos_scores = util.cos_sim(query_embeddings, solutions_embeddings)[0]
        top_k = torch.topk(cos_scores, k=k)

        relevant_solutions = []
        for score, idx in zip(top_k[0], top_k[1]):
            index = int(solutions_index_mask[int(idx)])
            sol = self.solutions_table[index]
            solution_number = sol["numsolution"][0]
            solution_text, *solution_desc = sol["soltext"][0].split(". ")
            logger.info(f"{solution_number} {solution_text} Score: {score:.2f}")
            relevant_solutions.append((solution_number, solution_text, solution_desc, score))

        return relevant_solutions

    @track_emissions()
    def testing(self):
        print(self.techno_texts)
        queries = ["Comment faire pour réduire la consommation de mon compresseur d'air comprimé ?",
                   "J'aimerais avoir une régulation optimisée de mon groupe froid",
                   "C'est quoi la HP flottante ?",
                   "Je voudrais dimensionner un panneau solaire.",
                   "Quel gain pour un variateur de vitesse ?",
                   "Quelles sont les meilleures solutions pour l'agro-alimentaire ?"]

        for query in queries:
            self.find_similar_queries(query, k=5)


if __name__ == "__main__":
    retrieval_model = RetrievalModel(solution_file="solutions_table.csv", solutions_embeddings_file="solutions_vectors.pt")
    retrieval_model.testing()
