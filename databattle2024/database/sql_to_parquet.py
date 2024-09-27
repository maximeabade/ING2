import mariadb
import polars as pl

# Database connection details
host = "45.77.138.69"
user = "read_only"
password = "aqwzsx12"
database = "databattle"

def connect_to_db():
    """Connects to the MariaDB database."""
    try:
        conn = mariadb.connect(host=host, user=user, password=password, database=database)
        cursor = conn.cursor()
        return conn, cursor
    except mariadb.Error as err:
        print(f"Error connecting to database: {err}")
        return None, None

def fetch_table(cursor, table_name):
    try:
        df = pl.read_database(query=f"SELECT * FROM {table_name}", connection=cursor)
        return df
    except Exception as e:
        raise e

def fetch_table_uri(table_name):
    try:
        df = pl.read_database_uri(query=f"SELECT * FROM {table_name}", uri=f"jdbc:mariadb://{user}:{password}@{host}:3306/{database}")
        return df
    except Exception as e:
        raise e

def main():
    col_name = "Tables_in_" + database
    tables = pl.read_database(query="SHOW TABLES", connection=cursor)

    for table in tables[col_name]:
        print(table)
        try:
            df = fetch_table(cursor, table)
            df.write_parquet("data/" + table[3:] + ".parquet")
        except Exception as e:
            print(f"failed fetching table {table} : {str(e)}")
            # df = fetch_table_uri(table)
            # df.write_parquet("data/" + table + ".parquet")


if __name__ == "__main__":
    conn, cursor = connect_to_db()

    main()
