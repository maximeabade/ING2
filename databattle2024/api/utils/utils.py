import os
import sys
import mariadb
import logging
import polars as pl
from sentence_transformers import SentenceTransformer
from keybert import KeyBERT
from currency_converter import CurrencyConverter
# local import
from config import *

converter = CurrencyConverter()
logging.basicConfig(level=logging.INFO, format='%(asctime)s %(levelname)-8s %(message)s', datefmt='%Y-%m-%d %H:%M:%S', handlers=[logging.StreamHandler(sys.stdout)])
logger = logging.getLogger("document-retrival")

def connect_to_db():
    """Connects to the MariaDB database."""
    try:
        logging.info("Connecting to sql database")
        conn = mariadb.connect(host=db_host, user=db_user, password=db_password, database=db_database)
        cursor = conn.cursor()
        logging.info("Connected to sql database")
        return conn, cursor
    except mariadb.Error as e:
        logging.error(f"Error connecting to database: {str(e)}")
        # print(f"Error connecting to database: {e}")
        return None, None

def fetch_sql_from_db(cursor, sql, schema: dict = None):
    try:
        if schema is None:
            df = pl.read_database(query=sql, connection=cursor)
        else:
            df = pl.read_database(query=sql, connection=cursor, schema_overrides=schema)
        return df
    except Exception as e:
        logging.error(f"Error fetching sql: {str(e)}")
        raise e

def fetch_table_from_db(cursor, table_name):
    try:
        df = pl.read_database(query=f"SELECT * FROM {table_name}", connection=cursor)
        return df
    except Exception as e:
        logging.error(f"Error fetching table: {str(e)}")
        raise e

def load_sentence_model():
    """Loads the sentence model defined in config.py """
    try:
        sentence_model = SentenceTransformer(sentence_model_name)
        return sentence_model
    except Exception as e:
        logging.error(f"Error loading sentence model: {str(e)}")
        raise e

def load_keyword_model(sentence_model):
    """Loads the KeyBERT model from the sentence model"""
    try:
        keyword_model = KeyBERT(sentence_model)
        return keyword_model
    except Exception as e:
        logging.error(f"Error loading keyword model: {str(e)}")
        raise e

def load_stopwords():
    """Loads the stopwords from the file in config"""
    try:
        stopwords = open(stopword_file).read().split()
    except Exception as e:
        logging.error(f"Error loading the stopwords: {str(e)}")
        raise e

def convert(x, from_currency, to_currency):
    # currencies last updated on 24-03-24
    if x is None or from_currency is None or to_currency is None:
        return x
    if from_currency == "FRF":
        rate = {"EUR": 0.15247,
                "USD": 0.16477}
        if to_currency not in rate.keys():
            raise KeyError(f"Currency not supported: {to_currency}")
        return x * rate[to_currency]
    if from_currency == "LACS":
        rate = {"EUR": 0.01100,
                "USD": 0.01190}
        if to_currency not in rate.keys():
            raise KeyError(f"Currency not supported: {to_currency}")
        return x * rate[to_currency]
    else:
        return converter.convert(x, from_currency, to_currency)

def convert_energy(value: float, from_unit: str, to_unit: str = "Wh") -> float:
    """Converts an energy value between different units.

    Args:
            value: The value to convert.
            from_unit: The unit of the input value (e.g., "Wh", "J", "MJ").
            to_unit: The unit to convert the value to (default: "kWh").

    Returns:
            The converted value in kWh, or None if the conversion is not possible.
    """

    conversion_factors = {
      "kWh": 1e3,                   # Already in kWh
      "MWh": 1e6,                 # Megawatt hour to kWh
      "GWh": 1e9,             # Gigawatt hour to kWh
      "GJ": 277778,                # Gigajoule to kWh
      "Btu": 0.00029307107,             # Million British thermal unit to kWh
      "MMBtu": 0.29307107,             # Million British thermal unit to kWh
      "therms": 0.00293001,             # Therm (US) to kWh
      # Handle potential typo (assuming kWh cumulative)
      "kWh cumac": 1e3,
    }

    if from_unit not in conversion_factors:
        return None    # Conversion not supported

    return value * conversion_factors[from_unit]


if __name__ == "__main__":
    logger.info("Testing connections and loading models")
    conn, cursor = connect_to_db()

    fetch_sql_from_db(cursor, "select * from tbltechno")

    fetch_table_from_db(cursor, "tbltechno")

    sentence_model = load_sentence_model()

    load_keyword_model(sentence_model)

    stopwords = load_stopwords()
