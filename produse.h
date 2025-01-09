#ifndef PRODUSE_H
#define PRODUSE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

// Clasa de bază Produs
class Produs {
protected:
    string nume;
    string categorie;
    string oras;
    double pret;
    double costProductie;
    int stock;
    int nrVandute;

public:
    Produs(const string& nm, const string& ctg, const string& cty, double pr, double cp, int st, int nV);
    virtual void displayInfo() const;
    const string& getNume() const;
    const string& getCategorie() const;
    const string& getOras() const;
    int getNrVandute();
    int getStock();
    double getPret() const;
    double getCostProductie();
    virtual ~Produs();
};

// Clase derivate
class Sandwich : public Produs {
public:
    Sandwich(const string& nm, const string& cty,double prt, double cp, int st, int nV);
    void displayInfo() const override;
    ~Sandwich();
};

class Cafea : public Produs {
public:
    Cafea(const string& nm,const string& cty, double prt, double cp, int st, int nV);
    void displayInfo() const override;
    ~Cafea();
};

class Ceai : public Produs {
public:
    Ceai(const string& nm, const string& cty,double prt, double cp, int st, int nV);
    void displayInfo() const override;
    ~Ceai();
};

class Bauturi : public Produs {
public:
    Bauturi(const string& nm,const string& cty, double prt, double cp, int st, int nV);
    void displayInfo() const override;
    ~Bauturi();
};

class Desert : public Produs {
public:
    Desert(const string& nm, const string& cty,double prt, double cp, int st, int nV);
    void displayInfo() const override;
    ~Desert();
};

// Clasa singleton pentru gestionarea produselor
class produseMenu {
private:
    vector<Produs*> produse;
    static produseMenu* instance;

    produseMenu();

public:
    static produseMenu* getInstance();
    void addProduct();
    void deleteProduct(const string& nume, const string& categorie, const string& oras);
    void displayAllProductsByCity();
    void calculateProfitByCity();
    void searchProductByCategoryandCity(const string& category, const string& name, const string& city);
    void MenuForProducts();
    static void destroyInstance();
    ~produseMenu();
};


map<string, map<string, double>> loadProductData(const string& filename);


#endif