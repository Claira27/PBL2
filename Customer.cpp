#include "Customer.h"
#include "Order.h"

int Customer::numberOfCustomer=0;
map<string, Customer> Customer::customerList;

Customer::Customer() : phone(" "), name(" ") {}
Customer::Customer(const string &phone, const string &name) :
    phone(phone), name(name) {}

string Customer::getName() const
{
    return name;
}
string Customer::getPhone() const
{
    return phone;
}

void Customer::setName(string name)
{
    this->name=name;
}
void Customer::setPhone(string phone)
{
    this->phone=phone;
}
istream &operator>>(istream &is, Customer &customer)
{
    is.ignore();
    getline(is,customer.phone, ',');
    getline(is,customer.name, ',');
    return is;
}
ostream &operator<<(ostream &os, const Customer &myCustomer)
{
    os<<myCustomer.phone<<"\t"<<myCustomer.name<<endl;
    return os;
}
void Customer::CustomerLoad()
{
    ifstream inputFile("Customers.txt");
    if (!inputFile)
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    Customer customer;
    while (inputFile >> customer)
    {
        customerList[customer.getPhone()] = customer; // Add a new customer
        numberOfCustomer++;
    }
    cout << "Information uploaded from file." << endl;
    inputFile.close();
}
int Customer::getNumberOfCustomer()
{
    return numberOfCustomer;
}
void Customer::ReadCustomer()
{
    for(const auto& pair : customerList)
        cout<<pair.second;
}
void Customer::FindCustomer()
{
    string phone;
    cout<<"Finding customer: "; getline(cin, phone);
    auto currentCustomer = customerList.find(phone);
    if(currentCustomer != customerList.end())
    {
        cout<<currentCustomer->second;
    }
    else
    {
        cout<<"Non-existing customer!"<<endl;
        return;
    }
}
void Customer::CreateCustomerList()
{
    ofstream outputFile;
    outputFile.open("Customers.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of new customers
    int num;
    do
    {
        cout<<"Enter the number of new customers to create: ";
        cin>>num;
        if(num > 50)
        {
            cout << "Exceeded the allowed number of new customers to be created mutually, stream file instead!" << endl;
        }
    }while(num  > 50);
    //Create new customer
    cin.ignore();
    while(num--)
    {
        Customer newCustomer;
        string name, phone;
        cout << "Enter customer name: ";
        getline(cin, name);
        cout << "Enter customer phone: ";
        getline(cin, phone);
        if(customerList.count(phone))
        {
            cout<<"Customer already existed!"<<endl;
            num++;
        }
        newCustomer.setPhone(phone);
        newCustomer.setName(name);
        customerList[phone] = newCustomer;
        //Write new customers to file
        outputFile<<newCustomer.getPhone()<<","
                  <<newCustomer.getName()<<","<<endl;
        numberOfCustomer++;
    }

    outputFile.close();
    cout<<"Information written to file."<<endl;
}
void Customer::createNewCustomer(const string &phone)
{
    ofstream outputFile;
    outputFile.open("Customers.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    Customer newCustomer;
    string name;
    cout << "Enter customer name: ";
    getline(cin, name);
    newCustomer.setPhone(phone);
    newCustomer.setName(name);
    customerList[phone] = newCustomer;
    //Write new customers to file
    outputFile<<newCustomer.getPhone()<<","
              <<newCustomer.getName()<<","<<endl;
    numberOfCustomer++;
    outputFile.close();
}
int Customer::ReferenceConstraint(const string &phone)
{
    for(auto order : Order::orderList)
    if(phone == order.second.getCustomerPhone())
        return 1;
    return 0;
}
void Customer::EraseCustomer()
{
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of customers to erase
    int num;
    do
    {
        cout<<"Enter the number of customers to erase: ";
        cin>>num;
        if(num  > numberOfCustomer)
        {
            cout << "Exceeded the number of existing customers" << endl;
        }
    }while(num > numberOfCustomer);
    //erase customers
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string phone;
        cout<<i<<". Customer phone : "; getline(cin, phone);
        if(customerList.count(phone))
        {
            if(!ReferenceConstraint(phone))
            {
                customerList.erase(phone);
                numberOfCustomer--;
                i++;
            }
        }
        else
        {
            cout<<"Non-existing customer!"<<endl;
        }
    }
    //Overwriting the file to erase customers
    outputFile<<endl;
    for(auto currentCustomer : customerList)
    {
        outputFile<<currentCustomer.second.getPhone()<<","
                  <<currentCustomer.second.getName()<<","<<endl;
    }
    outputFile.close();
    cout<<num<<" Customers have been erased."<<endl;
}
void Customer::UpdateCustomer()
{
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of customers to update
    int num;
    do
    {
        cout<<"Enter the number of customers to update: ";
        cin>>num;
        if(num  > numberOfCustomer)
        {
            cout << "Exceeded the number of existing customers" << endl;
        }
    }while(num > numberOfCustomer);
    //Update customers
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string phone;
        cout<<i<<". Customer phone : "; getline(cin, phone);
        if(customerList.count(phone))
        {
            if(!ReferenceConstraint(phone))
            {
                customerList.erase(phone);
                Customer newCustomer;
                string name, phone;
                cout << "Enter customer name: ";
                getline(cin, name);
                cout << "Enter customer phone: ";
                getline(cin, phone);
                newCustomer.setPhone(phone);
                newCustomer.setName(name);
                customerList[phone] = newCustomer;
                i++;
            }
        }
        else
        {
            cout<<"Non-existing customer!"<<endl;
        }
    }
    //Overwriting the file to update customers
    outputFile<<endl;
    for(auto currentCustomer : customerList)
        outputFile<<currentCustomer.second.getPhone()<<","
                  <<currentCustomer.second.getName()<<","<<endl;
    outputFile.close();
    cout<<num<<" Updates have been made."<<endl;
}

