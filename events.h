#ifndef EVENIMENTE_H
#define EVENIMENTE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

class EvenimentSpecial {
private:
    string numeEveniment;
    string data;
    string descriere;
    string locatie;
    double costParticipare;
    int nrParticipanti;

public:
    EvenimentSpecial(const string& nume, const string& data, const string& descriere, 
                     const string& locatie, double cost, int nrParticipanti);

    void displayEvenimentInfo() const;
    double calculeazaCostTotal() const;
    const string& getNumeEveniment() const;
    const string& getData() const;
    const string& getLocatie() const;
    double getCostParticipare() const;
    int getNrParticipanti() const;
    ~EvenimentSpecial();
};

class EvenimenteMenu {
private:
    vector<EvenimentSpecial*> evenimente;
    static EvenimenteMenu* instance;

    EvenimenteMenu();
public:
    static EvenimenteMenu* getInstance();
    ~EvenimenteMenu();

    void adaugaEveniment();
    void afiseazaEvenimente();
    void afiseazaCostTotalEvenimente();
    void MenuForEvenimente();
    static void destroyInstance();
};

#endif // EVENIMENTE_H
