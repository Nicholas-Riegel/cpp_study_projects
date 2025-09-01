#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Employee struct
struct Employee {
    string name;
    int age;
};

// Create employee
void addEmployee(vector<Employee>& vect){
    
    Employee emp;
    string empName;
    int empAge;

    cout << "Enter employee's name" << endl;
    cin.ignore();
    getline(cin, empName);
    
    cout << "Enter employee's age" << endl;
    while (!(cin >> empAge) || empAge < 0 || empAge > 150) {
        cout << "Invalid age. Please enter a number between 0-150: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    emp.name = empName;
    emp.age = empAge;

    vect.push_back(emp);
}

// Print employees
void printEmployees(vector<Employee>& vect){
    cout << "=========" << endl;
    cout << "Employees" << endl;
    cout << "=========" << endl;
    for (Employee e : vect){
        cout << e.name << " " << e.age << endl;
    }
    cout << "=========" << endl;
}

// Delete employees
void deleteEmployee(vector<Employee>& vect){
    
    string empName;

    cout << "Please enter the employee's name" << endl;
    cin.ignore();
    getline(cin, empName);

    for (auto it = vect.begin(); it != vect.end();){
        if (it->name == empName) {
            it = vect.erase(it);
            cout << "Employee deleted." << endl;
            return;
        } else {
            ++it;
        }
    }
    cout << "Employee not found." << endl;
}

// Edit employee
void editEmployee(vector<Employee>& vect){
    
    string empName;
    int newAge;

    // Get employee's name
    cout << "Please enter the employee's name" << endl;
    cin.ignore();
    getline(cin, empName);

    // Check if employee exists
    bool found = false;
    for (Employee& e : vect){
        if (e.name == empName){
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found" << endl;
        return;
    }

    // Get employee's new age
    cout << "Enter employee's new age" << endl;
    while (!(cin >> newAge) || newAge < 0 || newAge > 150) {
        cout << "Invalid age. Please enter a number between 0-150: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Update employee's age
    for (Employee& e : vect) {
        if (e.name == empName) {
            e.age = newAge;
            cout << "Employee updated." << endl;
            return;
        }
    }
}

// Main function
int main(){
    
    // Main vector
    vector<Employee> employees;

    // Add some dummy employees
    Employee emp1, emp2;
    emp1.name = "John"; emp1.age = 33; employees.push_back(emp1);
    emp2.name = "Fred"; emp2.age = 35; employees.push_back(emp2);

    // User choice
    string answer;

    cout << "==========================" << endl;
    cout << "Employee Management System" << endl;
    cout << "==========================" << endl;
    
    while (true){

        cout << endl;
        cout << "Choose an option" << endl;
        cout << "1. Show employees" << endl;
        cout << "2. Add an employee" << endl;
        cout << "3. Delete an employee" << endl;
        cout << "4. Edit an employee" << endl;
        cout << "Or type \"exit\"" << endl;
        cin >> answer;

        if (answer == "exit"){
            break;
        } else if (answer == "1"){
            printEmployees(employees);
        } else if (answer == "2"){
            addEmployee(employees);
        } else if (answer == "3"){
            deleteEmployee(employees);
        } else if (answer == "4"){
            editEmployee(employees);
        }
    }

    cout << "Goodbye!" << endl;
    
    return 0;
}