#include "Customer.h"
static int Customer::numberOfCustomer=0;
Customer::Customer() : ID(" "), name(" "), phone(" ") {}
Customer::Customer(string ID,const string &name,const string &phone) :
    ID(ID), name(name), phone(phone) {}
string Customer::getID() const
{
    return ID;
}
string Customer::getName() const
{
    return name;
}
string Customer::getPhone() const
{
    return phone;
}
void Customer::setID(string ID)
{
    this->ID=ID;
}
void Customer::setName(const string &name)
{
    this->name=name;
}
void Customer::setPhone(const string &phone)
{
    this->phone=phone;
}
istream &operator>>(istream &is, Customer &myCustomer)
{
    getline(is,myCustomer.ID, ',');
    getline(is,myCustomer.name, ',');
    getline(is,myCustomer.phone, ',');
    return is;
}
ostream &operator<<(ostream &os, const Customer &myCustomer)
{
    os<<setw(10)<<myCustomer.ID<<"\t"<<myCustomer.name<<"\t"<<myCustomer.phone<<endl;
    return os;
}
