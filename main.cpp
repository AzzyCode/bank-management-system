#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>


class Account {
public:
    int accountNumber {};
    std::string username {};
    std::string name {};
    double balance {};

    Account(int accNumber, std::string &user, std::string &custName, double initBalance)
        : accountNumber(accNumber), username(user), name(custName), balance(initBalance) {}

    void deposit(double amount) {
        balance += amount;
        recordTransation("Deposit", amount);
    }

    void withdraw(double amount) {
        if (balance >= amount){
            balance -= amount;
            recordTransation("Withdraw", amount);
        } else {
            std::cout << "Insufficient found.\n";
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (balance > amount) {
            withdraw(amount);
            toAccount.deposit(amount);
            recordTransation("Transfer to: " + std::to_string(toAccount.accountNumber), amount);
            toAccount.recordTransation("Transfer from" + std::to_string(accountNumber), amount);
        } else {
            std::cout << "Insufficient funds for transfer.\n";
        }
    }

    void display() {
        std::cout << "Account Number: " << accountNumber << ", Name: " << name << ", Balance: " << balance << "$.\n"; 
        //std::cout << "Account Number: " << accountNumber << std::endl;
        //std::cout << "Name: " << name << std::endl;
        //std::cout << "Balance: " << balance << "$" << std::endl;
    }

    void applyInterest(double rate) {
        double interest = balance * rate;
        balance += interest;
        recordTransation("Interest applied", interest);
    }

    void displayTransactionHistory() const {
        std::cout << "Transation history for Account" << accountNumber << ":\n";
        for (const auto &transaction : transactionHistory) {
            std::cout << transaction << "\n";
        } 
    }

private:
    std::vector<std::string> transactionHistory;

    void recordTransation(const std::string &type, double amount) {
        std::ostringstream ss;
        ss << type << ": " << amount << "$. Balance: " << balance << "$.";
        transactionHistory.push_back(ss.str());
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
        }
        std::cout << "Account not found.\n";
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


class User {
private:
    std::string username;
    std::string password;
    std::map<std::string, std::string> users;

public:
    User(const std::string &userUsername, const std::string userPassword) : username(userUsername), password(userPassword) {};


    void addUser (const std::string &username, const std::string &password) {
        users[username] = password;
    }

    bool validateUser(const std::string &username, const std::string &password) {
        auto it = users.find(username);
        
        // Check if the username was found and if the password matches
        return (it != users.end() && it->second == password);
    }

    void saveCredentialsToFile(const std::string &filename) const {
        std::ofstream outFile(filename);

        if (outFile.is_open()) {
            for (const auto &user : users) {
                outFile << user.first << " " << user.second << std::endl;
            }
            outFile.close();
        } else {
            std::cerr << "saveCredentialsToFile Error. Unable to open file for write" << filename << std::endl;
        }
    }

    void loadCredentialsFromFile(const std::string &filename) {
        std::ifstream inFile(filename);
        std::string line;

        if (inFile.is_open()) {
           users.clear();

           while (std::getline(inFile, line)) {
                // Use an isstringstream to parse the line
                std::istringstream iss(line);
                std::string username, password;

                // Extract the username and password from the line
                if (iss >> username >> password) {
                    users[username] = password;
                }
           }
           inFile.close();
        } else {
            std::cerr << "loadCredentialsFromFile Error(). Unable to open file for read" << filename << std::endl;
        }
    }
};

            
int main() {
    Bank bank;
    User user("", "");

    std::string userFile = "users.txt";
    std::string accountFile = "test_accounts.txt";

    user.loadCredentialsFromFile(userFile);

    std::string username, password;
    char choice;

    std::cout << "1. Login\n2. Register\nChoose an option: ";
    std::cin >> choice;

    switch (choice) {
        case '1':
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            if (!user.validateUser(username, password)) {
                std::cout << "Invalid username or password\n";
                return 1;
            }
            break;
        case '2':
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            user.addUser(username, password);
            user.saveCredentialsToFile(userFile);
            break;
        default:
            std::cout << "Invalid choice.\n";
            return 1;
    }

    char userChoice;
    if (user.validateUser(username, password)) {
        std::cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. View Balance\n Choose an option: ";
        std::cin >> userChoice;
    }


    //bank.saveToFile(accountFile);

    //bank.loadFromFile(accountFile);

    return 0;
}