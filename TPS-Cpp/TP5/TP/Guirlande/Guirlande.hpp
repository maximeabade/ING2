
#ifndef GUIRLANDE_HPP
#define GUIRLANDE_HPP


#include "Electrique.hpp"
#include "Ampoule.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Guirlande {
    public:
        Guirlande();
        Guirlande(int length);
        void addAmpoule(Ampoule ampoule);
        void display() const;
        double getPrice() const;
        void setPrice(double price);
        int getLength() const;
        vector<Ampoule> ampoules;
        int length;
        string representation;
        string getRepresentation() const;
        double price;
        double priceCable;
        double getPriceCable() const;
        void setPriceCable(double priceCable);
        double priceAmpoules;
        double getPriceAmpoules() const;
        void setPriceAmpoules(double priceAmpoules);
        double priceTotalBeforeMargin;
        double getPriceTotalBeforeMargin() const;
        void setPriceTotalBeforeMargin(double priceTotalBeforeMargin);
        double priceTotalAfterMargin;
        double getPriceTotalAfterMargin() const;
        void setPriceTotalAfterMargin(double priceTotalAfterMargin);

        //read du fichier "guirlandes.txt" ==> getLine pour chaque guirlande, sa reorésentation sera "oOOooo" par exemple
        static vector<Guirlande> read(const string& path);
        
        //ecriture de la guirlande et de son prix dans un fichier
        static void write(const string& path, const Guirlande& guirlande);

};

#endif // GUIRLANDE_HPP

