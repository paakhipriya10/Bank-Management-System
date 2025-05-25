#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/*
---------------------------------------------------
           BANK MANAGEMENT SYSTEM
---------------------------------------------------
FEATURES:
1. Create a new account with an initial deposit.
2. Display all accounts with holder names and balances.
3. Search for an account by account number.
4. Deposit money into an account.
5. Withdraw money from an account (if sufficient balance is available).
6. Check the balance of an account.
7. Delete an account from the system.
8. Menu continuously displays until the user chooses to exit.
9. Prevents crashing on invalid inputs using input validation.
10. Ensures smooth user interaction without unexpected program exits.
---------------------------------------------------
*/

class Account {
private:
    string holderName;
    int accountNumber;
    double accountBalance;

public:
    // Constructor to initialize account
    Account(string name, int accNum, double balance) {
        holderName = name;
        accountNumber = accNum;
        accountBalance = balance;
    }

    // Getters
    string getHolderName() { return holderName; }
    int getAccountNumber() { return accountNumber; }
    double getBalance() { return accountBalance; }

    // Function to deposit money into account
    void depositMoney(double amount) {
        accountBalance += amount;
        cout << "\t\tDeposit Successful!\n";
    }

    // Function to withdraw money from account
    void withdrawMoney(double amount) {
        if (accountBalance >= amount) {
            accountBalance -= amount;
            cout << "\t\tWithdrawal Successful!\n";
        } else {
            cout << "\t\tInsufficient Balance...\n";
        }
    }
};

class Bank {
private:
    vector<Account> accountList;

public:
    // Function to create a new account
    void addNewAccount(string name, int accNum, double balance) {
        accountList.push_back(Account(name, accNum, balance));
        cout << "\t\tAccount Created Successfully!\n";
    }

    // Function to display all accounts
    void displayAllAccounts() {
        cout << "\t\tAll Account Holders:\n";
        for (Account &acc : accountList) {
            cout << "Name: " << acc.getHolderName() << ", Account Number: "
                 << acc.getAccountNumber() << ", Balance: " << acc.getBalance() << "\n";
        }
    }

    // Function to find an account by account number
    void findAccount(int accNum) {
        for (Account &acc : accountList) {
            if (acc.getAccountNumber() == accNum) {
                cout << "Name: " << acc.getHolderName() << ", Account Number: "
                     << acc.getAccountNumber() << ", Balance: " << acc.getBalance() << "\n";
                return;
            }
        }
        cout << "\t\tAccount Not Found...\n";
    }

    // Function to locate an account (returns pointer)
    Account* locateAccount(int accNum) {
        for (Account &acc : accountList) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    // Function to check balance
    void checkBalance(int accNum) {
        Account* acc = locateAccount(accNum);
        if (acc) {
            cout << "\t\tAvailable Balance: " << acc->getBalance() << "\n";
        } else {
            cout << "\t\tAccount Not Found...\n";
        }
    }

    // Function to delete an account
    void deleteAccount(int accNum) {
        for (auto it = accountList.begin(); it != accountList.end(); ++it) {
            if (it->getAccountNumber() == accNum) {
                accountList.erase(it);
                cout << "\t\tAccount Deleted Successfully...\n";
                return;
            }
        }
        cout << "\t\tAccount Not Found...\n";
    }
};

int main() {
    Bank bank;
    int choice;

    while (true) {
        // Display menu options
        cout << "\n\t\t:: Bank Management System ::\n";
        cout << "\t\t1. Create New Account\n";
        cout << "\t\t2. Show All Accounts\n";
        cout << "\t\t3. Search Account\n";
        cout << "\t\t4. Deposit Money\n";
        cout << "\t\t5. Withdraw Money\n";
        cout << "\t\t6. Balance Inquiry\n";
        cout << "\t\t7. Delete Account\n";
        cout << "\t\t8. Exit\n";
        cout << "\t\tEnter Your Choice: ";
        cin >> choice;

        // Handle invalid inputs
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tInvalid Input! Please enter a number.\n";
            continue;
        }

        if (choice == 8) {
            cout << "\t\tExiting...\n";
            break;
        }

        int accNum;
        double amount;
        string name;

        switch (choice) {
            case 1:
                cout << "\t\tEnter Name: ";
                cin >> name;
                cout << "\t\tEnter Account Number: ";
                cin >> accNum;
                cout << "\t\tEnter Initial Balance: ";
                cin >> amount;
                bank.addNewAccount(name, accNum, amount);
                break;

            case 2:
                bank.displayAllAccounts();
                break;

            case 3:
                cout << "\t\tEnter Account Number: ";
                cin >> accNum;
                bank.findAccount(accNum);
                break;

            case 4:
                cout << "\t\tEnter Account Number: ";
                cin >> accNum;
                if (Account* acc = bank.locateAccount(accNum)) {
                    cout << "\t\tEnter Amount to Deposit: ";
                    cin >> amount;
                    acc->depositMoney(amount);
                } else {
                    cout << "\t\tAccount Not Found...\n";
                }
                break;

            case 5:
                cout << "\t\tEnter Account Number: ";
                cin >> accNum;
                if (Account* acc = bank.locateAccount(accNum)) {
                    cout << "\t\tEnter Amount to Withdraw: ";
                    cin >> amount;
                    acc->withdrawMoney(amount);
                } else {
                    cout << "\t\tAccount Not Found...\n";
                }
                break;

            case 6:
                cout << "\t\tEnter Account Number: ";
                cin >> accNum;
                bank.checkBalance(accNum);
                break;

            case 7:
                cout << "\t\tEnter Account Number to Delete: ";
                cin >> accNum;
                bank.deleteAccount(accNum);
                break;

            default:
                cout << "\t\tInvalid Choice! Please enter a valid option.\n";
        }
    }

    return 0;
}
