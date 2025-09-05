#include "employee.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Write vector to db file and clear
void writeVectorToFileAndClear(std::vector<Employee>& vect){
    std::ofstream db("employees.csv");
    for (const Employee& e : vect){
        db 
        << e.id << "," 
        << e.name << "," 
        << e.age << "," 
        << e.salary << std::endl;
    } 
	db.close();
    vect.clear();
}

// Convert line to Employee helper function
Employee lineToEmployee(const std::string& line){
    
    Employee emp;
    std::vector<std::string> employeeParts;
    
    std::stringstream ss(line);
    std::string item;
    
    while (std::getline(ss, item, ',')) {
        employeeParts.push_back(item);
    }
    emp.id = std::stoi(employeeParts.at(0));
    emp.name = employeeParts.at(1);
    emp.age = std::stoi(employeeParts.at(2));
    emp.salary = std::stoi(employeeParts.at(3));
    
    return emp;
}

// Read db file to vector
void readFileToVector(std::vector<Employee>& vect){
    
    std::string line;
    Employee emp;
    
    std::ifstream db("employees.csv");
    while (std::getline(db, line))
    {
        emp = lineToEmployee(line);
        vect.push_back(emp);
    }
    
    db.close();
}

// Get int helper function 
// Returns -1 if invalid input
int getIntOrNegativeOne(){

    std::string input;
    int result;

    std::getline(std::cin, input);
    try {
        result = std::stoi(input);
        return result;
    } catch(...){
        return -1;
    }
}

// Get largest id for new employee
int getNextId(const std::vector<Employee>& vect) {
    
    if (vect.empty()) return 1;
    
    int maxId = 0;
    
    for (const Employee& e : vect) {
        if (e.id > maxId) {
            maxId = e.id;
        }
    }
    
    return maxId + 1;
}

// Create/add employee
void addEmployee(std::vector<Employee>& vect){
    
    Employee emp;
    std::string empName;
    int empAge;
    int empSalary;

    std::cout << "Enter employee's name" << std::endl;
    std::getline(std::cin, empName);
    
    std::cout << "Enter employee's age" << std::endl;
    empAge = getIntOrNegativeOne();
    while (empAge < EmployeeValidation::MIN_AGE || empAge > EmployeeValidation::MAX_AGE) {
        std::cout << "Invalid age. Please enter a number between " 
                  << EmployeeValidation::MIN_AGE << "-" 
                  << EmployeeValidation::MAX_AGE << std::endl;
        empAge = getIntOrNegativeOne();
    }
    
    std::cout << "Enter employee's salary" << std::endl;
    empSalary = getIntOrNegativeOne();
    while (empSalary < EmployeeValidation::MIN_SALARY) {
        std::cout << "Invalid salary. Please enter a number greater than " 
                  << EmployeeValidation::MIN_SALARY << std::endl;
        empSalary = getIntOrNegativeOne();
    }
    
    readFileToVector(vect);
    
    emp.id = getNextId(vect);
    emp.name = empName;
    emp.age = empAge;
    emp.salary = empSalary;

    vect.push_back(emp);
    
    writeVectorToFileAndClear(vect);
}

// Print employees
void printEmployees(std::vector<Employee>& vect){
    
    readFileToVector(vect);
    
    std::cout << "=====================" << std::endl;
    std::cout << "Employees" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "Id Name Age Salary" << std::endl;
    std::cout << "---------------------" << std::endl;
    for (Employee& e : vect){
        std::cout 
        << e.id << " " 
        << e.name << " " 
        << e.age << " " 
        << e.salary << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    
    vect.clear();
}

// Check if employee id exists
bool employeeExists(const std::vector<Employee>& vect, int empId){
    bool employeeExists = false; 
    for (const Employee& e : vect) {
        if (e.id == empId) {
            employeeExists = true;
            break;
        }
    }
    return employeeExists;
}

// Delete employees
void deleteEmployee(std::vector<Employee>& vect){

    // Get employee id
    int empId;

    std::cout << "Please enter the employee's id" << std::endl;
    empId = getIntOrNegativeOne();

    if (empId < EmployeeValidation::INVALID_ID){
        std::cout << "Invalid input" << std::endl;
        return;
    }

    readFileToVector(vect);

    if (!employeeExists(vect, empId)){
        vect.clear();
        std::cout << "Employee not found." << std::endl;
        return;
    }

    for (auto it = vect.begin(); it != vect.end();){
        if (it->id == empId) {
            it = vect.erase(it);
            std::cout << "Employee deleted." << std::endl;
            writeVectorToFileAndClear(vect);
            return;
        } else {
            ++it;
        }
    }

    vect.clear();
}

// update helper function
void update(
    std::vector<Employee>& vect, 
    int empId, 
    EmployeeField empField, 
    std::string stringValue, 
    int intValue
){
    for (Employee& e : vect) {
        if (e.id == empId) {
            switch (empField) {
                case EmployeeField::NAME:
                    e.name = stringValue;
                    break;
                case EmployeeField::AGE:
                    e.age = intValue;
                    break;
                case EmployeeField::SALARY:
                    e.salary = intValue;
                    break;
            }
            writeVectorToFileAndClear(vect);
            std::cout << "Employee updated." << std::endl;
            return;
        }
    }
}

// Edit employee
void editEmployee(std::vector<Employee>& vect){
    
    // Get employee id
    int empId;
    std::string option;
    std::string newName;
    int newAge;
    int newSalary;
    
    // Get employee id
    std::cout << "Please enter the employee's id" << std::endl;
    empId = getIntOrNegativeOne();
    
    // Check if employee exists
    if (empId < EmployeeValidation::INVALID_ID){
        std::cout << "Invalid input" << std::endl;
        return;
    }

    // Load the vector
    readFileToVector(vect);

    if (!employeeExists(vect, empId)){
        vect.clear();
        std::cout << "Employee not found." << std::endl;
        return;
    }
    
    // Get user's option
    std::cout << "Choose option" << std::endl;
    std::cout << "1. Update name" << std::endl;
    std::cout << "2. Update age" << std::endl;
    std::cout << "3. Update salary" << std::endl;
    std::getline(std::cin, option);

    if (option == "1"){
        
        // Get employee's new name
        std::cout << "Enter employee's new name" << std::endl;
        std::getline(std::cin, newName);
        
        update(vect, empId, EmployeeField::NAME, newName, 0);

    } else if (option == "2"){
        
        // Get employee's new age
        std::cout << "Enter employee's new age" << std::endl;
        newAge = getIntOrNegativeOne();
        while (newAge < EmployeeValidation::MIN_AGE || newAge > EmployeeValidation::MAX_AGE) {
            std::cout << "Invalid age. Please enter a number between " 
                      << EmployeeValidation::MIN_AGE << "-" 
                      << EmployeeValidation::MAX_AGE << std::endl;
            newAge = getIntOrNegativeOne();
        }
        
        update(vect, empId, EmployeeField::AGE, "", newAge);

    } else if (option == "3"){
        
        // Get employee's new salary≠≠
        std::cout << "Enter employee's new salary" << std::endl;
        newSalary = getIntOrNegativeOne();
        while (newSalary < EmployeeValidation::MIN_SALARY) {
            std::cout << "Invalid salary. Please enter a number greater than " 
                      << EmployeeValidation::MIN_SALARY << std::endl;
            newSalary = getIntOrNegativeOne();
        }
        
        update(vect, empId, EmployeeField::SALARY, "", newSalary);
        
    } else {
        vect.clear();
    }
}