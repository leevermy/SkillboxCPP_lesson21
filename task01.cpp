#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Payments {
    std::string name;
    std::string surname;
    std::string date;
    int salary;
};

void InputFromUser(Payments& payment);
bool isValidDate(const std::string date);
bool isLeapYear(int year);
int daysInMonth(int month, int year);
bool isValidData(const std::string& data);
std::vector<Payments> List(const std::string& filename);
void Add(const std::string& filename);


int main() {
    std::string command;
    const std::string filename = "./payments.txt";

    while (true) {
        std::cout << "Enter the command to operate ('list' to show employees, 'add' to add information): ";
        std::cin >> command;
        std::cin.ignore(1000, '\n');

        if (command == "list") {
            std::vector<Payments> payments = List(filename);
            if (payments.empty()) continue;
            
            std::cout << "\nInformation about employees: " << std::endl;
            for (const auto payment : payments) {
                std::cout << payment.name << " " << payment.surname << " " << payment.date << " " << payment.salary << std::endl;
            }
            std::cout << std::endl;

        } else if (command == "add") {
            Add(filename);
            std::cout << std::endl;

        } else {
            std::cout << "Unknown command. Terminate!" << std::endl;
            break;
        }
    };
    return 0;
}


void Add(const std::string& filename) {
    std::ofstream out_file(filename, std::ios::app);
    if (!out_file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }
    Payments payment;
    InputFromUser(payment);
    out_file << payment.name << " " << payment.surname << " " << payment.date << " " << payment.salary << std::endl;
    out_file.close();
}

std::vector<Payments> List(const std::string& filename) {
    std::ifstream in_file(filename);
    if (!in_file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return{};
    }

    std::vector<Payments> payments;
    while (!in_file.eof()) {
        Payments payment;
        in_file >> payment.name;
        if (in_file.eof()) break;
        in_file >> payment.surname >> payment.date >> payment.salary;
        payments.push_back(payment);
    }
    in_file.close();
    return payments;
}

void InputFromUser(Payments& payment) {
    std::cout << "Enter the name of the employee: ";
    std::cin >> payment.name;
    while (!isValidData(payment.name)) {
        std::cout << "Invalid name. Only alphabetic characters allowed. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> payment.name;
    }

    std::cout << "Enter the surname of the employee: ";
    std::cin >> payment.surname;
    while (!isValidData(payment.surname)) {
        std::cout << "Invalid surname. Only alphabetic characters allowed. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> payment.surname;
    }

    std::cout << "Enter the date of the salary(dd.mm.yyyy): ";
    std::cin >> payment.date;
    while(!isValidDate(payment.date)) {
        std::cout << "Wrong date. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> payment.date;
    }

    std::cout << "Enter the payment amount in rubles: ";
    std::cin >> payment.salary;
    while(std::cin.fail()) {
        std::cout << "Invalid payment. Only digits allowed. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> payment.salary;
    }

}

bool isValidDate(const std::string date) {
    if (date.length() != 10) return false;
    
    int size = date.length();
    for (int i = 0; i < size; ++i) {
        if ((i == 2 || i == 5) && date[i] != '.') 
            return false;
        else if ((i != 2 && i != 5) && !std::isdigit(date[i])) 
            return false;
    }

    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    return (month <= 12 && month >= 1 && day >= 1 && day <= daysInMonth(month, year));
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeapYear(year) ? 29 : 28;
        default: return 0;
    }
}

bool isValidData(const std::string& data) {
    return std::all_of(data.begin(), data.end(), [](unsigned char c) {
        return std::isalpha(c);
    });
}