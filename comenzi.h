#ifndef COMENZI_H
#define COMENZI_H


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include "Files.h"

using namespace std;

class Comanda{

    protected:
        string nume;
        string prenume;
        string oras;
        int nrProduse;
        double total;
        string produse;
        double discount;
    public:
        Comanda(const string& nm, const string& pr, const string& cty, int nr, const string& prd, double tot, double disc);

        virtual void displayOrderInfo() const;
        const string& getNume() const;
        const string& getPrenume() const;
        const string& getOras() const;
        const string& getProduse() const;
        int getNrProduse();
        double getTotal();
        void setDiscount(double disc);
        virtual ~Comanda();
};

class comenziMenu{
    private:
        vector<Comanda*> comenzi;
        static comenziMenu* instance;
        map<string,map<string,double>> productData;

        comenziMenu();
    public:
        static comenziMenu* getInstance();
        void addOrder();
        void displayAllOrders();
        void displayAllOrdersByCity();
        void calculateTotalByCity();
        void MenuForOrders();
        static void destroyInstance();
        ~comenziMenu();

        double calculateDiscount(const string& nume, const string& prenume);
};


#endif