#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <fstream>


class Account {
public:
    int accountNumber {};
    std::string name {};
    double balance {};

    Account(int accNumber, std::string custName, double initBalance)
        : accountNumber(accNumber), name(custName), balance(initBalance) {}

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (balance >= amount){
            balance -= amount;
        } else {
            std::cout << "Insufficient found.\n";
        }
    }

    void display() {
        std::cout << "Account Number: " << accountNumber << ", Name: " << name << ", Balance: " << balance << "$.\n"; 
        //std::cout << "Account Number: " << accountNumber << std::endl;
        //std::cout << "Name: " << name << std::endl;
        //std::cout << "Balance: " << balance << "$" << std::endl;
    }
};


class Bank {
private:
    std::vector<Account> accounts; 

public:
    void addAccount(const Account &acc) {
        accounts.push_back(acc);
    }

    void deleteAccount(int accNumber) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accNumber) {
                accounts.erase(it);
                return;
            }
            std::cout << "Account not found.\n";
        }
    }

    Account* findAccount(int accNumber) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accNumber) {
                return &acc;
            }
        }
        return nullptr;    
    }

    void displayAllAccounts() {
        for (auto &acc : accounts) {
            acc.display();
        }
    }

    void saveToFile(const std::string &filename) const {
        std::ofstream outFile(filename);
        
        if (outFile.is_open()){
            for (const auto &acc : accounts){
                outFile << acc.accountNumber << " " << acc.name << " " << acc.balance <<  std::endl;
            }
            outFile.close();
        } else {
            std::cerr << "saveToFile() Error. Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadFromFile(const std::string &filename) const {
        std::ifstream inFile(filename);
        std::string line;

        if (inFile.is_open()){
            while(std::getline(inFile, line)) {
                std::cout << line << std::endl;
            }
            inFile.close();
        } else {
            std::cerr << "loadFromFile() Error. Unable to open file for reading" << filename << std::endl;
        }
    }
};




int main() {
    Bank bank;
    bank.addAccount(Account(1001, "Alice", 1500.0));
    bank.addAccount(Account(1002, "Bob", 1200.5));
    bank.addAccount((Account(1003, "Charlie", 980.75)));
    bank.addAccount((Account(1004, "Mark", 8400.30)));

    std::string filename = "test_accounts.txt";

    bank.saveToFile(filename);

    bank.loadFromFile(filename);

    return 0;
}