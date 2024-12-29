#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include "Files.h"

using namespace std;

class Employee {
    protected:
        string lastName;
        string firstName;
        string job;
        string startTime;
        string endTime;
        vector<string> workDays;
        int nrOfDays;
        static int nrOfEmployees;
        string roleDescription;

    public:
        Employee(const string& fn, const string& ln, const string& jb, const string& sT, const string& eT, int nr,  const vector<string>& wDays)
            : firstName(fn), lastName(ln), job(jb), startTime(sT), endTime(eT), nrOfDays(nr), workDays(wDays){
            nrOfEmployees++;
        }

        static int getNrOfEmployees() {
            return nrOfEmployees;
        }

        virtual void displayInfo() const = 0;

        virtual void displayRoleDescription() const{
            cout << roleDescription << endl;
        }


        virtual ~Employee(){
            nrOfEmployees--;
        };

};

int Employee::nrOfEmployees = 0;

class Manager : public Employee {
    static int managerCount;
    
    public:
        Manager(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const vector<string>& wDays)
            : Employee(fn, ln, "Manager", sT, eT,nr, wDays) {
                managerCount++;
                roleDescription = "Coordoneaza echipa si gestioneaza operatiunile generale.";
            }

        void displayInfo() const override {
            cout << "Manager: " << lastName << " " << firstName << endl;
            cout << "Job: " << job << endl;

            cout << "Program de lucru: " << startTime << " - " << endTime << endl;
            cout << "Numarul de zile lucrate: " << nrOfDays << endl;
            cout << "Zilele de lucru: ";
            
            for(const auto& day : workDays){
                cout << day << " ";
            }
            cout << "\n";
            cout << "--------------------------------------------" << endl;
            
            
        }

        static int getManagerCount() {
            return managerCount;
        }

        void displayRoleDescription() {
            cout << roleDescription << endl;
        }

        ~Manager() {
            managerCount--;
        }
};

int Manager::managerCount = 0;

class Waiter : public Employee {
    static int waiterCount;
    
    public:
        Waiter(const string& fn, const string& ln, const string& sT, const string& eT, int nr, const vector<string>& wDays)
            : Employee(fn, ln, "Ospatar", sT, eT, nr, wDays) {
                waiterCount++;
                roleDescription = "Se ocupa de preluarea comenzilor, servirea clientilor si asigurarea unei experiente placute pentru acestia.";
            }

        void displayInfo() const override {
            cout << "Ospatar: " << lastName << " " << firstName << endl;
            cout << "Job: " << job << endl;

            cout << "Program de lucru: " << startTime << " - " << endTime << endl;

            cout << "Numarul de zile lucrate: " << nrOfDays << endl;
            cout << "Zilele de lucru: ";
            
            for(const auto& day : workDays){
                cout << day << " ";
            }
            cout << "\n";
            cout << "--------------------------------------------" << endl;

        }

        static int getWaiterCount() {
            return waiterCount;
        }

        void displayRoleDescription() {
            cout << roleDescription << endl;
        }

        ~Waiter() {
            waiterCount--;
        }
};

int Waiter::waiterCount = 0;

class Barista : public Employee {

    static int baristaCount;

    public:
        Barista(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const vector<string>& wDays)
            : Employee(fn, ln, "Barista", sT, eT, nr, wDays) {
                    baristaCount++;
                    roleDescription = "Pregateste bauturi precum cafeaua si ceaiul.";
            }

        void displayInfo() const override {
            cout << "Barista: " << lastName << " " << firstName << endl;
            cout << "Job: " << job << endl;
            
            if (!startTime.empty() && !endTime.empty()) {
                cout << "Program de lucru: " << startTime << " - " << endTime << endl;
            } else {
                cout << "Programul de lucru nu este setat corect.\n";
            }

            cout << "Numarul de zile lucrate: " << nrOfDays << endl;
            cout << "Zilele de lucru: ";
            
            for(const auto& day : workDays){
                cout << day << " ";
            }
            cout << "\n";
            cout << "--------------------------------------------" << endl;
        }

        static int getBaristaCount() {
            return baristaCount;
        }

        void displayRoleDescription() {
            cout << roleDescription << endl;
        }

        ~Barista() {
            baristaCount--;
        }
};

int Barista::baristaCount = 0;

class Menu {
    vector<Employee*> employees;

public:
    Menu() {
        try {
            vector<vector<string>> data = readCSV("employee.csv");

            for (const auto& line : data) {
                if (line.size() < 8) continue;

                string firstName = line[0];
                string lastName = line[1];
                string job = line[2];
                string city = line[3];
                int nrOfDays = stoi(line[4]);
                vector<string> workDays = splitString(line[5], ',');
                string startTime = line[6];
                string endTime = line[7];

                if (job == "Manager") {
                    employees.push_back(new Manager(firstName, lastName,startTime, endTime,nrOfDays, workDays));
                } else if (job == "Ospatar") {
                    employees.push_back(new Waiter(firstName, lastName, startTime, endTime,nrOfDays, workDays));
                } else if (job == "Barista") {
                    employees.push_back(new Barista(firstName, lastName, startTime, endTime,nrOfDays, workDays));
                }
            }
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
        }
    }

    ~Menu() {
        for (auto employee : employees) {
            delete employee;
        }
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
                int nrOfDays;

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

                cout << "Zilele lucrate (separate prin virgula): ";
                getline(cin, workDaysInput);
                vector<string> workDays = splitString(workDaysInput, ',');

                if (workDays.size() != nrOfDays) {
                    cerr << "Eroare: Numarul zilelor lucrate nu corespunde cu zilele introduse.\n";
                    continue;
                }

                cout << "Ora de inceput: ";
                getline(cin, startTime);

                cout << "Ora de sfarsit: ";
                getline(cin, endTime);

                if (job == "Manager") {
                    employees.push_back(new Manager(firstName, lastName, startTime, endTime,  nrOfDays, workDays));
                } else if (job == "Ospatar") {
                    employees.push_back(new Waiter(firstName, lastName, startTime, endTime,  nrOfDays, workDays));
                } else if (job == "Barista") {
                    employees.push_back(new Barista(firstName, lastName, startTime, endTime,  nrOfDays, workDays));
                } else {
                    cerr << "Job invalid! Angajatul nu a fost adaugat.\n";
                    continue;
                }

                vector<string> row = {"\n",lastName, firstName, job, city, to_string(nrOfDays), workDaysInput, startTime, endTime};

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
        for (auto employee : employees) {
            employee->displayInfo();
            cout << "----------------------------------------------\n";
        }
    }

    void printNumberOfEmployees() {
        cout << "Numarul de angajati: " << Employee::getNrOfEmployees() << endl;
    }

    void displayEmployeeCounts() {
        cout << "Numar de Manageri: " << Manager::getManagerCount() << endl;
        cout << "Numar de Ospatari: " << Waiter::getWaiterCount() << endl;
        cout << "Numar de Barista: " << Barista::getBaristaCount() << endl;
    }
    
    void deleteEmployee (const string& lastName, const string& firstName){
        vector<vector<string>> data = readCSV("employee.csv");
        vector<vector<string>> updateData;

        bool found = false;
        for(const auto& line : data){
            if(line[0] == lastName && line[1] == firstName){
                found = true;
                continue;
            }
            updateData.push_back(line);
        }

        if(found){
            writeCSV("employee.csv", updateData, true);
            cout << "Angajatul " << lastName << " " << firstName << " a fost sters cu succes!\n";
        } else {
            cout << "Angajatul " << lastName << " " << firstName << " nu a fost gasit in baza de date!\n";
        }
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
                Manager m("fn", "ln", "08:00", "16:00", 0, {"zile"});
                m.displayRoleDescription();
                break;
            }
            case 2:{
                Waiter w("fn", "ln", "08:00", "16:00", 0, {"zile"});
                w.displayRoleDescription();
                break;
            }
            case 3:{
                Barista b("fn", "ln", "08:00", "16:00", 0, {"zile"});
                b.displayRoleDescription();
                break;
            }
            default:
                cout << "Optiune invalida!\n";
        }
    }
};



int main(){
    
    Menu menu;
    
    int choice;
    int choiceForRole;

    cout << "Bine ati venit la Cafenea!\n";
    cout << "Alegeti o optiune:\n";

    do{
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
                menu.printNumberOfEmployees();
                break;
            case 2:
                menu.addEmployee();
                break;
            case 3:{
                string nume, prenume;
                cout << "Introduceti numele si prenumele angajatului pe care doriti sa il stergeti: ";
                cin >> nume >> prenume;
                menu.deleteEmployee(nume, prenume);
                break;
            }
            case 4:
                menu.displayAllEmployees();
                break;
            case 5:
                menu.displayEmployeeCounts();
                break;
            case 6:
                menu.displayRoleDescription();
                break;
            case 0:
                cout << "La revedere!\n";
                break;
            default:
                cout << "Optiune invalida!\n";
        }
    }while(choice != 0);
    
    return 0;
}