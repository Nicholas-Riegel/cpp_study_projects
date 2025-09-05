#include <string>
#include <vector>

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

// Employee struct
struct Employee {
    int id;
    std::string name;
    int age;
    int salary;
};

// Write vector to db file and clear
void writeVectorToFileAndClear(std::vector<Employee>& vect);

// Convert line to Employee helper function
Employee lineToEmployee(const std::string& line);

// Read db file to vector
void readFileToVector(std::vector<Employee>& vect);

// Get int helper function 
// Returns -1 if invalid input
int getIntOrNegativeOne();

// Get largest id for new employee
int getNextId(const std::vector<Employee>& vect);

// Create/add employee
void addEmployee(std::vector<Employee>& vect);

// Print employees
void printEmployees(std::vector<Employee>& vect);

// Check if employee id exists
bool employeeExists(const std::vector<Employee>& vect, int empId);

// Delete employees
void deleteEmployee(std::vector<Employee>& vect);

// enum class for update helper function
enum class EmployeeField {
    NAME,
    AGE, 
    SALARY
};

// update helper function
void update(
    std::vector<Employee>& vect, 
    int empId, 
    EmployeeField empField, 
    std::string stringValue, 
    int intValue
);

// Edit employee
void editEmployee(std::vector<Employee>& vect);


#endif