import time
import streamlit as st  # Bibliothèque Streamlit pour la création d'applications web
import math
import numpy as np
import requests         # Bibliothèque requests pour effectuer des requêtes HTTP
import polars as pl     # Bibliothèque Polars pour le traitement des données
import pandas as pd     # Bibliothèque pandas pour le traitement des données
import streamlit.components.v1 as components  # Bibliothèque Streamlit pour l'intégration de composants web
import seaborn as sns
import matplotlib.pyplot as plt

def set_query_session(query: str):
    st.session_state.query = query

def set_codesolution_session(codesolution: int):
    st.session_state.codesolution = codesolution

def reset_session(key: str = None):
    if key is None:
        for key in st.session_state.keys():
            del st.session_state[key]
    elif key in st.session_state:
        del st.session_state[key]

def apply_score_threshold(score: float) -> str:
    """Applique un seuil aux scores pour les classer en catégories

    Args:
        score (float): Le score de la solution

    Returns:
        str: La catégorie du score
    """
    categorie = "Confiance élevée"
    if score < 0.33:
        categorie = "None"
    elif score < 0.42:
        categorie = "Confiance faible"
    elif score < 0.5:
        categorie = "Confiance moyenne"
    return categorie

@st.cache_data
def fetch_cases_count(codesolution: int):
    res = requests.get("http://api:8000/cases", params={'query': "count", 'codesolution': codesolution})
    res.raise_for_status()
    data = res.json()
    return len(data)

@st.cache_data(experimental_allow_widgets=True)  # Décorateur pour mettre en cache les données et éviter des recalculs inutiles
def fetch_query(requete_utilisateur):
    """Requête l'API pour obtenir des solutions à partir de la requête utilisateur

    Args:
        requete_utilisateur (_type_): La requête de l'utilisateur pour laquelle les solutions sont recherchées
    """
    api_url = "http://api:8000/get_solution/"  # URL de l'API à laquelle les requêtes sont envoyées

    try:
        response = requests.get(api_url, params={"query": requete_utilisateur, "k": 5})  # Envoie une requête GET à l'API
        response.raise_for_status()  # Vérifie que la requête s'est bien passée, sinon lève une exception
        data = response.json()       # Convertit la réponse en JSON
        df = pd.DataFrame(data)      # Convertit les données en DataFrame pandas
        df["threshold"] = df["score"].apply(apply_score_threshold)  # Ajoute une colonne pour les seuils
        # st.dataframe(df)             # Affiche le DataFrame dans l'interface utilisateur

        if "error" in data:          # Si une erreur est renvoyée par l'API
            st.error(data["error"])  # Affiche l'erreur dans l'interface utilisateur
        else:
            st.subheader("Voici quelques solutions qui pourraient vous aider :")

        # Début de la boucle pour traiter chaque solution dans le DataFrame
        for i, solution in df.iterrows():
            # Récupère des informations supplémentaires pour la solution actuelle
            info = fetch_solution_information(solution['number'])
            # Convertit les informations récupérées en DataFrame pour un traitement facile
            df = pl.from_dicts(info)
            # st.dataframe(df)

            # Vérifie si des informations supplémentaires ont été trouvées
            if len(info) > 0:
                # Si oui, extrait le texte associé à l'indice 1
                solution_text = df.filter(pl.col("idx") == 1)["text"][0]
                solution_techno = df.filter(pl.col("idx") == 1)["texttechno"][0]
            else:
                # Sinon, utilise un texte par défaut indiquant l'absence de solution
                solution_text = "Solution non disponible"
                solution_techno = ""

            # Vérifie si une description est disponible dans les informations récupérées
            if 2 in df["idx"]:
                # Si oui, extrait la description associée à l'indice 2
                solution_description = df.filter(pl.col("idx") == 2)["text"][0]
            else:
                # Sinon, utilise un texte par défaut indiquant l'absence de description
                solution_description = "Description non disponible"

            # Définit un dictionnaire pour associer des niveaux de seuil à des couleurs
            colours = {'None': '#cccccc',
                       'Confiance faible': '#ef3303',
                       'Confiance moyenne': '#efbb30',
                       'Confiance élevée': '#33ef33'}

            # Crée un conteneur pour afficher les informations de la solution
            c = st.container(border=True)
            # Utilise le conteneur pour créer une ligne avec le titre de l'expander et le treshold aligné à droite
            c1, c2 = c.columns([0.8, 0.2])  # Ajustez la répartition selon le besoin

            c1.markdown(f"<h4>{solution['number']} : {solution_text}</h4> {solution_techno}", unsafe_allow_html=True)
            c2.markdown(f"<h5 style='color:{colours[solution['threshold']]}; text-align:center'>{solution['threshold']}</h5>", unsafe_allow_html=True)
            if solution_description == "Description non disponible":
                c.write(solution_description)
            else:
                hide_expander_border = """
                    <style>
                    [data-testid="stExpander"] details {
                        border-style: none;
                        }
                    </style>
                    """
                st.markdown(hide_expander_border, unsafe_allow_html=True)  # Cache la bordure de l'expander

                # Crée un expander pour les détails supplémentaires sans répéter les informations du titre
                with c.expander("Voir plus d'informations"):
                    # À l'intérieur de l'expander, affichez uniquement la description détaillée ou d'autres informations
                    st.markdown(solution_description, unsafe_allow_html=True)
            c_button, c_count = c.columns([2, 1])
            c_button.button("Calculer", key=solution['number'], on_click=set_codesolution_session, args=[solution['number']])
            c_count.markdown(f"Études de cas: {fetch_cases_count(solution['number'])}")

    # Bloc de gestion des exceptions pour les erreurs de requête
    except requests.exceptions.RequestException as e:
        # Affiche un message d'erreur si une exception est levée lors des requêtes
        st.error(f"An error occurred : {e}")  # Affiche une erreur en cas de problème avec la requête

@st.cache_data
def fetch_solution_information(codesolution: int):
    """Retourne des informations détaillées sur une solution à partir de son code

    Args:
        codesolution (int): Le code de la solution pour laquelle les informations sont recherchées
    """
    api_url = f"http://api:8000/solution/{codesolution}"  # URL de l'API pour récupérer des informations détaillées sur une solution

    try:
        response = requests.get(api_url)  # Envoie une requête GET à l'API
        response.raise_for_status()  # Vérifie que la requête s'est bien passée, sinon lève une exception
        data = response.json()  # Convertit la réponse en JSON
        return data  # Retourne les données

    except requests.exceptions.RequestException as e:
        st.error(f"An error ocurred : {e}")  # Affiche une erreur en cas de problème avec la requête

def local_css(file_name):
    with open(file_name) as f:
        st.markdown(f"<style>{f.read()}</style>", unsafe_allow_html=True)

@st.cache_data(experimental_allow_widgets=True)
def fetch_calculations(codesolution: int):
    """ good luck  """
    info = pl.from_dicts(requests.get(f"http://api:8000/solution/{codesolution}").json())
    text_solution = info.filter(pl.col("idx") == 1)["text"][0]
    st.subheader(f"{codesolution}:\t{text_solution}")
    cols = ["textsecteur", "textpays", "textregion", "textpublic", "texttechno1", "texttechno2", "texttechno3"]
    sec = pl.from_dicts(requests.get("http://api:8000/sec").json())
    pay = pl.from_dicts(requests.get("http://api:8000/pay").json())
    reg = pl.from_dicts(requests.get("http://api:8000/reg").json())
    pub = pl.from_dicts(requests.get("http://api:8000/pub").json())
    tec = pl.from_dicts(requests.get("http://api:8000/tec").json())
    default_values = ["Secteur", "Pays", "Région", "Domaine", "Technologie"]

    c_sec, c_pay, c_reg, c_pub, c_tec = st.columns(5)
    sec_selected = c_sec.selectbox("Secteur", sec["sec"], index=None)
    pay_selected = c_pay.selectbox("Pays", pay["pay"], index=None)
    if pay_selected is not None:
        reg = pl.from_dicts(requests.get("http://api:8000/reg", params={"codepay": int(pay.filter(pl.col("pay") == pay_selected)["codepay"][0])}).json())
    reg_selected = c_reg.selectbox("Région", reg["reg"], index=None)
    pub_selected = c_pub.selectbox("Domaine", pub["pub"], index=None)
    tec_selected = c_tec.selectbox("Techno", tec["tec"], index=None)

    query = ", ".join([item if item is not None else default_values[i] for i, item in enumerate([sec_selected, pay_selected, reg_selected, pub_selected, tec_selected])])
    st.write(f"Votre recherche: {query}")
    res = requests.get("http://api:8000/cases", params={'query': query, 'codesolution': codesolution})
    res.raise_for_status()
    data_info_c, toggle_c = st.columns([3, 1])
    show_data = toggle_c.toggle("Voir les données", False)
    data = res.json()
    c_df = st.container()
    c_cout, c_button = st.columns([3, 1])
    c1, c2, c3 = st.columns(3)
    if len(data) > 0:
        df = pl.from_dicts(data)
        df = df.with_columns(pl.Series("count", values=[3 - row.count(None) for row in df[["gainfinancierEUR", "coutfinancierEUR", "tri"]].rows()]))
        if show_data:
            c_df.dataframe(df[cols])
            c_df.dataframe(df[["score", "count", "gainfinancierEUR", "coutfinancierEUR", "tri", "gainenergie_kWh", "textunitenergie", "textperiodeenergie"]])

        ## starting prediction
        # predicted_tri = calculate_value(df, "tri")
        gain_p = calculate_poly(df, "coutfinancierEUR", "gainfinancierEUR")
        ges_p = calculate_poly(df, "coutfinancierEUR", "ges")
        energie_p = calculate_poly(df, "coutfinancierEUR", "gainenergie_kWh")

        predicted_cout = c_cout.text_input("label", placeholder="Coût", label_visibility="hidden")
        if not predicted_cout:
            predicted_cout = 1000.0
        else:
            predicted_cout = float(predicted_cout)
            if predicted_cout > 100000000000000000:
                predicted_cout = 1000.0

        c_button.write("")
        c_button.write("")
        if c_button.button("Prédire"):
            c1.metric("Cout", value=f"{predicted_cout:0,.2f}€")
            if gain_p is None:
                c2.error("Gain: pas assez de données")
                c3.error("TRI: pas assez de données")
            else:
                predicted_gain = gain_p[0] * predicted_cout ** 2 + gain_p[1] * predicted_cout + gain_p[2]
                c2.metric("Gain", value=f"{predicted_gain:0,.2f}€")
                c3.metric("TRI", value=f"{predicted_cout / predicted_gain:.1f} années")
                if show_data:
                    line_x = np.linspace(0, predicted_cout, 100)
                    line_y = gain_p[0] * line_x ** 2 + gain_p[1] * line_x + gain_p[2]
                    fig = sns.scatterplot(df.to_pandas(), x="coutfinancierEUR", y="gainfinancierEUR")
                    fig.plot(line_x, line_y)
                    plt.grid()
                    c_df.pyplot(fig.get_figure())
                    plt.close()

            if energie_p is None:
                c1.error("Énergie: pas assez de données")
            else:
                predicted_energie = energie_p[0] * predicted_cout ** 2 + energie_p[1] * predicted_cout + energie_p[2]
                if predicted_energie > 999:
                    energie, k = value_to_human_read(predicted_energie)
                else:
                    energie = predicted_energie
                    k = ""
                per = df["textperiodeenergie"].value_counts().max()["textperiodeenergie"][0]
                if per is None:
                    per = "/an"
                c1.metric("Energie", value=f"{energie:.0f} {k}Wh{per}")
                if show_data:
                    line_x = np.linspace(0, predicted_cout, 100)
                    line_y = energie_p[0] * line_x ** 2 + energie_p[1] * line_x + energie_p[2]
                    fig = sns.scatterplot(df.to_pandas(), x="coutfinancierEUR", y="gainenergie_kWh")
                    fig.plot(line_x, line_y)
                    plt.grid()
                    c_df.pyplot(fig.get_figure())
                    plt.close()

            if ges_p is None:
                c3.error("Ges: pas assez de données")
            else:
                predicted_ges = ges_p[0] * predicted_cout ** 2 + ges_p[1] * predicted_cout + ges_p[2]
                if predicted_ges > 999:
                    ges, k = value_to_human_read(predicted_ges)
                else:
                    ges = predicted_ges
                    k = ""
                c3.metric("GES", value=f"{ges:.0f} {k}tCO2/an")

    else:
        if show_data:
            c_df.json(data)
        c_df.error("Pas d'étude de cas pour votre solution, veuillez en essayer une autre.")

def add_currency_to_input(label, cur_symbol='€'):
    st.markdown(
        f"""
        <style>
            [aria-label="{label}"] {{
                padding-left: 30px;
            }}
            [data-testid="stNumberInput"]:has([aria-label="{label}"])::before {{
                position: absolute;
                content: "{cur_symbol}";
                left:12px;
                top:8px;
            }}
        </style>
        """,
        unsafe_allow_html=True,
    )

def calculate_poly(df, colx, coly, d=1):
    df2 = df.filter(pl.col(coly).is_not_null()).with_columns(((pl.col("score") * pl.col("count")) / (pl.col("score") * pl.col("count")).sum()).alias("prob"))[[coly, colx, "prob"]].drop_nulls()
    if len(df2) == 0:
        return None
    if len(df2) == 1 or True:
        df2 = pl.concat([pl.DataFrame({coly: 0.0, colx: 0.0, "prob": 1.0}), df2])
    x = df2[colx].to_numpy()
    y = df2[coly].to_numpy()
    weights = df2["prob"].to_numpy()
    if d == 2:
        a, b, c = np.polyfit(x, y, deg=d, w=weights)
    elif d == 1:
        b, c = np.polyfit(x, y, deg=d, w=weights)
        a = 0
    return a, b, c

def value_to_human_read(value):
    """
        c1.metric("Gain", value=f"{gain:0,.2f}€")
        gain = calculate_value(df, 'gainfinancierEUR')
        c1.metric("Gain Financier", value=f"{gain:0,.2f}€")
        cout = calculate_value(df, 'coutfinancierEUR')
        c2.metric("Coût Financier", value=f"{cout:0,.2f}€")
        tri = calculate_value(df, 'tri')
        c3.metric("TRI", value=f"{tri:.2f} années")
        ges = calculate_value(df, 'ges')
        ges, k = value_to_human_read(ges)
        c3.metric("TRI", value=f"{ges:.0f} {k}tCO2/an")
    """
    if value == 0:
        raise ValueError("Size is not valid.")
    value = int(value)
    size_name = ("", "k", "M", "G", "T", "P", "E", "Z", "Y")
    index = int(math.floor(math.log(value, 1024)))
    power = math.pow(1024, index)
    size = round(value / power, 2)
    return size, size_name[index]

def calculate_value(df, column):
    df = df.filter(pl.col(column).is_not_null()).with_columns(((pl.col("score") * pl.col("count")) / (pl.col("score") * pl.col("count")).sum()).alias("prob"))
    value = df.select(pl.col("prob") * pl.col(column))["prob"].sum()
    return value

def main():
    """Application Streamlit pour la recherche de solutions en français"""

    # Configure la page
    st.set_page_config(page_title="Trouver des solutions", layout="centered", page_icon="🔍")
    main_bg = "background.jpg"
    main_bg_ext = "jpg"
    import base64
    st.markdown(f"""
    <style>
        .reportview-container {{
            margin-top: -2em;
        }}
        # MainMenu {{visibility: hidden;}}
        footer {{visibility: hidden;}}
        #stDecoration {{display:none;}}
        header {{visibility: hidden;}}
        [data-testid="stApp"] {{
            background-image: url(data:{main_bg_ext};base64,{base64.b64encode(open(main_bg, "rb").read()).decode()});
            background-size: 100%;
        }}
        .st-emotion-cache-r421ms {{
            background-color: rgba(255, 255, 255, 1);
        }}
    </style>
""", unsafe_allow_html=True)
    # Crée un conteneur pour une meilleure organisation visuelle
    if 'codesolution' not in st.session_state:
        # Crée un conteneur pour une meilleure organisation visuelle
        with st.container():
            st.title("Kerdos Solutions Finder")
            st.subheader("Décrivez votre problème ou votre question et je trouverai les solutions les plus utiles pour vous.")

            c_button, c_duration, c_energy, c_emission = st.columns([2, 1, 2, 2])
            # ici on veut rajouter un bouton de refresh d embedding
            refresh_button = c_button.button("Recharger le modèle", use_container_width=True)
            if refresh_button:
                ## loader icon
                with st.spinner("en cours..."):
                    ## try to fetch http://api:8000/refreshembeedings en methode get
                    try:
                        response = requests.get("http://api:8000/refreshembeddings")
                        response.raise_for_status()
                        data = response.json()
                        c_duration.metric("Duration", f"{data['duration'] / 10:.1f}s")
                        c_emission.metric("Emissions", f"{data['emissions']:.4f} kg eq. CO2")
                        c_energy.metric("Electricy", f"{data['energy_consumed']:.4f} kWh")
                        st.write("Apprentissage terminé")
                    except requests.exceptions.RequestException as e:
                        st.error(f"An error occurred: {e}")

        # Champ de saisie pour l'utilisateur
        # could use a placeholder that changes and gives suggestions ?
        if 'query' in st.session_state:
            requete_utilisateur = st.session_state['query']
            requete_utilisateur = st.text_input("Décrivez votre problème ou votre question :", value=st.session_state['query'])
        else:
            requete_utilisateur = st.text_input("Décrivez votre problème ou votre question :")

        # Bouton pour démarrer la recherche
        if st.button("Rechercher des solutions"):
            if not requete_utilisateur:
                st.error("Veuillez entrer une requête pour rechercher des solutions.")
            else:
                fetch_query(requete_utilisateur)
    else:
        with st.container():
            st.title("Kerdos Solutions Calculator")

        fetch_calculations(st.session_state.codesolution)

        st.button("Retour", on_click=reset_session, args=['codesolution'])


if __name__ == "__main__":
    main()
