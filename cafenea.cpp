#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include "Files.h"
#include "produse.h"
#include "comenzi.h"
#include "events.h"

using namespace std;

template <typename T>
class Counter {
    static int count;
public:
    Counter() { count++; }
    ~Counter() {
        count--; }
    static int getCount() { return count; }
};
template <typename T>
int Counter<T>::count = 0;

class Employee {
    protected:
        string lastName;
        string firstName;
        string job;
        string startTime;
        string endTime;
        string workDays;
        int nrOfDays;
        string roleDescription;
        int salary;

    public:
        Employee(const string& fn, const string& ln, const string& jb, const string& sT, const string& eT, int nr,  const string& wDays, int sal)
            : firstName(fn), lastName(ln), job(jb), startTime(sT), endTime(eT), nrOfDays(nr), workDays(wDays), salary(sal){
        }

        string getLastName() const {
            return lastName;
        }

        string getFirstName() const {
            return firstName;
        }

        virtual void displayInfo() const{
            cout << job << ": " << lastName << " " << firstName << endl;
            cout << "Program de lucru: " << startTime << " - " << endTime << endl;
            cout << "Numarul de zile lucrate: " << nrOfDays << endl;
            cout << "Zilele de lucru: " << workDays << endl;
            cout << "Salariu: " << salary << " RON\n";
            cout << "\n--------------------------------------------\n";
        }

        virtual void displayRoleDescription() const{
            cout << roleDescription << endl;
        }
        virtual ~Employee(){
        };

};
class Manager : public Employee, public Counter<Manager> {
    
    public:
        Manager(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const string& wDays, int sal)
            : Employee(fn, ln, "Manager", sT, eT,nr, wDays,sal) {
            }

        void displayInfo() const override {
            Employee::displayInfo();
        }

        void displayRoleDescription() {
            roleDescription = "Coordoneaza echipa si gestioneaza operatiunile generale.";
            cout << roleDescription << endl;
        }

        ~Manager() {
        }
};
class Waiter : public Employee, public Counter<Waiter> {
    
    public: 
        Waiter(const string& fn, const string& ln, const string& sT, const string& eT, int nr, const string& wDays,int sal)
            : Employee(fn, ln, "Ospatar", sT, eT, nr, wDays,sal) {}
        void displayInfo() const override {
            Employee::displayInfo();
        }

        void displayRoleDescription() {
            roleDescription = "Se ocupa de preluarea comenzilor, servirea clientilor si asigurarea unei experiente placute pentru acestia.";
            cout << roleDescription << endl;
        }

        ~Waiter() {
        }
};
class Barista : public Employee, public Counter<Barista> {

    public:
        Barista(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const string& wDays,int sal)
            : Employee(fn, ln, "Barista", sT, eT, nr, wDays,sal) {}

        void displayInfo() const override {
            Employee::displayInfo();
        }

        void displayRoleDescription() {
            roleDescription = "Pregateste bauturi precum cafeaua si ceaiul.";
            cout << roleDescription << endl;
        }

        ~Barista() {
        }
};

//Singleton
class Menu {
    private:
        vector<Employee*> employees;
        static Menu* instance;

        // Constructor privat
        Menu() {
            try {
                vector<vector<string>> data = readCSV("employee.csv");
                cout << data.size() << " angajati gasiti in baza de date.\n";
                
                for (int j = 1; j < data.size(); j++) {

                    const auto& line = data[j];
                    if (line.size() < 9) continue;

                    string firstName = line[1];
                    string lastName = line[0];
                    string job = line[2];
                    string city = line[3];
                    int nrOfDays = stoi(line[4]);
                    string workDays = line[5];
                    string startTime = line[6];
                    string endTime = line[7];
                    int salary = stoi(line[8]);

                    if (job == "Manager") {
                        employees.push_back(new Manager(firstName, lastName, startTime, endTime, nrOfDays, workDays,salary));
                    } else if (job == "Ospatar") {
                        employees.push_back(new Waiter(firstName, lastName, startTime, endTime, nrOfDays, workDays,salary));
                    } else if (job == "Barista") {
                        employees.push_back(new Barista(firstName, lastName, startTime, endTime, nrOfDays, workDays,salary));
                    }
                }
            } catch (const exception& e) {
                cerr << "Eroare: " << e.what() << endl;
            }
        }
        // Destructor pentru eliberarea memoriei
        ~Menu() {
            for (auto employee : employees) {
                delete employee;
            }
        }

    public:

        static Menu* getInstance() {
            if (instance == nullptr) {
                instance = new Menu();
                cout << "S-a creat o instanta pentru prima data a meniului.\n";
            }
            return instance;
        }
        void addEmployee() {
            try {
                cout << "Introduceti nr de angajati pe care doriti sa ii adaugati: ";
                int n;
                cin >> n;
                cin.ignore();
                vector<vector<string>> newData;

            for (int i = 0; i < n; ++i) {
                cout << "Introduceti datele pentru angajatul " << i + 1 << ":\n";

                string lastName, firstName, job, city, workDaysInput, startTime, endTime;
                int nrOfDays, salary;

                cout << "Nume: ";
                getline(cin, lastName);
                lastName = capitalizeWords(lastName);

                cout << "Prenume: ";
                getline(cin, firstName);
                firstName = capitalizeWords(firstName);

                cout << "Job: ";
                getline(cin, job);
                job = capitalizeWords(job);

                cout << "Oras: ";
                getline(cin, city);
                city = capitalizeWords(city);

                cout << "Numarul de zile lucrate: ";
                cin >> nrOfDays;
                cin.ignore();

                cout << "Zilele lucrate (separate prin spatiu + trebuie sa corespunda cu numarul de zile): ";
                getline(cin, workDaysInput);

                cout << "Ora de inceput: ";
                getline(cin, startTime);

                cout << "Ora de sfarsit: ";
                getline(cin, endTime);

                cout << "Salariu: ";
                cin >> salary;
                cin.ignore();

                if (job == "Manager") {
                    employees.push_back(new Manager(firstName, lastName, startTime, endTime,  nrOfDays, workDaysInput,salary));
                } else if (job == "Ospatar") {
                    employees.push_back(new Waiter(firstName, lastName, startTime, endTime,  nrOfDays, workDaysInput,salary));
                } else if (job == "Barista") {
                    employees.push_back(new Barista(firstName, lastName, startTime, endTime,  nrOfDays, workDaysInput,salary));
                } else {
                    cerr << "Job invalid! Angajatul nu a fost adaugat.\n";
                    continue; 
                }

                vector<string> row = {lastName, firstName, job, city, to_string(nrOfDays), workDaysInput, startTime, endTime,to_string(salary)};

                // Verifică datele introduse
                cout << "Randul adaugat: ";
                for (const auto& field : row) {
                    cout << field << " ";
                }
                cout << endl;

                newData.push_back(row);
            }

            writeCSV("employee.csv", newData, true);
            cout << "Fisierul a fost actualizat cu succes!" << endl;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
        }
    }
        void displayAllEmployees() {
            try {
                vector<vector<string>> data = readCSV("employee.csv"); // Recitește fișierul
                if (data.empty()) {
                    cout << "Nu exista angajati în baza de date.\n";
                    return;
                }

                cout << "Angajatii existenti sunt:\n";
                for (const auto& line : data) {
                    for (const auto& field : line) {
                        cout << field << " ";
                    }
                    cout << endl;
                }
            } catch (const exception& e) {
                cerr << "Eroare la afișare: " << e.what() << endl;
            }
        }
        void printNumberOfEmployees() {

        int nrOfEmployees = 0;
        nrOfEmployees = Manager::getCount() + Waiter::getCount() + Barista::getCount();
        cout << "Numarul de angajati: " << nrOfEmployees << endl;
    }
        void displayEmployeeCounts() {
        cout << "Numar de Manageri: " << Counter<Manager>::getCount() << endl;
        cout << "Numar de Ospatari: " << Counter<Waiter>::getCount() << endl;
        cout << "Numar de Barista: "  << Counter<Barista>::getCount() << endl;
    }
        void deleteEmployee (const string& lastName, const string& firstName){

            try{
            
                vector<vector<string>> updateData;
                vector<vector<string>> data = readCSV("employee.csv");
                    
                bool found = false;
                for(const auto& line : data){
                    if(line[0] == lastName && line[1] == firstName){
                        found = true;
                        continue;
                    }
                    updateData.push_back(line);
                }
                
                for(int i = 0; i < employees.size(); i++){
                    cout << employees[i]->getLastName() << " " << employees[i]->getFirstName() << endl;
                    if(employees[i]->getLastName() == lastName && employees[i]->getFirstName() == firstName){
                        cout << "Vreau sa ii dau delete\n";
                        delete employees[i];
                        employees.erase(employees.begin() + i);
                        break;
                    }
                }


                if(found){
                    writeCSV("employee.csv", updateData, false);
                    cout << "Angajatul " << lastName << " " << firstName << " a fost sters cu succes!\n";
                } else {
                    cout << "Angajatul " << lastName << " " << firstName << " nu a fost gasit in baza de date!\n";
                }
            }catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;}
        }
        void displayRoleDescription() {

        int choiceForRole;
        cout << "Alegeti un job pentru a vedea descrierea rolului:\n";
        cout << "1. Manager\n";
        cout << "2. Ospatar\n";
        cout << "3. Barista\n";

        cin >> choiceForRole;
        cin.ignore();

        switch(choiceForRole){
            case 1:{
                Manager m("fn", "ln", "08:00", "16:00", 0, {"zile"},0);
                m.displayRoleDescription();
                cout << "----------------------------------------------\n";
                break;
            }
            case 2:{
                Waiter w("fn", "ln", "08:00", "16:00", 0, {"zile"},0);
                w.displayRoleDescription();
                cout << "----------------------------------------------\n";
                break;
            }
            case 3:{
                Barista b("fn", "ln", "08:00", "16:00", 0, {"zile"},0);
                b.displayRoleDescription();
                cout << "----------------------------------------------\n";
                break;
            }
            default:
                cout << "Optiune invalida!\n";
        }
    }
        static void destroyInstance() {
            delete instance;
            instance = nullptr;
        }

        void employeeMenu(){
            int choice;
            cout << "Alegeti o optiune:\n";
            cout << "1. Afiseaza numarul de angajati\n";
            cout << "2. Adauga in lista un angajat\n";
            cout << "3. Sterge din lista un angajat\n";
            cout << "4. Afiseaza toti angajatii\n";
            cout << "5. Afiseaza numarul de oameni care lucreaza pentru fiecare job\n";
            cout << "6. Afiseaza rolurile fiecarui job\n";
            cout << "0. Iesire\n";
            cin >> choice;
            cin.ignore();

            switch(choice){
                case 1:
                    printNumberOfEmployees();
                    break;
                case 2:
                    addEmployee();
                    break;
                case 3:{
                    cout << "Introduceti numarul de angajati pe care doriti sa ii stergeti: ";
                    int n;
                    cin >> n;
                    cin.ignore();

                    string lastName, firstName;

                    for(int i = 0; i < n; ++i){

                        cout << "Introduceti datele pentru angajatul " << i + 1 << ":\n";
                        
                        cout << "Nume: ";
                        getline(cin, lastName);
                        lastName = capitalizeWords(lastName);
                    
                        cout << "Prenume: ";
                        getline(cin, firstName);
                        firstName = capitalizeWords(firstName);

                        deleteEmployee(lastName, firstName);
                    }
                    break;
                }
                case 4:
                    displayAllEmployees();
                    break;
                case 5:
                    displayEmployeeCounts();
                    break;
                case 6:
                    displayRoleDescription();
                    break;
                
                case 0:
                    cout << "La revedere!\n";
                    break;
                default:
                    cout << "Optiune invalida!\n";
            }
        }
};

Menu* Menu::instance = nullptr;

#include <map>

void generateDailyReport() {
    try {
        // Citire date angajați
        vector<vector<string>> employeesData = readCSV("employee.csv");

        // Citire date comenzi
        vector<vector<string>> ordersData = readCSV("orders.csv");

        // Citire produse
        vector<vector<string>> productsData = readCSV("products.csv");

        double totalRevenue = 0.0, totalCost = 0.0, totalSalaries = 0.0;

        // Calcul venituri din comenzi
        for (size_t i = 1; i < ordersData.size(); ++i) {
            totalRevenue += stod(ordersData[i][5]); // Coloana Total
        }

        // Calcul costuri de producție din produse
        map<string, double> productionCosts;
        for (size_t i = 1; i < productsData.size(); ++i) {
            string productName = productsData[i][0];
            double cost = stod(productsData[i][4]); // Coloana Cost de producție
            int sold = stoi(productsData[i][5]);    // Coloana Numar Vandut
            productionCosts[productName] = cost * sold;
            totalCost += productionCosts[productName];
        }

        // Calcul salarii angajați
        for (size_t i = 1; i < employeesData.size(); ++i) {
            totalSalaries += stod(employeesData[i][8]); // Coloana Salariu
        }

        // Generare raport
        ofstream reportFile("financial_report.csv");
        if (reportFile.is_open()) {
            reportFile << "Raport Zilnic Cafenea\n";
            reportFile << "======================\n";
            reportFile << "Venituri totale: " << fixed << setprecision(2) << totalRevenue << " RON\n";
            reportFile << "Costuri produse: " << fixed << setprecision(2) << totalCost << " RON\n";
            reportFile << "Salarii angajați: " << fixed << setprecision(2) << totalSalaries << " RON\n";
            reportFile << "Profit net: " << fixed << setprecision(2) << (totalRevenue - totalCost - totalSalaries) << " RON\n";

            reportFile << "\nCosturi detaliate per produs:\n";
            for (const auto& [product, cost] : productionCosts) {
                reportFile << " - " << product << ": " << cost << " RON\n";
            }

            reportFile.close();
            cout << "Raportul zilnic a fost generat cu succes în 'financial_report.csv'.\n";
        } else {
            cerr << "Nu s-a putut deschide fișierul pentru scrierea raportului.\n";
        }
    } catch (const exception& e) {
        cerr << "Eroare la generarea raportului: " << e.what() << endl;
    }
}


int main(){
    
    Menu* menu = Menu::getInstance();
    produseMenu* produseMenu = produseMenu::getInstance();
    comenziMenu* comenziMenu = comenziMenu::getInstance();
    EvenimenteMenu* EvenimenteMenu = EvenimenteMenu::getInstance();
    
    int alegere;

    cout << "Bine ati venit la Cafenea!\n";
    cout << "Alegeti o optiune:\n";

    do{
        cout << "1. Gestioneaza angajatii\n";
        cout << "2. Gestioneaza produsele\n";
        cout << "3. Gestioneaza comenzile\n";
        cout << "4. Gestioneaza evenimentele\n";
        cout << "5. Genereaza raport zilnic\n";
        cout << "0. Iesire\n";
        cin >> alegere;
        cin.ignore();

        switch(alegere){
            case 1:
                menu->employeeMenu();
                break;
            case 2:
                produseMenu::getInstance()->MenuForProducts();
                break;
            case 3:
                comenziMenu::getInstance()->MenuForOrders();
                break;
            case 4:
                EvenimenteMenu::getInstance()->MenuForEvenimente();
                break;
            case 5:
                generateDailyReport();
                break;
            case 0:
                cout << "La revedere!\n";
                break;
            default:
                cout << "Optiune invalida!\n";
        }

    }while(alegere != 0);
    
    Menu::destroyInstance();
    produseMenu::destroyInstance();
    comenziMenu::destroyInstance();
    EvenimenteMenu::destroyInstance();
    return 0;
}