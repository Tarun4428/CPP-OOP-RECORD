#include <iostream>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;

public:
    Student(int r, string n)
    {
        rollNo = r;
        name = n;
        cout << "Object Created!" << endl;
    }

    void display()
    {
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
    }

    ~Student()
    {
        cout << "Object Destroyed!" << endl;
    }
};

int main()
{
    Student s1(105, "Neha"); 
    s1.display();
    
    return 0;
}

