#include"myFunctions.h"

void FilestreamCustomer(map<string, Customer> customerList)
{
    ifstream inputFile("Customers.txt");
    if (!inputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    int check=0;
    Customer customer;
    while (inputFile >> customer)
    {
        // Check if the customer already exists in the map
        auto existingCustomer = customerList.find(customer.getID());
        if (existingCustomer != customerList.end())
        {
            existingCustomer->second = customer; // Updating existing customer
            check++;
        }
        else
        {
            customerList[customer.getID()] = customer; // Add a new customer
            numberOfcustomer++;
        }
    }
    inputFile.close();
    if(check)
    {
        cout << "Customers( by CustomerID) already exist. Information uploaded and updated from file." << endl;
    }
    else
    {
        cout << "Information uploaded from file." << endl;
    }
}
void CreateCustomer(map<string, Customer> customerList)
{

}
void myCreateCustomer()
{
    while(1)
    {
        cout<<"Enter 1 to stream customer data from existing file"<<endl;
        cout<<"Enter 2 to customize customer data"<<endl;
        cout<<"Enter 3 to exit"<<endl;
        int inputmethod;
        cin>>inputmethod;
        switch (inputmethod)
        {
            case 1:
                FilestreamCustomer(map<string, Customer> customerList);
            break;
            case 2:
                CreateCustomer(map<string, Customer> customerList);
            break;
            case 3: return;
            default:
                cout<<"Invalid input method. Please try again"<<endl;
            break;
        }

    }
}
void ReadCustomer(map<string, Customer> customerList);
void UpdateCustomer(map<string, Customer> customerList);
void DeleteCustomer(map<string, Customer> customerList);
