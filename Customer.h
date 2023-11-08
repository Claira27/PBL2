#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<vector>
using namespace std;

class Customer
{
    string ID;
    string phone;
    string name;
public:
    Customer();
    Customer(const string &ID, const string &phone, const string &name);
    //Get information
    string getID() const;
    string getName() const;
    string getPhone() const;
    void setID(string ID);
    void setName(string name);
    void setPhone(string phone);

    friend istream &operator>>(istream &is, Customer &myCustomer);
};

#endif // CUSTOMER_H
