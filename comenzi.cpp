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

Comanda::Comanda(const string& nm, const string& pr, const string& cty, int nr, const string& prd,double tot, double disc = 0.0)
    : nume(nm), prenume(pr), oras(cty), nrProduse(nr), produse(prd), total(tot),discount(disc) {}

void Comanda::displayOrderInfo() const {
    cout << "Nume: " << nume << "\n";
    cout << "Prenume: " << prenume << "\n";
    cout << "Oras: " << oras << "\n";
    cout << "Numar de produse: " << nrProduse << "\n";
    cout << "Produse: " << produse << "\n";
    cout << "Total comanda: " << fixed << setprecision(1) << total << " RON\n";
    cout << "Discount: " << fixed << setprecision(1) << discount << " RON\n";
    cout << "Total de plata dupa reducere: " << fixed << setprecision(1) << (total - total*discount) << " RON\n";
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
double Comanda::getTotal() {
    return total - (total * discount);
}

void Comanda::setDiscount(double disc) {
    discount = disc;
}

Comanda::~Comanda() {
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
            if (line.size() < 6) {
                cerr << "Avertisment: Linia " << i << " nu are suficiente campuri. Este ignorata.\n";
                continue;
            }

            // Extrage câmpurile din linie
            string nume = line[0];
            string prenume = line[1];
            string oras = line[2];
            int nrProduse = stoi(line[3]);
            string produse = line[4];
            double total = stod(line[5]);

            // Creează și adaugă o nouă comandă
            comenzi.push_back(new Comanda(nume, prenume, oras, nrProduse, produse, total));
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

double comenziMenu::calculateDiscount(const string& nume, const string& prenume) {
    int orderCount = 0;
    double totalSpent = 0.0;
    double discount = 0.0;

    // Citim istoricul comenzilor pentru acest client din orders.csv
    vector<vector<string>> orderHistory = readCSV("orders.csv");
    for (const auto& order : orderHistory) {
        if (order[0] == nume && order[1] == prenume) {
            orderCount++;
            totalSpent += stod(order[5]);
        }
    }

    // Aplica reducerile
    if (orderCount >= 3) {
        discount = 0.05;  // 5% reducere pentru 3 comenzi
    } else if (totalSpent >= 200) {
        discount = 0.10;  // 10% reducere pentru 200 RON cheltuiți
    }

    return discount;
}

void comenziMenu::addOrder() {
    string nume, prenume, oras;
    int nrProduse;

    cout << "Introduceti numele clientului: ";
    cin >> nume;
    cout << "Introduceti prenumele clientului: ";
    cin >> prenume;
    cout << "Introduceti orasul unde se afla cafeneaua: ";
    cin >> oras;

    cout << "Introduceti numarul de tipuri de produse disponibile: ";
    cin >> nrProduse;
    cin.ignore();

    map<string, int> productsOrdered;
    vector<string> orderedProducts;
    double total = 0.0;
    bool allProductsAvailable = true;

    vector<vector<string>> productData = readCSV("products.csv");

    // Procesăm produsele comandate
    for (int i = 0; i < nrProduse; ++i) {
        string productName;
        int quantity;

        cout << "Introduceti numele produsului " << (i + 1) << ": ";
        getline(cin, productName);
        productName = trim(productName);

        cout << "Cate unitati din " << productName << " doriti? ";
        cin >> quantity;
        cin.ignore();

        bool found = false;
        for (size_t j = 1; j < productData.size(); ++j) {
            vector<string> row = productData[j];
            string csvProductName = trim(row[0]);
            string csvCity = trim(row[2]);
            int stock = stoi(row[6]);
            double price = stod(row[3]);

            if (csvProductName == productName && csvCity == oras && stock >= quantity) {
                total += price * quantity;
                productsOrdered[productName] = quantity;
                orderedProducts.push_back(productName + " x" + to_string(quantity));
                row[6] = to_string(stock - quantity);
                productData[j] = row;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Produsul \"" << productName << "\" nu este disponibil sau nu exista suficient stoc.\n";
            allProductsAvailable = false;
        }
    }

    if (allProductsAvailable) {
        // Calculăm discount-ul pentru client
        double discount = calculateDiscount(nume, prenume);
        cout << "Reducere aplicata: " << discount * 100 << "%\n";

        total -= total * discount;  // Aplica reducerea la total

        string produse = joinString(orderedProducts, " | ");
        comenzi.push_back(new Comanda(nume, prenume, oras, nrProduse, produse, total, discount));

        ostringstream totalStream;
        totalStream << fixed << setprecision(1) << total;
        string totalFormatted = totalStream.str();

        // Salvăm comanda în orders.csv
        vector<vector<string>> orderData = {{nume, prenume, oras, to_string(nrProduse), produse, totalFormatted}};
        writeCSV("orders.csv", orderData, true);

        // Salvăm stocurile actualizate în products.csv
        writeCSV("products.csv", productData, false);
    } else {
        cout << "Comanda nu a fost procesata din cauza produselor indisponibile.\n";
    }
}


void comenziMenu::displayAllOrders() {
    for (const auto& comanda : comenzi) {
        comanda->displayOrderInfo();
    }
    cout << "Numar comenzi incarcate: " << comenzi.size() << endl;
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

void comenziMenu::calculateTotalByCity() {
    map<string, double> totalByCity;

    for (const auto& comanda : comenzi) {
        totalByCity[comanda->getOras()] += comanda->getTotal();
    }

    cout << "Total produse pe oras:\n";
    for (const auto& [oras, total] : totalByCity) {
        cout << oras << ": " << fixed << setprecision(2) << total << " RON\n";
    }
}

void comenziMenu::MenuForOrders(){
    int choice;
    cout << "Alegeti o optiune:\n";
    cout << "1. Adauga o comanda\n";
    cout << "2. Afiseaza toate comenzile\n";
    cout << "3. Afiseaza comenzile dintr-un oras\n";
    cout << "4. Calculeaza totalul comenzilor pe oras\n";
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
            calculateTotalByCity();
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