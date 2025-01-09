#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include "produse.h"
#include "Files.h"

using namespace std;


Produs::Produs(const string& nm, const string& ctg, const string& cty, double pr, double cp, int st, int nV)
        : nume(nm), categorie(ctg), oras(cty), pret(pr), costProductie(cp), stock(st), nrVandute(nV){}

void Produs::displayInfo() const {
            cout << fixed << setprecision(2);
            cout << "Nume: " << nume << "\n";
            cout << "Categorie: " << categorie << "\n";
            cout << "Pret: " << pret << "\n";
            cout << "Cost de productie: " << costProductie << "\n";
            cout << "Stoc: " << stock << "\n";
            cout << "Numar de produse vandute: " << nrVandute << "\n";
}

const string& Produs::getNume() const {
    return nume; 
}
        
const string& Produs::getCategorie() const {
    return categorie;
}

const string& Produs::getOras() const {
    return oras;
}

int Produs::getNrVandute() {
    return nrVandute;
}

int Produs::getStock() {
    return stock;
}

double Produs::getPret() const {
    return pret;
}

double Produs::getCostProductie() { 
    return costProductie;
}

Produs::~Produs() {}

Sandwich::Sandwich(const string& nm, const string&cty,double prt, double cp, int st, int nV)
    : Produs(nm, "Sandwich", cty, prt, cp, st, nV) {}

void Sandwich::displayInfo() const {
    cout << "Sandwich - ";
    Produs::displayInfo();
}

Sandwich::~Sandwich() {}

Cafea::Cafea(const string& nm,const string& cty, double prt, double cp, int st, int nV)
    : Produs(nm, "Cafea", cty, prt, cp, st, nV) {}

void Cafea::displayInfo() const {
    cout << "Cafea - ";
    Produs::displayInfo();
}

Cafea::~Cafea() {}

Ceai::Ceai(const string& nm, const string& cty,double prt, double cp, int st, int nV)
    : Produs(nm, "Ceai", cty, prt, cp, st, nV) {}

void Ceai::displayInfo() const {
    cout << "Ceai - ";
    Produs::displayInfo();
}

Ceai::~Ceai() {}

Bauturi::Bauturi(const string& nm, const string&cty, double prt, double cp, int st, int nV)
    : Produs(nm, "Bauturi", cty, prt, cp, st, nV) {}

void Bauturi::displayInfo() const {
    cout << "Bauturi - ";
    Produs::displayInfo();
}

Bauturi::~Bauturi() {}

Desert::Desert(const string& nm, const string& cty,double prt, double cp, int st, int nV)
    : Produs(nm, "Desert", cty, prt, cp, st, nV) {}

void Desert::displayInfo() const {
    cout << "Desert - ";
    Produs::displayInfo();
}

Desert::~Desert() {}

produseMenu::produseMenu(){
            try {
                vector<vector<string>> data = readCSV("products.csv");
                cout << "S-a citit fisierul products.csv\n";

                for(int i = 1; i < data.size(); i++){
                    const auto& line = data[i];

                    if(line.size() < 7){
                        cerr << "Avertisment: Linia " << i << " are mai putine coloane (" << line.size() << "). Este ignorată.\n";
                        continue;
                    }

                    cout << "Verificare linie " << i << ": " 
                    << line[0] << ", " 
                    << line[1] << ", " 
                    << line[2] << ", " 
                    << line[3] << ", " 
                    << line[4] << ", " 
                    << line[5] << ", " 
                    << line[6] << endl;

                    string nume = line[0];
                    string categorie = line[1];
                    string oras = line[2];

                    // Elimină spațiile albe din jurul valorilor
                    double pret = stod(trim(line[3]));
                    double costProductie = stod(trim(line[4]));
                    int stock = stoi(trim(line[5]));
                    int nrVandute = stoi(trim(line[6]));

                    if(categorie == "Cafea"){
                        produse.push_back(new Cafea(nume, oras, pret, costProductie, stock, nrVandute));
                    } else if(categorie == "Sandwich"){
                        produse.push_back(new Sandwich(nume,oras, pret, costProductie, stock, nrVandute));
                    } else if(categorie == "Ceai"){
                        produse.push_back(new Ceai(nume, oras, pret, costProductie, stock, nrVandute));
                    } else if(categorie == "Bauturi"){
                        produse.push_back(new Bauturi(nume, oras, pret, costProductie, stock, nrVandute));
                    } else if(categorie == "Desert"){
                        produse.push_back(new Desert(nume,oras, pret, costProductie, stock, nrVandute));
                    }else{
                        cerr << "Categorie necunoscută pe linia " << i << ": " << categorie << ". Produsul este ignorat.\n";
                    }
                }
            } catch (const exception& e) {
                cerr << "Eroare: " << e.what() << endl;
            }
}

produseMenu::~produseMenu(){
    for(auto produs : produse){
        delete produs;
    }
}

produseMenu* produseMenu::getInstance(){
    if(instance == nullptr){
        instance = new produseMenu();
        cout << "S-a creat o instanta pentru prima data a meniului de produse.\n";
    }
    return instance;
}

void produseMenu::addProduct(){
            try{
                cout << "Introduceti nr de produse pe care doriti sa ii adaugati: ";
                int n;
                cin >> n;
                cin.ignore();
                vector<vector<string>> newData;

                for(int i = 0; i < n; i++){
                    cout << "Introduceti datele pentru produsul " << i + 1 << ":\n";

                    string nume, categorie, oras;
                    double pret, costProductie;
                    int stock, nrVandute;

                    cout << "Nume: ";
                    getline(cin, nume);
                    nume = capitalizeWords(nume);

                    cout << "Categorie: ";
                    getline(cin, categorie);
                    categorie = capitalizeWords(categorie);

                    cout << "Oras: ";
                    getline(cin, oras);
                    oras = capitalizeWords(oras);

                    cout << "Pret: ";
                    cin >> pret;
                    cin.ignore();

                    cout << "Cost de productie: ";
                    cin >> costProductie;
                    cin.ignore();

                    cout << "Stoc: ";
                    cin >> stock;
                    cin.ignore();

                    cout << "Numar de produse vandute: ";
                    cin >> nrVandute;
                    cin.ignore();

                    ostringstream ossPret, ossCostProductie;
                    ossPret << fixed << setprecision(1) << pret;
                    ossCostProductie << fixed << setprecision(1) << costProductie;

                    vector<string> newProduct = {nume, categorie, oras, ossPret.str(), ossCostProductie.str(), to_string(stock), to_string(nrVandute)};
                    newData.push_back(newProduct);
                }

                writeCSV("products.csv", newData, true);
                cout << "Produsele au fost adaugate cu succes!\n";
            } catch (const exception& e) {
                cerr << "Eroare: " << e.what() << endl;
            }
        }
void produseMenu::deleteProduct(const string& nume, const string& categorie, const string& oras){
            try{
                vector<vector<string>> updateData;
                vector<vector<string>> data = readCSV("products.csv");

                bool found = false;
                for (auto& line : data) {
                    string produsNume = trim(line[0]);
                    string produsCategorie = trim(line[1]);
                    string produsOras = trim(line[2]);

                    if (produsNume == nume && produsCategorie == categorie && produsOras == oras) {
                        found = true;
                        continue; // Sarim linia care trebuie stearsa
                    }
                    updateData.push_back(line);
                }

                for (int i = 0; i < produse.size(); i++) {
                    if (trim(produse[i]->getNume()) == nume && trim(produse[i]->getCategorie()) == categorie &&
                        trim(produse[i]->getOras()) == oras) {
                        delete produse[i];
                        produse.erase(produse.begin() + i);
                        break;
                    }
                }

                if(found){
                    writeCSV("products.csv", updateData, false);
                    cout << "Produsul " << nume << " a fost sters cu succes!\n";
                } else {
                    cout << "Produsul " << nume << " nu a fost gasit in baza de date!\n";
                }
            } catch (const exception& e) {
                cerr << "Eroare: " << e.what() << endl;
            }
        }

void produseMenu::displayAllProductsByCity(){
    vector<string> cities = {"Timisoara", "Iasi", "Bucuresti", "Cluj-Napoca", "Brasov"};

    for (const auto& city : cities) {
        cout << "Produse disponibile in orasul " << city << ":\n";
        bool found = false;

        for (const auto& produs : produse) {
            if (produs->getOras() == city) {
                produs->displayInfo();
                cout << "\n--------------------------------------------\n";
                found = true;
            }
        }

        if (!found) {
            cout << "Nu exista produse disponibile in acest oras.\n";
        }

        cout << "============================================\n";
    }
}
        
void produseMenu::calculateProfitByCity() {
            // Map pentru a stoca profitul total pentru fiecare oraș
            map<string, double> profitByCity;

            for (const auto& produs : produse) {
                profitByCity[produs->getOras()] += 
                    (produs->getPret() - produs->getCostProductie()) * produs->getNrVandute();
            }

            cout << "Profituri pe oras:\n";
            for (const auto& [oras, profit] : profitByCity) {
                cout << oras << ": " << profit << " RON\n";
            }
        }
void produseMenu::searchProductByCategoryandCity(const string& category, const string& name, const string& city){
            bool found = false;

            for (const auto& produs : produse) {
                if (produs->getCategorie() == category && produs->getNume() == name &&
                    produs->getOras() == city) {
                        cout << "Produs gasit:\n";
                        produs->displayInfo();
                        found = true;
                        break; // Se oprește după găsirea primului produs care corespunde
                }
            }

            if (!found) {
                cout << "Produsul cu numele \"" << name << "\" din categoria \"" 
                    << category << "\" nu a fost gasit în orasul \"" << city << "\".\n";
            }       
}
void produseMenu::MenuForProducts(){
            int choice;
            cout << "Alegeti o optiune:\n";
            cout << "1. Adauga in lista un produs\n";
            cout << "2. Sterge din lista un produs\n";
            cout << "3. Afiseaza produsele pe orase\n";
            cout << "4. Calculeaza profitul pentru cafenelele din fiecare oras\n";
            cout << "5. Cauta existenta unui produs intr-un anumit oras\n";
            cout << "0. Iesire\n";
            cin >> choice;
            cin.ignore();

            switch(choice){
                case 1:
                    addProduct();
                    break;
                case 2:{
                    cout << "Introduceti numele produsului pe care doriti sa il stergeti: ";
                    string nume;
                    getline(cin, nume);
                    nume = capitalizeWords(nume);
                    cout << "Introduceti categoria produsului: ";
                    string categorie;
                    getline(cin, categorie);
                    categorie = capitalizeWords(categorie);
                    cout << "Introduceti orasul: ";
                    string oras;
                    getline(cin, oras);
                    deleteProduct(nume,categorie,oras);
                    break;
                };
                case 3:
                    displayAllProductsByCity();
                    break;
                case 4:
                    calculateProfitByCity();
                    break;
                case 5:{
                    cout << "Introduceti numele produsului: ";
                    string nume;
                    getline(cin, nume);
                    nume = capitalizeWords(nume);

                    cout << "Introduceti categoria produsului: ";
                    string categorie;
                    getline(cin, categorie);
                    categorie = capitalizeWords(categorie);

                    cout << "Introduceti orasul: ";
                    string oras;
                    getline(cin, oras);
                    oras = capitalizeWords(oras);
                    searchProductByCategoryandCity(categorie, nume, oras);
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Optiune invalida!\n";
                    break;
            }
        }

void produseMenu::destroyInstance() {
    delete instance;
    instance = nullptr;
}

produseMenu* produseMenu::instance = nullptr;

map<string, map<string, double>> loadProductData(const string& filename) {
    map<string, map<string, double>> productData;

    // Citești fișierul CSV
    vector<vector<string>> data = readCSV(filename);

    for (size_t i = 0; i < data.size(); ++i) {
        const auto& line = data[i];

        // Sari peste liniile incomplete
        if (line.size() < 4) {
            cerr << "Linia " << i + 1 << " este incompleta și a fost ignorata.\n";
            continue;
        }

        string productName = line[0]; // Numele produsului
        string city = line[2];        // Orașul
        string priceStr = line[3];   // Prețul ca șir de caractere

        try {
            // Încearcă să convertești prețul la double
            double price = stod(priceStr);

            // Adaugă produsul și orașul în map
            productData[productName][city] = price;
        } catch (const exception& e) {
            // Dacă conversia eșuează, afișează o eroare
            cerr << "Eroare la conversia prețului pe linia " << i + 1 << ": " << priceStr
                 << ". Mesaj: " << e.what() << "\n";
        }
    }

    return productData;
}