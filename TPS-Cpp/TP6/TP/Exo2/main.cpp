#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// Fonction pour diviser une chaîne en tokens en utilisant un délimiteur
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::string dataDir = "./data/";

    // Ensemble des caractéristiques distinctes
    std::unordered_set<std::string> distinctFeatures;

    // Parcourir tous les fichiers dans le répertoire data
    for (const auto& entry : fs::directory_iterator(dataDir)) {
        std::ifstream inputFile(entry.path());
        if (!inputFile.is_open()) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << entry.path() << std::endl;
            continue;
        }

        // Lecture des caractéristiques des applications
        std::string line;
        while (std::getline(inputFile, line)) {
            // Diviser la ligne en tokens
            std::vector<std::string> tokens = split(line, ',');

            // Parcourir les caractéristiques de l'application
            for (size_t i = 1; i < tokens.size(); ++i) {
                // Ajouter cette caractéristique à l'ensemble des caractéristiques distinctes
                distinctFeatures.insert(tokens[i]);
            }
        }

        inputFile.close();
    }

    // Vecteur d'incorporation initialisé à 0
    std::vector<int> initialEmbeddingVector(distinctFeatures.size(), 0);

    // Map pour stocker les vecteurs d'incorporation (embedding vectors) pour chaque application
    std::unordered_map<std::string, std::vector<int>> embeddingVectors;

    // Parcourir tous les fichiers dans le répertoire data pour construire les vecteurs d'incorporation
    for (const auto& entry : fs::directory_iterator(dataDir)) {
        std::ifstream inputFile(entry.path());
        if (!inputFile.is_open()) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << entry.path() << std::endl;
            continue;
        }

        // Lecture des caractéristiques des applications
        std::string line;
        while (std::getline(inputFile, line)) {
            // Diviser la ligne en tokens
            std::vector<std::string> tokens = split(line, ',');

            // Premier élément est le nom de l'application
            std::string appName = tokens[0];

            // Copie du vecteur d'incorporation initialisé à 0
            std::vector<int> embeddingVector(initialEmbeddingVector);

            // Parcourir les caractéristiques de l'application
            for (size_t i = 1; i < tokens.size(); ++i) {
                std::string feature = tokens[i];
                // Marquer la présence de cette caractéristique dans le vecteur d'incorporation
                auto it = distinctFeatures.find(feature);
                if (it != distinctFeatures.end()) {
                    embeddingVector[std::distance(distinctFeatures.begin(), it)] = 1;
                }
            }

            // Stocker le vecteur d'incorporation pour cette application
            embeddingVectors[appName] = embeddingVector;
        }

        inputFile.close();
    }


    // Création de chaînes représentant la présence des vecteurs d'incorporation pour chaque fichier
    for (const auto& entry : fs::directory_iterator(dataDir)) {
        std::ifstream inputFile(entry.path());
        if (!inputFile.is_open()) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << entry.path() << std::endl;
            continue;
        }
        std::string embeddingString = "0";
        std::cout << "Fichier: " << entry.path() << " - Présence des vecteurs d'incorporation: " << embeddingString << std::endl;

        std::string line;
        while (std::getline(inputFile, line)) {
            // Diviser la ligne en tokens
            std::vector<std::string> tokens = split(line, ',');
            // Vérifier si l'application est présente dans les vecteurs d'incorporation
            auto it = embeddingVectors.find(tokens[0]);
               // std::cout << "controle ici"<<std::endl;
                std::cout << tokens[0] << std::endl;
            //pour chaque fichier, si il contient l une des strings de tokens[0], on lui attribue la presence du vecteur
            //sa string representative prend donc la concatenation de 0 si il n'est pas present et 1 si il est present
                        if (it != embeddingVectors.end()) {
                // Ajouter la représentation de présence ou absence des caractéristiques à la chaîne
                for (int value : it->second) {
                    embeddingString += (value == 1) ? "1" : "0";
                }
                embeddingString += " ";
            }
        }

        inputFile.close();
    }

    return 0;
}
