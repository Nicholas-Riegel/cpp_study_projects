#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Employee struct
struct Employee {
    int id;
    std::string name;
    int age;
    int salary;
};

// Write vector to db file and clear
void writeVectorToFileAndClear(std::vector<Employee>& vect){
    std::ofstream db("employees.csv");
    for (Employee& e : vect){
        db << e.id << "," << e.name << "," << e.age << "," << e.salary << std::endl;
    } 
	db.close();
    vect.clear();
}

// Convert line to Employee helper function
Employee lineToEmployee(std::string& line){
    
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
int getInt(){

    std::string input;
    int result;

    std::getline(std::cin, input);
    try {
        result = std::stoi(input);
        return result;
    } catch(...){
        std::cout << "Invalid input." << std::endl;
        return -1;
    }
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
    empAge = getInt();
    while (empAge < 0 || empAge > 150) {
        std::cout << "Invalid age. Please enter a number between 0-150: ";
        empAge = getInt();
    }
    
    std::cout << "Enter employee's salary" << std::endl;
    empSalary = getInt();
    while (empSalary < 0) {
        std::cout << "Invalid salary. Please enter a number greater than 0: ";
        empSalary = getInt();
    }
    
    readFileToVector(vect);
    
    emp.id = vect.size() + 1;
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
    for (Employee e : vect){
        std::cout << e.id << " " << e.name << " " << e.age << " " << e.salary << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    
    vect.clear();
}

// Delete employees
void deleteEmployee(std::vector<Employee>& vect){

    // Get employee id
    int empId;
    std::string empIdStr;

    std::cout << "Please enter the employee's id" << std::endl;
    std::getline(std::cin, empIdStr);
    try {
        empId = std::stoi(empIdStr);
    } catch (...) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    readFileToVector(vect);

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
    std::cout << "Employee not found." << std::endl;
}

// Edit employee
void editEmployee(std::vector<Employee>& vect){
    
    // Get employee id
    int empId;
    std::string empIdStr;

    std::cout << "Please enter the employee's id" << std::endl;
    std::getline(std::cin, empIdStr);
    try {
        empId = std::stoi(empIdStr);
    } catch (...) {
        std::cout << "Invalid input." << std::endl;
        return;
    }

    std::string option;
    std::string newName;
    int newAge;
    int newSalary;
    
    // Load the vector
    readFileToVector(vect);

    // Get user's option
    std::cout << "Choose option" << std::endl;
    std::cout << "1. Update name" << std::endl;
    std::cout << "2. Update age" << std::endl;
    std::cout << "3. Update salary" << std::endl;
    std::getline(std::cin, option);

    if (option == "1"){
        
        // Get employee's new age
        std::cout << "Enter employee's new name" << std::endl;
        std::getline(std::cin, newName);
        
        // Update employee's name
        for (Employee& e : vect) {
            if (e.id == empId) {
                e.name = newName;
                writeVectorToFileAndClear(vect);
                std::cout << "Employee updated." << std::endl;
                return;
            }
        }

    } else if (option == "2"){
        
        // Get employee's new age
        std::cout << "Enter employee's new age" << std::endl;
        newAge = getInt();
        while (newAge < 0 || newAge > 150) {
            std::cout << "Invalid age. Please enter a number between 0-150: ";
            newAge = getInt();
        }
        
        // Update employee's age
        for (Employee& e : vect) {
            if (e.id == empId) {
                e.age = newAge;
                writeVectorToFileAndClear(vect);
                std::cout << "Employee updated." << std::endl;
                return;
            }
        }
    } else if (option == "3"){
        
        // Get employee's new age
        std::cout << "Enter employee's new salary" << std::endl;
        newSalary = getInt();
        while (newSalary < 0) {
            std::cout << "Invalid salary. Please enter a number greater than 0: ";
            newSalary = getInt();
        }
        
        // Update employee's salary
        for (Employee& e : vect) {
            if (e.id == empId) {
                e.salary = newSalary;
                writeVectorToFileAndClear(vect);
                std::cout << "Employee updated." << std::endl;
                return;
            }
        }
    }
}

// Main function
int main(){
    
    // Main vector
    std::vector<Employee> employees;

    // Add some dummy employees
    Employee emp1 = {.id = 1, .name = "John", .age = 33, .salary = 83000}; 
    Employee emp2 = {.id = 2, .name = "Fred", .age = 35, .salary = 75000};
     
    employees.push_back(emp1);
    employees.push_back(emp2);

    // Write vector to file and clear
    writeVectorToFileAndClear(employees);

    // User choice
    std::string answer;

    std::cout << "==========================" << std::endl;
    std::cout << "Employee Management System" << std::endl;
    std::cout << "==========================" << std::endl;
    
    while (true){

        std::cout << std::endl;
        std::cout << "Choose an option" << std::endl;
        std::cout << "1. Show employees" << std::endl;
        std::cout << "2. Add an employee" << std::endl;
        std::cout << "3. Delete an employee" << std::endl;
        std::cout << "4. Edit an employee" << std::endl;
        std::cout << "Or type \"exit\"" << std::endl;
        std::getline(std::cin, answer);

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

    std::cout << "Goodbye!" << std::endl;
    
    return 0;
}