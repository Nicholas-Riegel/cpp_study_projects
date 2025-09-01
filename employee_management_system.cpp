#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Employee struct
struct Employee {
    string name;
    int age;
};

// Get int helper function 
// Returns -1 if invalid input
int getInt(){

    string input;
    int result;
    getline(cin, input);
    
    try {
        result = stoi(input);
        return result;
    } catch(...){
        cout << "Invalid input." << endl;
        return -1;
    }
}

// Create employee
void addEmployee(vector<Employee>& vect){
    
    Employee emp;
    string empName;
    int empAge;

    cout << "Enter employee's name" << endl;
    getline(cin, empName);
    
    cout << "Enter employee's age" << endl;
    empAge = getInt();
    while (empAge < 0 || empAge > 150) {
        cout << "Invalid age. Please enter a number between 0-150: ";
        empAge = getInt();
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

    // Get employee's name
    cout << "Please enter the employee's name" << endl;
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

    string answer;
    string newName;
    int newAge;
    
    cout << "Choose option" << endl;
    cout << "1. Update name" << endl;
    cout << "2. Update age" << endl;
    getline(cin, answer);

    if (answer == "1"){
        
        // Get employee's new age
        cout << "Enter employee's new name" << endl;
        getline(cin, newName);
        
        // Update employee's name
        for (Employee& e : vect) {
            if (e.name == empName) {
                e.name = newName;
                cout << "Employee updated." << endl;
                return;
            }
        }

    } else if (answer == "2"){
        
        // Get employee's new age
        cout << "Enter employee's new age" << endl;
        newAge = getInt();
        while (newAge < 0 || newAge > 150) {
            cout << "Invalid age. Please enter a number between 0-150: ";
            newAge = getInt();
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
        getline(cin, answer);

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