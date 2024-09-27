#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Robots.hpp" 
#include <algorithm>

int main() {
    // Appel de la fonction read pour lire les robots à partir du fichier "Robots.txt"
    std::vector<Robot> robots = Robot::read("./Robots.txt");
    //affichage des robots lus
    std::cout << "Robots lus depuis le fichier : " << robots.size() << std::endl;
    for (Robot robot : robots) {
        std::cout << robot << std::endl;
    }
    std::cout << "====================================" << std::endl;
    //lets find the bot called "Wall-e"
    std::string name = "Wall-e";
    for (Robot robot : robots) {
        if (robot.getName() == name) {
            std::cout << "Robot " << name << " found!" << std::endl;
            break;
        }
    }

    std::cout << "====================================" << std::endl;
    //sort by price, storage of the sorted robots in a new vector that will be written in SortedRobots.txt
    std::vector<Robot> sortedRobots = robots;
    std::sort(sortedRobots.begin(), sortedRobots.end(), [](const Robot& a, const Robot& b) {
        return a.price < b.price;
    });
    std::ofstream outfile("SortedRobots.txt");
    for (Robot robot : sortedRobots) {
        outfile << robot << std::endl;
    }

    return 0;
}
