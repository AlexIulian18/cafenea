#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include "Files.h"

using namespace std;

template <typename T>
class Counter {
    static int count;
public:
    Counter() { count++; }
    ~Counter() {
        cout << "Destructor counter\n";
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

    public:
        Employee(const string& fn, const string& ln, const string& jb, const string& sT, const string& eT, int nr,  const string& wDays)
            : firstName(fn), lastName(ln), job(jb), startTime(sT), endTime(eT), nrOfDays(nr), workDays(wDays){
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
            cout << "\n--------------------------------------------\n";
        }

        virtual void displayRoleDescription() const{
            cout << roleDescription << endl;
        }
        virtual ~Employee(){
            cout << "Destructor angajat/employee\n";
        };

};

class Manager : public Employee, public Counter<Manager> {
    
    public:
        Manager(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const string& wDays)
            : Employee(fn, ln, "Manager", sT, eT,nr, wDays) {
            }

        void displayInfo() const override {
            Employee::displayInfo();
        }

        void displayRoleDescription() {
            roleDescription = "Coordoneaza echipa si gestioneaza operatiunile generale.";
            cout << roleDescription << endl;
        }

        ~Manager() {
            cout << "Destructor manager\n";
        }
};

class Waiter : public Employee, public Counter<Waiter> {
    
    public: 
        Waiter(const string& fn, const string& ln, const string& sT, const string& eT, int nr, const string& wDays)
            : Employee(fn, ln, "Ospatar", sT, eT, nr, wDays) {}
        void displayInfo() const override {
            Employee::displayInfo();
        }

        void displayRoleDescription() {
            roleDescription = "Se ocupa de preluarea comenzilor, servirea clientilor si asigurarea unei experiente placute pentru acestia.";
            cout << roleDescription << endl;
        }

        ~Waiter() {
            cout << "Destructor ospatar\n";
        }
};

class Barista : public Employee, public Counter<Barista> {

    public:
        Barista(const string& fn, const string& ln, const string& sT, const string& eT,int nr, const string& wDays)
            : Employee(fn, ln, "Barista", sT, eT, nr, wDays) {}

        void displayInfo() const override {
            Employee::displayInfo();
        }

        void displayRoleDescription() {
            roleDescription = "Pregateste bauturi precum cafeaua si ceaiul.";
            cout << roleDescription << endl;
        }

        ~Barista() {
            cout << "Destructor barista\n";
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

        static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }
};

Menu* Menu::instance = nullptr;

int main(){
    
    Menu* menu = Menu::getInstance();
    
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
                menu->printNumberOfEmployees();
                break;
            case 2:
                menu->addEmployee();
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

                    menu->deleteEmployee(lastName, firstName);
                }
                break;
            }
            case 4:
                menu->displayAllEmployees();
                break;
            case 5:
                menu->displayEmployeeCounts();
                break;
            case 6:
                menu->displayRoleDescription();
                break;
            case 0:
                cout << "La revedere!\n";
                break;
            default:
                cout << "Optiune invalida!\n";
        }
    }while(choice != 0);
    
    Menu::destroyInstance();
    return 0;
}