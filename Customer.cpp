#include "Customer.h"

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

    os<<setw(6)<<"|"<< ANSI_GREEN<<setw(16)<<left<<myCustomer.phone
        <<ANSI_RESET<<setw(12)<<left<<"|"<< ANSI_GREEN<<setw(26)<<left<<myCustomer.name<< ANSI_RESET <<"|"<<endl;
    return os;
}
void Customer::CustomerLoad()
{
    ifstream inputFile("Customers.txt");
    if (!inputFile)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
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
    //system("cls");
    cout << "\t\t\t\t\t\t"<< "Fetching customer data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(500);
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"======================Customer information===================="<<ANSI_RESET<<endl;
    cout<<endl;
    cout<< "\t\t\t\t\t\t"<<setw(6)<<left<<"|"<< ANSI_CYAN <<setw(16)<<left<<"Customer phone"
        <<ANSI_RESET<<setw(16)<<left<<"|"<< ANSI_CYAN<<setw(22)<<left<<"Name"<< ANSI_RESET<<"|"<<endl;
    for(const auto& pair : customerList)
    {
        cout<< "\t\t\t\t\t\t"<<"------------------------------------------------------------"<<endl;
        cout<< "\t\t\t\t\t\t"<<pair.second;
    }
    cout<< "\t\t\t\t\t\t"<<"------------------------------------------------------------"<<endl;
    getch();
}


void Customer::createNewCustomer(const string &phone)
{
    //system("cls");
    ofstream outputFile;
    outputFile.open("Customers.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
        return;
    }
    Customer newCustomer;
    string name;
    cout << "\t\t\t\t\t\t"<< "Enter customer name: ";
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

