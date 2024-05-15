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
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Balance: " << balance << "$" << std::endl;
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
            std::cout << "Account now found.";
        }
    }
};