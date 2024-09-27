import polars as pl
import os
import html
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from typing import List, Annotated, Optional
from pydantic import BaseModel
from codecarbon import OfflineEmissionsTracker
# local imports
from document_retrieval import RetrievalModel
from cases import CasesModel
from utils import connect_to_db, fetch_sql_from_db


# check if cache dir is created
if not os.path.exists("cache/"):
    os.mkdir("cache")

# load prequists
# this is slow, find way to speedup
conn, cursor = connect_to_db()
# cursor needs to reconnect after a certain while
retrieval_model = RetrievalModel(cursor=cursor)
cases_model = CasesModel(cursor=cursor)
tracker = OfflineEmissionsTracker(country_iso_code="FRA")

class Solution(BaseModel):
    number: int
    text: str
    desc: list[str]
    score: float


api = FastAPI()

api.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@api.get("/")
def root():
    return {"hello: world"}

@api.get("/refreshembeddings")
def refresh_embeddings():
    global retrieval_model, cases_model, tracker
    # delete .pt files in cache if they exist (one by one)
    if os.path.exists("cache/cases_vectors.pt"):
        os.remove("cache/cases_vectors.pt")
    if os.path.exists("cache/solutions_vectors.pt"):
        os.remove("cache/solutions_vectors.pt")
    if os.path.exists("cache/techno_embeddings.pt") and False:
        os.remove("cache/techno_embeddings.pt")
    tracker.start()
    retrieval_model = RetrievalModel(cursor=cursor)
    cases_model = CasesModel(cursor=cursor)
    tracker.stop()
    df = pl.read_csv("emissions.csv").row(-1, named=True)
    res = {"duration": df["duration"],
           "emissions": df["emissions"],
           "energy_consumed": df["energy_consumed"]
           }
    return res

@api.get("/solution/{codesolution}")
def fetch_solution_from_db(codesolution: int):
    sql = f"""
    SELECT t.codeappelobjet AS codesolution, t.indexdictionnaire AS idx, t.traductiondictionnaire AS text, t2.traductiondictionnaire AS texttechno
    FROM tbldictionnaire AS t
    LEFT JOIN tblsolution AS ts ON ts.numsolution = t.codeappelobjet
    LEFT JOIN tbldictionnaire AS t2 ON ts.codetechno = t2.codeappelobjet AND t2.codelangue = 2 AND t2.typedictionnaire = "tec" AND t2.indexdictionnaire = 1
    WHERE t.codeappelobjet = {codesolution} AND t.codelangue = 2 AND t.typedictionnaire = "sol"
    """
    solution_table = fetch_sql_from_db(cursor, sql)
    if not solution_table.is_empty():
        solution_table = solution_table.with_columns(pl.col("text").map_elements(html.unescape, skip_nulls=True))
    return solution_table.to_dicts()

# "textpays", "textregion", "textpublic", "textsecteur", "texttravaux", "texttechno", "textreseau"
@api.get("/pay")
def fetch_pays():
    name = "pay"
    df = fetch_sql_from_db(cursor, f"SELECT DISTINCT t.codeappelobjet AS codepay, t.traductiondictionnairecategories AS {name} FROM tbldictionnairecategories AS t WHERE t.typedictionnairecategories = '{name}' AND t.codelangue = 2")
    return df.to_dicts()

@api.get("/reg")
def fetch_regs(codepay: Optional[int] = None):
    if codepay is None:
        name = "reg"
        sql = f"SELECT DISTINCT t.codeappelobjet AS codereg, t.traductiondictionnairecategories AS {name} FROM tbldictionnairecategories AS t WHERE t.typedictionnairecategories = '{name}' AND t.codelangue = 2"
    else:
        sql = f"""
        SELECT DISTINCT r.codepays AS codepays, t.codeappelobjet AS codereg, t.traductiondictionnairecategories AS reg
        FROM tbldictionnairecategories AS t
        LEFT JOIN tblregion AS r ON r.numregion = t.codeappelobjet
        WHERE t.typedictionnairecategories = 'reg' AND t.codelangue = 2 AND r.codepays = {codepay}"""
    df = fetch_sql_from_db(cursor, sql)
    return df.to_dicts()

@api.get("/pub")
def fetch_pub():
    name = "pub"
    df = fetch_sql_from_db(cursor, f"SELECT DISTINCT t.codeappelobjet AS code{name}, t.traductiondictionnairecategories AS {name} FROM tbldictionnairecategories AS t WHERE t.typedictionnairecategories = '{name}' AND t.codelangue = 2")
    return df.to_dicts()

@api.get("/tra")
def fetch_tra():
    name = "tra"
    df = fetch_sql_from_db(cursor, f"SELECT DISTINCT t.codeappelobjet AS code{name}, t.traductiondictionnairecategories AS {name} FROM tbldictionnairecategories AS t WHERE t.typedictionnairecategories = '{name}' AND t.codelangue = 2")
    return df.to_dicts()

@api.get("/res")
def fetch_res():
    name = "res"
    df = fetch_sql_from_db(cursor, f"SELECT DISTINCT t.codeappelobjet AS code{name}, t.traductiondictionnairecategories AS {name} FROM tbldictionnairecategories AS t WHERE t.typedictionnairecategories = '{name}' AND t.codelangue = 2")
    return df.to_dicts()

@api.get("/tec")
def fetch_tec():
    sql = "SELECT DISTINCT t.codeappelobjet AS codetechno, t.traductiondictionnaire AS tec FROM tbldictionnaire AS t WHERE t.typedictionnaire = 'tec' AND t.codelangue = 2 AND t.indexdictionnaire = 1"
    df = fetch_sql_from_db(cursor, sql)
    return df.to_dicts()

@api.get("/sec")
def fetch_sec():
    sql = "SELECT DISTINCT t.codeappelobjet AS codesec, t.traductiondictionnaire AS sec FROM tbldictionnaire AS t WHERE t.typedictionnaire = 'sec' AND t.codelangue = 2 AND t.indexdictionnaire = 1"
    df = fetch_sql_from_db(cursor, sql)
    return df.to_dicts()

@api.get("/cases")
def get_cases(codesolution: Optional[int] = None, query: str = ""):
    # Validate the presence of the query parameter
    if not query:
        return {"error": "Missing query parameter"}

    cases = cases_model.find_similar_cases(query=query, codesolution=codesolution)

    return cases.to_dicts()

@api.get('/get_solution', response_model=List[Solution])
def get_solution(query: str = "", k: int = 1) -> List[Solution]:
    # Validate the presence of the query parameter
    if not query:
        return {"error": "Missing query parameter"}

    # Find similar solutions based on the user query
    solutions = retrieval_model.find_similar_queries(query=query, k=k)

    # Convert retrieved solutions to the expected response format
    response_solutions = []
    for solution_number, solution_text, solution_desc, score in solutions:
        response_solutions.append(Solution(number=solution_number, text=solution_text, desc=solution_desc, score=score))

    return response_solutions
