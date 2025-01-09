#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

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
    Employee(const string& fn, const string& ln, const string& jb, 
             const string& sT, const string& eT, int nr, const string& wDays);
    virtual ~Employee();

    string getLastName() const;
    string getFirstName() const;

    virtual void displayInfo() const;
    virtual void displayRoleDescription();
};

class Manager : public Employee, public Counter<Manager> {
public:
    Manager(const string& fn, const string& ln, const string& sT, 
            const string& eT, int nr, const string& wDays);
    ~Manager();

    void displayInfo() const override;
    void displayRoleDescription() override;
};

class Waiter : public Employee, public Counter<Waiter> {
public:
    Waiter(const string& fn, const string& ln, const string& sT, 
           const string& eT, int nr, const string& wDays);
    ~Waiter();

    void displayInfo() const override;
    void displayRoleDescription() override;
};

class Barista : public Employee, public Counter<Barista> {
public:
    Barista(const string& fn, const string& ln, const string& sT, 
            const string& eT, int nr, const string& wDays);
    ~Barista();

    void displayInfo() const override;
    void displayRoleDescription() override;
};

class Menu{
    private:
        vector<Employee*> employees;
        static Menu* instance;

        Menu();

    public:

        static Menu* getInstance();
        void addEmployee();
        void displayAllEmployees();
        void printNumberOfEmployees();
        void displayEmployeeCounts();
        void deleteEmployee (const string& lastName, const string& firstName);
        void displayRoleDescription();
        static void destroyInstance();
        void employeeMenu();
        ~Menu();
};

#endif // FILES_H