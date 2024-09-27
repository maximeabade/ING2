import os
import torch
import html
import polars as pl
from cleantext import clean
from codecarbon import track_emissions
from sentence_transformers import util
from sentence_transformers import SentenceTransformer
# local imports
from utils import fetch_sql_from_db, load_keyword_model, load_stopwords, logger, load_sentence_model
from config import solution_vector_embeddings_file, sentence_model_name

def fetch_solution_texts(cursor):
    """Fetches the relevant information from the sql database for solutions"""
    solutions_sql = """
    SELECT ts.numsolution, d1.indexdictionnaire,
           d1.traductiondictionnaire AS soltext,
           ts.codetechno,
           d2.traductiondictionnaire AS technotext,
           t.codeparenttechno,
           d3.traductiondictionnaire AS parenttechnotext,
           tt.codeparenttechno AS codegrandparenttechno,
           d4.traductiondictionnaire AS grandparenttechnotext
    FROM tblsolution ts
    LEFT JOIN tbltechno t ON ts.codetechno = t.numtechno
    LEFT JOIN tbltechno tt ON t.codeparenttechno = tt.numtechno
    LEFT JOIN tbldictionnaire d1 ON ts.numsolution = d1.codeappelobjet AND d1.typedictionnaire = 'sol' AND d1.codelangue = 2
    LEFT JOIN tbldictionnaire d2 ON ts.codetechno = d2.codeappelobjet AND d2.typedictionnaire = 'tec' AND d2.codelangue = 2 AND d2.indexdictionnaire = 1
    LEFT JOIN tbldictionnaire d3 ON t.codeparenttechno = d3.codeappelobjet AND d3.typedictionnaire = 'tec' AND d3.codelangue = 2 AND d3.indexdictionnaire = 1
    LEFT JOIN tbldictionnaire d4 ON tt.codeparenttechno = d4.codeappelobjet AND d4.typedictionnaire = 'tec' AND d4.codelangue = 2 AND d4.indexdictionnaire = 1
    """

    table = fetch_sql_from_db(cursor, solutions_sql, schema={'numsolution': pl.Int32, 'indexdictionnaire': pl.Int8, 'soltext': pl.Utf8, 'codetechno': pl.Int32, 'technotext': pl.Utf8,
                                                             'codeparenttechno': pl.Int32, 'parenttechnotext': pl.Utf8, 'codegrandparenttechno': pl.Int32, 'grandparenttechnotext': pl.Utf8})
    # remove html tags and filter null / small text
    table = table.with_columns(pl.col("soltext").map_elements(html.unescape))
    table = table.with_columns(pl.col("soltext").str.replace_all(r'<[^>]*>', '')).drop_nulls().filter(pl.col("soltext").str.len_chars() > 1)
    # table = table.with_columns(pl.col("soltext").str.replace_all(r"[^\w \[\],;:!?./&~()-_@]+", ''))
    # use a cleaning function to remove anomalities
    table = table.with_columns(pl.col("soltext").map_elements(clean)).sort("numsolution")
    return table

def create_embeddings(solutions_table, sentence_model):
    # 884 unique solutions
    solutions = solutions_table.with_columns((pl.col("soltext").map_elements(lambda r: '. '.join(r))).over("numsolution"))[["numsolution", "soltext"]].unique().sort("numsolution")

    techo_sentences = solutions_table.select(pl.concat_str([pl.col("technotext"), pl.col("parenttechnotext"), pl.col("grandparenttechnotext")], separator=". ").over("numsolution").alias("techno_sentence"), pl.col("numsolution")).unique().sort("numsolution")
    solutions = solutions.join(techo_sentences, on="numsolution")
    solutions = solutions.join(techo_sentences, on="numsolution").select(pl.concat_str([pl.col("soltext"), pl.col("techno_sentence")], separator=". "), pl.col("numsolution"))

    solutions_vectors = sentence_model.encode(solutions["soltext"].to_list(), convert_to_tensor=True)

    return solutions_vectors

@track_emissions()
def save_solutions_embeddings(file_name: str = ""):
    if file_name:
        solutions_table = pl.read_csv("solutions_table.csv")
    else:
        solutions_table = fetch_solution_texts()
        solutions_table.write_csv("solutions_table")

    sentence_model = load_sentence_model()

    solution_vectors = create_embeddings(solutions_table, sentence_model)

    if os.path.exists(solution_vector_embeddings_file):
        # logger.warn(f"Rewriting {solution_vector_embeddings_file}")
        print(f"Rewriting {solution_vector_embeddings_file}")

    torch.save(solution_vectors, solution_vector_embeddings_file)


if __name__ == "__main__":
    pass
    # save_solutions_embeddings("solutions_table.csv")
