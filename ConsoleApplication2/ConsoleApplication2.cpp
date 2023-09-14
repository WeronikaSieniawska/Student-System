#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Student {
public:
    Student(int roll, const std::string& name, int age, char grade)
        : rollNumber(roll), studentName(name), studentAge(age), studentGrade(grade) {}

    void display() const {
        std::cout << "Roll Number: " << rollNumber << "\n";
        std::cout << "Name: " << studentName << "\n";
        std::cout << "Age: " << studentAge << "\n";
        std::cout << "Grade: " << studentGrade << "\n";
    }

    int getRollNumber() const {
        return rollNumber;
    }

    bool isValid() const {
        return rollNumber > 0 && !studentName.empty() && studentAge >= 0 && (studentGrade >= 2 && studentGrade <= 5);
    }

private:
    int rollNumber;
    std::string studentName;
    int studentAge;
    char studentGrade;
};

int main() {
    std::vector<Student> studentRecords;
    int choice;

    while (true) {
        std::cout << "Student Record Management System\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Display All Students\n";
        std::cout << "3. Update Student Details\n";
        std::cout << "4. Delete Student Record\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid option.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            int roll;
            std::string name;
            int age;
            char grade;

            std::cout << "Enter Roll Number: ";
            std::cin >> roll;

            bool duplicate = false;
            for (const Student& student : studentRecords) {
                if (student.getRollNumber() == roll) {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate) {
                std::cout << "Student with the same Roll Number already exists.\n";
            }
            else {
                std::cin.ignore();
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Age: ";
                std::cin >> age;
                std::cout << "Enter Grade (2-5): ";
                std::cin >> grade;

                if (std::cin.fail() || grade < 2 || grade > 5) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter valid data.\n";
                }
                else {
                    studentRecords.emplace_back(roll, name, age, grade);
                    std::cout << "Student added successfully.\n";
                }
            }
            break;
        }
        case 2: {
            if (studentRecords.empty()) {
                std::cout << "No student records found.\n";
            }
            else {
                std::cout << "Student Records:\n";
                for (const Student& student : studentRecords) {
                    student.display();
                    std::cout << "\n";
                }
            }
            break;
        }
        case 3: {
            int rollToUpdate;
            std::cout << "Enter Roll Number of Student to Update: ";
            std::cin >> rollToUpdate;

            bool found = false;
            for (Student& student : studentRecords) {
                if (student.getRollNumber() == rollToUpdate) {
                    std::cin.ignore();
                    std::string name;
                    int age;
                    char grade;

                    std::cout << "Enter New Name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter New Age: ";
                    std::cin >> age;
                    std::cout << "Enter New Grade (2-5): ";
                    std::cin >> grade;

                    if (std::cin.fail() || grade < 2 || grade > 5) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter valid data.\n";
                    }
                    else {
                        student = Student(rollToUpdate, name, age, grade);
                        std::cout << "Student details updated successfully.\n";
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Student with Roll Number " << rollToUpdate << " not found.\n";
            }

            break;
        }
        case 4: {
            int rollToDelete;
            std::cout << "Enter Roll Number of Student to Delete: ";
            std::cin >> rollToDelete;

            bool found = false;
            for (auto it = studentRecords.begin(); it != studentRecords.end(); ++it) {
                if (it->getRollNumber() == rollToDelete) {
                    studentRecords.erase(it);
                    std::cout << "Student record deleted successfully.\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Student with Roll Number " << rollToDelete << " not found.\n";
            }

            break;
        }
        case 5:
            std::cout << "Exiting program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
