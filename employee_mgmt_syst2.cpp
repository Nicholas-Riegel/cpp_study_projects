#include "employee.h"
#include <iostream>

// Main function
int main(){
    
    // Main vector 
    std::vector<Employee> employees;

    // User choice
    std::string answer;

    std::cout << "==========================" << std::endl;
    std::cout << "Employee Management System" << std::endl;
    std::cout << "==========================" << std::endl;
    
    while (true){

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