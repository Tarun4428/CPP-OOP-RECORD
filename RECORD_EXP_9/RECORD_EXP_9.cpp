#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Observer
{
public:
    virtual void notify(const string& message) = 0;
    virtual ~Observer() {}
};

class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email to " << email
             << ": " << message << endl;
    }
};

class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS to " << phoneNumber
             << ": " << message << endl;
    }
};

class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    EventManager()
    {
    }

public:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void triggerEvent(const string& message)
    {
        cout << "\nEvent: "
             << message << endl;

        cout << "Notifying...\n";

        for (auto observer : observers)
        {
            observer->notify(message);
        }
    }
};

int main()
{
    EventManager& manager = EventManager::getInstance();

    shared_ptr<Observer> emailUser =
        NotificationFactory::createNotification(
            "EMAIL",
            "user@example.com");

    shared_ptr<Observer> smsUser =
        NotificationFactory::createNotification(
            "SMS",
            "9444012345");

    manager.subscribe(emailUser);
    manager.subscribe(smsUser);

    manager.triggerEvent(
        "Placement drive registration closes tonight!");

    return 0;
}
