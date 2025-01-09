#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include "Files.h"
#include "comenzi.h"
#include "produse.h"

using namespace std;

Comanda::Comanda(const string& nm, const string& pr, const string& cty, int nr, const string& prd)
    : nume(nm), prenume(pr), oras(cty), nrProduse(nr), produse(prd) {}

void Comanda::displayOrderInfo() const {
    cout << "Nume: " << nume << "\n";
    cout << "Prenume: " << prenume << "\n";
    cout << "Oras: " << oras << "\n";
    cout << "Numar de produse: " << nrProduse << "\n";
    cout << "Produse: " << produse << "\n";
    cout << "--------------------------------------------\n";
}

const string& Comanda::getNume() const {
    return nume;
}
const string& Comanda::getPrenume() const {
    return prenume;
}
const string& Comanda::getOras() const {
    return oras;
}
const string& Comanda::getProduse() const {
    return produse;
}
int Comanda::getNrProduse() {
    return nrProduse;
}

Comanda::~Comanda() {
    cout << "Destructor comanda\n";
}

comenziMenu::comenziMenu() {
    try {
        // Adaugă un mesaj de debug pentru a verifica că funcția este apelată
        cout << "Se initializeaza meniul comenzilor...\n";

        // Încearcă să citești fișierul CSV
        vector<vector<string>> data = readCSV("orders.csv");

        // Confirmă că fișierul a fost citit
        cout << "S-a citit fisierul orders.csv\n";
        cout << "Citire fisier orders.csv: " << data.size() << " randuri citite.\n";

        // Parcurge liniile din fișier
        for (int i = 1; i < data.size(); i++) { // Start de la 1 pentru a ignora antetul, dacă există
            const auto& line = data[i];

            // Debug: afișează fiecare linie citită
            cout << "Linie " << i << ": ";
            for (const auto& field : line) {
                cout << field << " ";
            }
            cout << endl;

            // Verifică dacă linia are suficiente câmpuri
            if (line.size() < 5) {
                cerr << "Avertisment: Linia " << i << " nu are suficiente campuri. Este ignorata.\n";
                continue;
            }

            // Extrage câmpurile din linie
            string nume = line[0];
            string prenume = line[1];
            string oras = line[2];
            int nrProduse = stoi(line[3]);
            string produse = line[4];

            // Creează și adaugă o nouă comandă
            comenzi.push_back(new Comanda(nume, prenume, oras, nrProduse, produse));
        }
    } catch (const runtime_error& e) {
        cerr << "Eroare la citirea fișierelor CSV: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Eroare neasteptata: " << e.what() << endl;
    } catch (...) {
        cerr << "O eroare necunoscuta a aparut.\n";
    }
}


comenziMenu* comenziMenu::getInstance() {
    if (instance == nullptr) {
        instance = new comenziMenu();
        cout << "S-a creat o instanta pentru prima data a meniului de comenzi.\n";
    }
    return instance;
}

comenziMenu::~comenziMenu(){
    for(auto comanda : comenzi){
        delete comanda;
    }
    comenzi.clear();
}

void comenziMenu::addOrder() {
    string nume, prenume, oras, produse;
    int nrProduse;

    cout << "Introduceti numele clientului: ";
    cin >> nume;
    cout << "Introduceti prenumele clientului: ";
    cin >> prenume;
    cout << "Introduceti orasul unde se afla cafeneaua: ";
    cin >> oras;
    cout << "Introduceti numarul de produse: ";
    cin >> nrProduse;
    cin.ignore(); // Curăță bufferul de intrare

    cout << "Introduceti produsele (separate prin virgula): ";
    getline(cin, produse);

    vector<string> productList = splitString(produse, ',');

    double total = 0.0;
    bool allProductsAvailable = true;

    for (const auto& product : productList) {
        string trimmedProduct = trim(product); // Curăți spațiile albe

        // Verifici dacă produsul este în map-ul de produse
        if (productData.find(trimmedProduct) != productData.end() &&
            productData[trimmedProduct].find(oras) != productData[trimmedProduct].end()) {
            total += productData[trimmedProduct][oras]; // Adaugi prețul la total
        } else {
            cout << "Produsul \"" << trimmedProduct << "\" nu este disponibil in orasul " << oras << ".\n";
            allProductsAvailable = false;
        }
    }

    if (allProductsAvailable) {
        cout << "Comanda a fost plasata cu succes. Total: " << total << " RON.\n";
        comenzi.push_back(new Comanda(nume, prenume, oras, nrProduse, produse)); // Salvezi comanda
    } else {
        cout << "Comanda nu a fost procesată din cauza produselor indisponibile.\n";
    }
}

void comenziMenu::displayAllOrders() {
    for (const auto& comanda : comenzi) {
        comanda->displayOrderInfo();
    }
}

void comenziMenu::displayAllOrdersByCity() {
    vector<string> cities = {"Timisoara", "Iasi", "Bucuresti", "Cluj-Napoca", "Brasov"};

    for (const auto& city : cities) {
        cout << "Comenzi disponibile in orasul " << city << ":\n";
        bool found = false;

        for (const auto& comanda : comenzi) {
            if (comanda->getOras() == city) {
                comanda->displayOrderInfo();
                found = true;
            }
        }

        if (!found) {
            cout << "Nu exista comenzi disponibile in acest oras.\n";
        }

        cout << "============================================\n";
    }
}

/*void comenziMenu::calculateTotalByCity() {
    map<string, double> totalByCity;

    for (const auto& comanda : comenzi) {
        totalByCity[comanda->getOras()] += comanda->getNrProduse();
    }

    cout << "Total produse pe oras:\n";
    for (const auto& [oras, total] : totalByCity) {
        cout << oras << ": " << total << " produse\n";
    }
}
*/

void comenziMenu::MenuForOrders(){
    int choice;
    cout << "Alegeti o optiune:\n";
    cout << "1. Adauga o comanda\n";
    cout << "2. Afiseaza toate comenzile\n";
    cout << "3. Afiseaza comenzile dintr-un oras\n";
    cout << "4. Calculeaza totalul de produse pe oras\n";
    cout << "0. Iesire\n";
    cin >> choice;
    cin.ignore();

    switch(choice){
        case 1:
            addOrder();
            break;
        case 2:
            displayAllOrders();
            cout << "Numar comenzi incarcate: " << comenzi.size() << endl;
            break;
        case 3:
            displayAllOrdersByCity();
            break;
        case 4:
            //calculateTotalByCity();
            break;
        case 0:
            break;
        default:
            cout << "Optiune invalida!\n";
            break;
    }
}

void comenziMenu::destroyInstance() { // Implementarea funcției
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

comenziMenu* comenziMenu::instance = nullptr;