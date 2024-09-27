#include "Guirlande.hpp"

Guirlande::Guirlande() : length(0), price(0), representation("") {}

Guirlande::Guirlande(int length) : length(length), price(0), representation("") {}

void Guirlande::addAmpoule(Ampoule ampoule) {
    ampoules.push_back(ampoule);
    price += ampoule.getPrice();
    representation += ampoule.getRepresentation();
}

void Guirlande::display() const {
    cout << representation << endl;
}

double Guirlande::getPrice() const {
    return price;
}

int Guirlande::getLength() const {
    return length;
}

string Guirlande::getRepresentation() const {
    return representation;
}

void Guirlande::setPrice(double price) {
    this->price = price;
}

//getterPrice Cable en fonction du nombre d ampoules => 1.1 * (nb ampoules - 1)
double Guirlande::getPriceCable() const {
    return 1.1 * (ampoules.size() - 1);
}

void Guirlande::setPriceCable(double priceCable) {
    this->priceCable = priceCable;
}

//getterPrice Ampoules
double Guirlande::getPriceAmpoules() const {
    //pour chaque ampoule on rajoute son prix
    double priceAmpoules = 0;
    for (Ampoule ampoule : ampoules) {
        priceAmpoules += ampoule.getPrice();
    }
    return priceAmpoules;
}

void Guirlande::setPriceAmpoules(double priceAmpoules) {
    this->priceAmpoules = priceAmpoules;
}

//getterPrice Total Before Margin
double Guirlande::getPriceTotalBeforeMargin() const {
    return priceAmpoules + priceCable;
}

void Guirlande::setPriceTotalBeforeMargin(double priceTotalBeforeMargin) {
    this->priceTotalBeforeMargin = priceTotalBeforeMargin;
}

//getterPrice Total After Margin
double Guirlande::getPriceTotalAfterMargin() const {
    return priceTotalBeforeMargin * 1.2;
}

void Guirlande::setPriceTotalAfterMargin(double priceTotalAfterMargin) {
    this->priceTotalAfterMargin = priceTotalAfterMargin;
}



static vector<Guirlande> read(const string& path) {
    vector<Guirlande> guirlandes;
    ifstream infile(path);
    if (!infile.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << path << endl;
        return guirlandes;
    } else {
        cout << "File " << path << " opened successfully." << endl;
        string line;
        while (getline(infile, line)) {
            Guirlande guirlande;
            for (char c : line) {
                Ampoule ampoule(c == 'O' ? 0.5 : 0.05);
                guirlande.addAmpoule(ampoule);
            }
            guirlandes.push_back(guirlande);
        }
    }
    return guirlandes;
}

static void write(const string& path, const Guirlande& guirlande) {
    string myPath = "./guirlandes_data.txt";
    ofstream outfile(myPath);
    if (!outfile.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << path << endl;
        return;
    }
    outfile << guirlande.getRepresentation() << " " << guirlande.getPriceTotalAfterMargin() << endl;
    outfile.close();
}


