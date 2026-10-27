#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BankException : public exception
{
protected:
    string message;

public:
    BankException(string msg)
    {
        message = msg;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance.")
    {
    }
};

class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be positive.")
    {
    }
};

class BankAccount
{
private:
    string name;
    double balance;

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        balance -= amount;
    }

    void display()
    {
        cout << "Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

int main()
{
    BankAccount account("Tarun", 8000);

    cout << "Initial Details:" << endl;
    account.display();

    try
    {
        cout << "\nDepositing Rs. 2000..." << endl;
        account.deposit(2000);

        cout << "Withdrawing Rs. 3000..." << endl;
        account.withdraw(3000);

        cout << "Withdrawing Rs. 15000..." << endl;
        account.withdraw(15000);
    }
    catch (const InsufficientFundsException &e)
    {
        cout << e.what() << endl;
    }
    catch (const InvalidAmountException &e)
    {
        cout << e.what() << endl;
    }
    catch (const BankException &e)
    {
        cout << "Bank Error: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "General Error: " << e.what() << endl;
    }

    cout << "\nFinal Details:" << endl;
    account.display();

    return 0;
}
