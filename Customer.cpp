#include "Customer.h"


Customer::Customer() : ID(" "), phone(" "), name(" ") {}
Customer::Customer(const string &ID, const string &phone, const string &name) :
    ID(ID), phone(phone), name(name) {}
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
    this->ID = ID;
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
    getline(is,customer.ID, '|');
    getline(is,customer.phone, '|');
    getline(is,customer.name, '|');
    is.ignore();
    return is;
}
