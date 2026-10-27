#include <iostream>
#include <memory>
using namespace std;

class Resource
{
public:
    Resource()
    {
        cout << "Acquired" << endl;
    }

    ~Resource()
    {
        cout << "Released" << endl;
    }

    void use()
    {
        cout << "Using resource" << endl;
    }
};

class MySmartPointer
{
private:
    Resource* ptr;

public:
    MySmartPointer(Resource* p)
    {
        ptr = p;
    }

    ~MySmartPointer()
    {
        delete ptr;
        cout << "Custom pointer destroyed" << endl;
    }

    Resource* operator->()
    {
        return ptr;
    }

    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;
};

int main()
{
    cout << "--- Custom Pointer ---" << endl;

    {
        MySmartPointer smartPtr(new Resource());
        smartPtr->use();
    }

    cout << "\n--- unique_ptr ---" << endl;

    {
        unique_ptr<Resource> uniquePtr =
            make_unique<Resource>();

        uniquePtr->use();
    }

    cout << "\n--- shared_ptr ---" << endl;

    {
        shared_ptr<Resource> sharedPtr1 =
            make_shared<Resource>();

        shared_ptr<Resource> sharedPtr2 = sharedPtr1;

        sharedPtr1->use();

        cout << "Count: "
             << sharedPtr1.use_count() << endl;
    }

    cout << "\nDone!" << endl;

    return 0;
}
