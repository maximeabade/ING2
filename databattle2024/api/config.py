# multilingual sentance transformer
# sentence_model_name = "distiluse-base-multilingual-cased-v1"
sentence_model_name = "sentence-transformers/multi-qa-MiniLM-L6-cos-v1"  # best found so far
# sentence_model_name = "sentence-transformers/multi-qa-mpnet-base-cos-v1"
# sentence_model_name = "dangvantuan/sentence-camembert-base"
# sentence_model_name = "CATIE-AQ/QAmembert"
# sentence_model_name = "microsoft/mpnet-base"


bert_model_name = "distilbert-base-uncased"

# a french bert model
camembert_model_name = "almanach/camembert-base"


# Database connection details
db_host = "45.77.138.69"
db_user = "read_only"
db_password = "aqwzsx12"
db_database = "databattle"

# stopword file
stopword_file = "document_retrieval/stopwords-fr.txt"

solution_vector_embeddings_file = "document_retrieval/solutions_vectors.pt"
