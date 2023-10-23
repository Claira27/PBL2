#include "Customer.h"
#include "Order.h"
// ANSI color codes for text
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[31m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_YELLOW = "\033[33m";
const string ANSI_CYAN = "\033[36m";
const string ANSI_BOLD = "\033[1m";
const string ANSI_BLINK = "\033[5m";

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
    os<< ANSI_GREEN <<myCustomer.phone<<"\t"<<myCustomer.name<< ANSI_RESET <<endl;
    return os;
}
void Customer::CustomerLoad()
{
    ifstream inputFile("Customers.txt");
    if (!inputFile)
    {
        cout<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
        return;
    }
    Customer customer;
    while (inputFile >> customer)
    {
        customerList[customer.getPhone()] = customer; // Add a new customer
        numberOfCustomer++;
    }
    inputFile.close();
}
int Customer::getNumberOfCustomer()
{
    return numberOfCustomer;
}
void Customer::ReadCustomer()
{
    system("cls");
    cout << "Fetching customer data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<< ANSI_CYAN <<"Customer phone\tName"<< ANSI_RESET<<endl;
    for(const auto& pair : customerList)
        cout<<pair.second;
}
void Customer::FindCustomer()
{
    system("cls");
    string phone;
    cout<<"Finding customer: "; getline(cin, phone);
    auto currentCustomer = customerList.find(phone);
    if(currentCustomer != customerList.end())
    {
        cout<<currentCustomer->second;
    }
    else
    {
        cout<<ANSI_YELLOW<<"Non-existing customer!"<< ANSI_RESET<<endl;
        return;
    }
}
void Customer::CreateCustomerList()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Customers.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
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
            cout <<ANSI_YELLOW<< "Exceeded the allowed number of new customers to be created mutually, stream file instead!" << ANSI_RESET<< endl;
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
            cout<<ANSI_YELLOW<<"Customer already existed!"<< ANSI_RESET<<endl;
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
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    outputFile.close();
    cout<<ANSI_GREEN<<"Information written to file."<< ANSI_RESET<<endl;
}
void Customer::createNewCustomer(const string &phone)
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Customers.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
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
    system("cls");
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
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
            cout<<ANSI_YELLOW << "Exceeded the number of existing customers" << ANSI_RESET<< endl;
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
            else cout<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
        }
        else
        {
            cout<<ANSI_YELLOW<<"Non-existing customer!"<< ANSI_RESET<<endl;
        }
    }
    //Overwriting the file to erase customers
    outputFile<<endl;
    for(auto currentCustomer : customerList)
    {
        outputFile<<currentCustomer.second.getPhone()<<","
                  <<currentCustomer.second.getName()<<","<<endl;
    }
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    outputFile.close();
    cout<<ANSI_GREEN<<num<<" Customers have been erased."<< ANSI_RESET<<endl;
}
void Customer::UpdateCustomer()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
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
            cout <<ANSI_YELLOW<< "Exceeded the number of existing customers" << ANSI_RESET<< endl;
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
            else cout<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
        }
        else
        {
            cout<<ANSI_YELLOW<<"Non-existing customer!"<< ANSI_RESET<<endl;
        }
    }
    //Overwriting the file to update customers
    outputFile<<endl;
    for(auto currentCustomer : customerList)
        outputFile<<currentCustomer.second.getPhone()<<","
                  <<currentCustomer.second.getName()<<","<<endl;
    outputFile.close();
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<<ANSI_GREEN<<num<<" Updates have been made."<< ANSI_RESET<<endl;
}

