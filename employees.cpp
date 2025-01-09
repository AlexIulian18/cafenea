#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "employees.h"
#include "Files.h"

using namespace std;


Employee::Employee(const string& fn, const string& ln, const string& jb, const string& sT, const string& eT, int nr,  const string& wDays)
    : firstName(fn), lastName(ln), job(jb), startTime(sT), endTime(eT), nrOfDays(nr), workDays(wDays){
}
string Employee::getLastName() const {
    return lastName;
}
string Employee::getFirstName() const {
    return firstName;
}
void Employee::displayInfo() const{
        cout << job << ": " << lastName << " " << firstName << endl;
        cout << "Program de lucru: " << startTime << " - " << endTime << endl;
        cout << "Numarul de zile lucrate: " << nrOfDays << endl;
        cout << "Zilele de lucru: " << workDays << endl;
        cout << "\n--------------------------------------------\n";
}
void Employee::displayRoleDescription(){
    cout << roleDescription << endl;
}
Employee::~Employee(){
    cout << "Destructor angajat/employee\n";
}

Manager::Manager(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const string& wDays)
    : Employee(fn, ln, "Manager", sT, eT,nr, wDays) {
}

void Manager::displayInfo() const{
    Employee::displayInfo();
}

void Manager::displayRoleDescription() {
    roleDescription = "Coordoneaza echipa si gestioneaza operatiunile generale.";
    cout << roleDescription << endl;
}

Manager::~Manager() {
    cout << "Destructor manager\n";
}
    
Waiter::Waiter(const string& fn, const string& ln, const string& sT, const string& eT, int nr, const string& wDays)
            : Employee(fn, ln, "Ospatar", sT, eT, nr, wDays) {}
        
        
void Waiter::displayInfo() const{
            Employee::displayInfo();
        }

void Waiter::displayRoleDescription(){
            roleDescription = "Se ocupa de preluarea comenzilor, servirea clientilor si asigurarea unei experiente placute pentru acestia.";
            cout << roleDescription << endl;
        }

Waiter::~Waiter() {
            cout << "Destructor ospatar\n";
        }

Barista::Barista(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const string& wDays)
            : Employee(fn, ln, "Barista", sT, eT, nr, wDays) {}

void Barista::displayInfo() const{
            Employee::displayInfo();
        }

void Barista::displayRoleDescription() {
        roleDescription = "Pregateste bauturi precum cafeaua si ceaiul.";
        cout << roleDescription << endl;
}

Barista::~Barista() {
        cout << "Destructor barista\n";
}

Menu::Menu() {
            try {
                vector<vector<string>> data = readCSV("employee.csv");
                cout << data.size() << " angajati gasiti in baza de date.\n";
                
                for (int j = 1; j < data.size(); j++) {

                    const auto& line = data[j];
                    
                    for(int i = 0; i < line.size(); i++){
                        cout << line[i] << " ";
                    }
                    cout << endl;
                    if (line.size() < 8) continue;

                    string firstName = line[1];
                    string lastName = line[0];
                    string job = line[2];
                    string city = line[3];
                    int nrOfDays = stoi(line[4]);
                    string workDays = line[5];
                    string startTime = line[6];
                    string endTime = line[7];

                    if (job == "Manager") {
                        employees.push_back(new Manager(firstName, lastName, startTime, endTime, nrOfDays, workDays));
                    } else if (job == "Ospatar") {
                        employees.push_back(new Waiter(firstName, lastName, startTime, endTime, nrOfDays, workDays));
                    } else if (job == "Barista") {
                        employees.push_back(new Barista(firstName, lastName, startTime, endTime, nrOfDays, workDays));
                    }
                }
            } catch (const exception& e) {
                cerr << "Eroare: " << e.what() << endl;
            }
}
// Destructor pentru eliberarea memoriei
Menu::~Menu() {
    for (auto employee : employees) {
        delete employee;
    }
}

Menu* Menu::getInstance() {
    if (instance == nullptr) {
        instance = new Menu();
        cout << "S-a creat o instanta pentru prima data a meniului.\n";
    }
    return instance;
}


void Menu::addEmployee() {
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

                cout << "Zilele lucrate (separate prin spatiu + trebuie sa corespunda cu numarul de zile): ";
                getline(cin, workDaysInput);

                cout << "Ora de inceput: ";
                getline(cin, startTime);

                cout << "Ora de sfarsit: ";
                getline(cin, endTime);

                if (job == "Manager") {
                    employees.push_back(new Manager(firstName, lastName, startTime, endTime,  nrOfDays, workDaysInput));
                } else if (job == "Ospatar") {
                    employees.push_back(new Waiter(firstName, lastName, startTime, endTime,  nrOfDays, workDaysInput));
                } else if (job == "Barista") {
                    employees.push_back(new Barista(firstName, lastName, startTime, endTime,  nrOfDays, workDaysInput));
                } else {
                    cerr << "Job invalid! Angajatul nu a fost adaugat.\n";
                    continue; 
                }

                vector<string> row = {lastName, firstName, job, city, to_string(nrOfDays), workDaysInput, startTime, endTime};

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

void Menu::displayAllEmployees() {
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

void Menu::printNumberOfEmployees() {

        int nrOfEmployees = 0;
        nrOfEmployees = Manager::getCount() + Waiter::getCount() + Barista::getCount();
        cout << "Numarul de angajati: " << nrOfEmployees << endl;
}
        
void Menu::displayEmployeeCounts() {
        cout << "Numar de Manageri: " << Counter<Manager>::getCount() << endl;
        cout << "Numar de Ospatari: " << Counter<Waiter>::getCount() << endl;
        cout << "Numar de Barista: "  << Counter<Barista>::getCount() << endl;
}

void Menu::deleteEmployee (const string& lastName, const string& firstName){

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

void Menu::displayRoleDescription() {

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
                cout << "----------------------------------------------\n";
                break;
            }
            case 2:{
                Waiter w("fn", "ln", "08:00", "16:00", 0, {"zile"});
                w.displayRoleDescription();
                cout << "----------------------------------------------\n";
                break;
            }
            case 3:{
                Barista b("fn", "ln", "08:00", "16:00", 0, {"zile"});
                b.displayRoleDescription();
                cout << "----------------------------------------------\n";
                break;
            }
            default:
                cout << "Optiune invalida!\n";
        }
    }

void Menu::destroyInstance() {
    delete instance;
    instance = nullptr;
}

void Menu::employeeMenu(){
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

Menu* Menu::instance = nullptr;