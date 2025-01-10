#include "events.h"
#include "Files.h" // Include fișierul Files.h pentru a folosi funcțiile din Files.cpp
#include <iostream>
#include <iomanip>

using namespace std;

// Definirea clasei EvenimentSpecial

EvenimentSpecial::EvenimentSpecial(const string& nume, const string& data, const string& descriere, 
                                   const string& locatie, double cost, int nrParticipanti)
    : numeEveniment(nume), data(data), descriere(descriere), locatie(locatie), 
      costParticipare(cost), nrParticipanti(nrParticipanti) {}

void EvenimentSpecial::displayEvenimentInfo() const {
    cout << "Nume Eveniment: " << numeEveniment << "\n";
    cout << "Data: " << data << "\n";
    cout << "Descriere: " << descriere << "\n";
    cout << "Locatie: " << locatie << "\n";
    cout << "Cost per Participare: " << fixed << setprecision(2) << costParticipare << " RON\n";
    cout << "Numar Participanti: " << nrParticipanti << "\n";
    cout << "Cost Total Eveniment: " << fixed << setprecision(2) << calculeazaCostTotal() << " RON\n";
    cout << "----------------------------------------\n";
}

double EvenimentSpecial::calculeazaCostTotal() const {
    return costParticipare * nrParticipanti;
}

const string& EvenimentSpecial::getNumeEveniment() const {
    return numeEveniment;
}

const string& EvenimentSpecial::getData() const {
    return data;
}

const string& EvenimentSpecial::getLocatie() const {
    return locatie;
}

double EvenimentSpecial::getCostParticipare() const {
    return costParticipare;
}

int EvenimentSpecial::getNrParticipanti() const {
    return nrParticipanti;
}

EvenimentSpecial::~EvenimentSpecial() {}

// Definirea clasei EvenimenteMenu

EvenimenteMenu* EvenimenteMenu::instance = nullptr;

EvenimenteMenu::EvenimenteMenu() {
    vector<vector<string>> data = readCSV("special_events.csv");

    for (int i = 1; i < data.size(); i++) { // Sărim peste header
        const auto& line = data[i];
        if (line.size() < 6) continue;

        string numeEveniment = line[0];
        string dataEveniment = line[1];
        string descriere = line[2];
        string locatie = line[3];
        double costParticipare = stod(line[4]);
        int nrParticipanti = stoi(line[5]);

        evenimente.push_back(new EvenimentSpecial(numeEveniment, dataEveniment, descriere, locatie, costParticipare, nrParticipanti));
    }
}

EvenimenteMenu* EvenimenteMenu::getInstance() {
    if (instance == nullptr) {
        instance = new EvenimenteMenu();
    }
    return instance;
}

EvenimenteMenu::~EvenimenteMenu() {
    for (auto eveniment : evenimente) {
        delete eveniment;
    }
    evenimente.clear();
}

void EvenimenteMenu::adaugaEveniment() {
    string nume, dataEveniment, descriere, locatie;
    double cost;
    int nrParticipanti;

    cout << "Introduceti numele evenimentului: ";
    cin >> nume;
    cout << "Introduceti data evenimentului (YYYY-MM-DD): ";
    cin >> dataEveniment;
    cout << "Introduceti descrierea evenimentului: ";
    cin.ignore();
    getline(cin, descriere);
    cout << "Introduceti locatie: ";
    getline(cin, locatie);
    cout << "Introduceti costul per participare (RON): ";
    cin >> cost;
    cout << "Introduceti numarul de participanti: ";
    cin >> nrParticipanti;

    evenimente.push_back(new EvenimentSpecial(nume, dataEveniment, descriere, locatie, cost, nrParticipanti));

    vector<vector<string>> data = {{nume, dataEveniment, descriere, locatie, to_string(cost), to_string(nrParticipanti)}};
    writeCSV("evenimente_speciale.csv", data, true);
}

void EvenimenteMenu::afiseazaEvenimente() {
    for (const auto& eveniment : evenimente) {
        eveniment->displayEvenimentInfo();
    }
}

void EvenimenteMenu::afiseazaCostTotalEvenimente() {
    double costTotal = 0.0;
    for (const auto& eveniment : evenimente) {
        costTotal += eveniment->calculeazaCostTotal();
    }
    cout << "Cost total pentru toate evenimentele: " << fixed << setprecision(2) << costTotal << " RON\n";
}

void EvenimenteMenu::MenuForEvenimente() {
    int choice;
    cout << "Alegeti o optiune:\n";
    cout << "1. Adauga un eveniment\n";
    cout << "2. Afiseaza toate evenimentele\n";
    cout << "3. Afiseaza costul total al evenimentelor\n";
    cout << "0. Iesire\n";
    cin >> choice;
    cin.ignore();

    switch(choice) {
        case 1:
            adaugaEveniment();
            break;
        case 2:
            afiseazaEvenimente();
            break;
        case 3:
            afiseazaCostTotalEvenimente();
            break;
        case 0:
            break;
        default:
            cout << "Optiune invalida!\n";
            break;
    }
}

void EvenimenteMenu::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}