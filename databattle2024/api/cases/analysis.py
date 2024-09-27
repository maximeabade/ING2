import os
import torch
import numpy as np
import polars as pl
from sentence_transformers import util
# local imports
from utils import fetch_sql_from_db, load_sentence_model, convert, logger, convert_energy


def fetch_cases_from_db(cursor, numsolution: int = None):
    sql_query = """
    SELECT tg.codesolution AS codesolution, tg.coderex AS coderex,
           tg.gainfinanciergainrex AS gainfinancier,
           tg.codemonnaiegainrex AS codegainmonnaie, tm.shortmonnaie AS textgainmonnaie,
           tg.codeperiodeeconomie AS codeperiodeeconomie, tdc_per3.traductiondictionnairecategories AS textperiodeeconomie,
           tg.trireelgainrex AS tri,
           tc.reelcoutrex AS coutfinancier,
           tc.codemonnaiecoutrex AS codecoutmonnaie, tm2.shortmonnaie AS textcoutmonnaie,
           tc.codeunitecoutrex AS codeunitcout, tdc_per.traductiondictionnairecategories AS textunitcoutenergie,
           tg.energiegainrex AS gainenergie,
           tg.uniteenergiegainrex AS codeunitenergie, tdc_uni.traductiondictionnairecategories AS textunitenergie,
           tg.codeperiodeenergie AS codeperiodeenergie, tdc_per2.traductiondictionnairecategories AS textperiodeenergie,
           tr.codepublic, tdc_pub.traductiondictionnairecategories AS textpublic,
           tr.codeTechno1, td_tec1.traductiondictionnaire AS texttechno1,
           tr.codeTechno2, td_tec2.traductiondictionnaire AS texttechno2,
           tr.codeTechno3, td_tec3.traductiondictionnaire AS texttechno3,
           tr.codetravaux, tdc_tra.traductiondictionnairecategories AS texttravaux,
           tr.codereseau, tdc_res.traductiondictionnairecategories AS textreseau,
           trg.codepays, tdc_pay.traductiondictionnairecategories AS textpays,
           trf.coderegion, tdc_reg.traductiondictionnairecategories AS textregion,
           trf.villereference AS ville,
           trf.codesecteur, td_sec.traductiondictionnaire AS textsecteur,
           tr.gesrex AS gesrex,
           tg.gesgainrex AS ges
    FROM tblgainrex AS tg
    LEFT JOIN tblcoutrex as tc ON tc.codesolution = tg.codesolution AND tc.coderex = tg.coderex
    LEFT JOIN tblrex AS tr ON tr.numrex = tg.coderex
    LEFT JOIN tblmonnaie AS tm ON tm.nummonnaie = tg.codemonnaiegainrex
    LEFT JOIN tblmonnaie AS tm2 ON tm2.nummonnaie = tc.codemonnaiecoutrex
    LEFT JOIN tbldictionnairecategories AS tdc_per ON tdc_per.codeappelobjet = tc.codeunitecoutrex AND tdc_per.typedictionnairecategories = "per" AND tdc_per.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_uni ON tdc_uni.codeappelobjet = tg.uniteenergiegainrex AND tdc_uni.typedictionnairecategories = "uni" AND tdc_uni.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_per2 ON tdc_per2.codeappelobjet = tg.codeperiodeenergie AND tdc_per2.typedictionnairecategories = "per" AND tdc_per2.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_per3 ON tdc_per3.codeappelobjet = tg.codeperiodeeconomie AND tdc_per3.typedictionnairecategories = "per" AND tdc_per3.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_pub ON tdc_pub.codeappelobjet = tr.codepublic AND tdc_pub.typedictionnairecategories = "pub" AND tdc_pub.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_tra ON tdc_tra.codeappelobjet = tr.codetravaux AND tdc_tra.typedictionnairecategories = "tra" AND tdc_tra.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_res ON tdc_res.codeappelobjet = tr.codereseau AND tdc_res.typedictionnairecategories = "res" AND tdc_res.codelangue = 2
    LEFT JOIN tbldictionnaire AS td_tec1 ON td_tec1.codeappelobjet = tr.codeTechno1 AND td_tec1.typedictionnaire = "tec" AND td_tec1.codelangue = 2 AND td_tec1.indexdictionnaire = 1
    LEFT JOIN tbldictionnaire AS td_tec2 ON td_tec2.codeappelobjet = tr.codeTechno2 AND td_tec2.typedictionnaire = "tec" AND td_tec2.codelangue = 2 AND td_tec2.indexdictionnaire = 1
    LEFT JOIN tbldictionnaire AS td_tec3 ON td_tec3.codeappelobjet = tr.codeTechno3 AND td_tec3.typedictionnaire = "tec" AND td_tec3.codelangue = 2 AND td_tec3.indexdictionnaire = 1
    LEFT JOIN tblreference AS trf ON tr.codereference = trf.numreference
    LEFT JOIN tblregion AS trg ON trf.coderegion = trg.numregion
    LEFT JOIN tbldictionnairecategories AS tdc_pay ON tdc_pay.codeappelobjet = trg.codepays AND tdc_pay.typedictionnairecategories = "pay" AND tdc_pay.codelangue = 2
    LEFT JOIN tbldictionnairecategories AS tdc_reg ON tdc_reg.codeappelobjet = trf.coderegion AND tdc_reg.typedictionnairecategories = "reg" AND tdc_reg.codelangue = 2
    LEFT JOIN tbldictionnaire AS td_sec ON td_sec.codeappelobjet = trf.codesecteur AND td_sec.typedictionnaire = "sec" AND td_sec.codelangue = 2 AND td_sec.indexdictionnaire = 1
    """
    schema = {'codesolution': pl.Int64,
              'coderex': pl.Int64,
              'gainfinancier': pl.Float64,
              'codegainmonnaie': pl.Int64,
              'textgainmonnaie': pl.Utf8,
              'codeperiodeeconomie': pl.Int64,
              'textperiodeeconomie': pl.Utf8,
              'tri': pl.Float64,
              'coutfinancier': pl.Float64,
              'codecoutmonnaie': pl.Int64,
              'textcoutmonnaie': pl.Utf8,
              'codeunitcout': pl.Int64,
              'textunitcoutenergie': pl.Utf8,
              'gainenergie': pl.Float64,
              'codeunitenergie': pl.Int64,
              'textunitenergie': pl.Utf8,
              'codeperiodeenergie': pl.Int64,
              'textperiodeenergie': pl.Utf8,
              'codepublic': pl.Int64,
              'textpublic': pl.Utf8,
              'codeTechno1': pl.Int64,
              'texttechno1': pl.Utf8,
              'codeTechno2': pl.Int64,
              'texttechno2': pl.Utf8,
              'codeTechno3': pl.Int64,
              'texttechno3': pl.Utf8,
              'codetravaux': pl.Int64,
              'texttravaux': pl.Utf8,
              'codereseau': pl.Int64,
              'textreseau': pl.Utf8,
              'codepays': pl.Int64,
              'textpays': pl.Utf8,
              'coderegion': pl.Int64,
              'textregion': pl.Utf8,
              'ville': pl.Utf8,
              'codesecteur': pl.Int64,
              'textsecteur': pl.Utf8,
              'gesrex': pl.Float64,
              'ges': pl.Float64
              }
    if numsolution is not None:
        sql_query += f"WHERE tg.codesolution = {numsolution}"

    table = fetch_sql_from_db(cursor, sql_query, schema).unique()

    return table

class CasesModel:

    def __init__(self, cursor=None, numsolution: int = None, cases_file: str = "cache/cases.csv", cases_embeddings_file: str = "cache/cases_vectors.pt"):
        self.sentence_model = load_sentence_model()

        if os.path.exists(cases_file):
            self.cases = pl.read_csv(cases_file)
        elif cursor is not None:
            logger.warn("Did not find saved cases, re-fetching")
            self.cases = fetch_cases_from_db(cursor, numsolution)
            self.cases.write_csv(cases_file)
        else:
            raise NotImplementedError("cases_file not defined and need connection to sql db")

        # convert to EUR
        # self.cases = self.cases.with_columns(pl.struct(["gainfinancier", "textgainmonnaie"]).map_elements(lambda x: convert(x["gainfinancier"], x["textgainmonnaie"], "EUR")).alias("gainfinancierEUR"))
        # self.cases = self.cases.with_columns(pl.struct(["coutfinancier", "textgainmonnaie"]).map_elements(lambda x: convert(x["coutfinancier"], x["textgainmonnaie"], "EUR")).alias("coutfinancierEUR"))

        # "textsecteur", "textpays", "textregion", "texttechno1", "texttechno2", "texttechno3", "texttravaux", "textreseau", "textpublic"

        self.embedding_text = self.cases[["textsecteur", "textpays", "textregion", "textpublic", "texttechno1", "texttechno2", "texttechno3"]].fill_null("")

        self.cases_sentences = ['. '.join(word) for word in self.embedding_text.to_numpy()]

        if os.path.exists(cases_embeddings_file):
            self.cases_embeddings = torch.load(cases_embeddings_file)
        else:
            logger.warn(f"CasesModel cases embeddings not defined {cases_embeddings_file} - recalculating embeddings")
            self.cases_embeddings = self.sentence_model.encode(self.cases_sentences, convert_to_tensor=True)
            torch.save(self.cases_embeddings, cases_embeddings_file)

    def find_similar_cases(self, query: str = "", k: int = None, codesolution: int = None):
        logger.info(f"Querying Case: {query}")

        # encode the query
        query_embeddings = self.sentence_model.encode(query, convert_to_tensor=True)

        # relevant cases:
        if codesolution is not None:
            indexes = np.argwhere(self.cases["codesolution"] == codesolution).ravel()
            relevant_embeddings = self.cases_embeddings[indexes.tolist()]
        else:
            indexes = list(range(len(self.cases_embeddings)))
            relevant_embeddings = self.cases_embeddings

        if len(indexes) > 0:
            # similarity
            # similarity_query = torch.nn.functional.cosine_similarity(relevant_embeddings, query_embeddings.unsqueeze(0))
            logger.info(relevant_embeddings.shape)
            cos_scores = util.cos_sim(query_embeddings, relevant_embeddings)[0]
            if k is None:
                top_k = torch.topk(cos_scores, k=len(cos_scores))
            else:
                top_k = torch.topk(cos_scores, k=k)

            indexes = indexes[top_k[1].tolist()]
            relevant_cases = self.cases[indexes.tolist()]

            # convert to EUR
            relevant_cases = relevant_cases.with_columns(pl.struct(["gainfinancier", "textgainmonnaie"]).map_elements(lambda x: convert(x["gainfinancier"], x["textgainmonnaie"], "EUR"), skip_nulls=False).alias("gainfinancierEUR"))
            relevant_cases = relevant_cases.with_columns(pl.struct(["coutfinancier", "textgainmonnaie"]).map_elements(lambda x: convert(x["coutfinancier"], x["textgainmonnaie"], "EUR"), skip_nulls=False).alias("coutfinancierEUR"))

            # convert energy to kWh
            relevant_cases = relevant_cases.with_columns(pl.struct(["gainenergie", "textunitenergie"]).map_elements(lambda x: convert_energy(x["gainenergie"], x["textunitenergie"], "kWh"), skip_nulls=False).alias("gainenergie_kWh"))

            relevant_cases = relevant_cases.with_columns(pl.Series(name="score", values=top_k[0].tolist()))

            return relevant_cases
        else:
            return pl.DataFrame(schema_overrides=self.cases.schema)

    def testing(self):
        logger.info("Starting case retrival tests")
        queries = ["Boissons. France. Aquitaine. Froid"]

        for query in queries:
            self.find_similar_cases(query, k=5)


if __name__ == "__main__":
    model = CasesModel()
    model.testing()
