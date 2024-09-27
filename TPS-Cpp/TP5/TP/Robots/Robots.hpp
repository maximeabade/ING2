#pragma once

#include <iostream>
#include <string>
#include <vector>

class Robot {
public:
    Robot();
    Robot(const std::string& name, const std::string& type, int price);

    friend std::ostream& operator<<(std::ostream& os, const Robot& robot);
    friend std::istream& operator>>(std::istream& is, Robot& robot);

    // Déclaration de la fonction read
    static std::vector<Robot> read(const std::string& path);

    std::string getName() const;
    std::string name;
    std::string type;
    int power;
    int price;
};


Robot::Robot() : power(0), price(0) {}

Robot::Robot(const std::string& name, const std::string& type,  int price) :
    name(name), type(type), power(power), price(price) {}

std::ostream& operator<<(std::ostream& os, const Robot& robot) {
    os << "Nom: " << robot.name << ", Type: " << robot.type << ", Prix: " << robot.price;
    return os;
}

std::istream& operator>>(std::istream& is, Robot& robot) {
    std::string name, type;
    int power, price;

    // Lecture des données du robot depuis le fichier
    if (is >> name >> type >> power >> price) {
        // Création d'un nouvel objet Robot et assignation des valeurs lues
        robot = Robot(name, type, price);
    }

    return is;
}

std::vector<Robot> Robot::read(const std::string& path)
{
    // Déclaration d'un vecteur pour stocker les robots
    std::vector<Robot> robots;

    // Ouverture du fichier Robots.txt en lecture
    std::ifstream infile(path);

if (!infile.is_open()) {
    std::cerr << "Erreur : impossible d'ouvrir le fichier " << path << std::endl;
    return robots; // Return empty vector
} else {
    std::cout << "File Robots.txt opened successfully." << std::endl;
    //utilisation de getline pour lire le fichier ligne par ligne
    std::string line;
    while (std::getline(infile, line)) {
        //std::cout << line << std::endl;
        //transformation en vecteur de la ligne
        std::vector<std::string> words;
        std::string word;
        for (char c : line) {
            if (c == ' ') {
                words.push_back(word);
                word = "";
            } else {
                word += c;
            }
        }
        words.push_back(word);
        //affichage du vector words

        //push des words dans le vector robots
        Robot robot(words[0], words[1], std::stoi(words[2]));
        robots.push_back(robot);
    }
    return robots;
}
}

std::string Robot::getName() const {
    return name;
}
