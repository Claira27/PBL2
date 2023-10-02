#include<bits/stdc++.h>
using namespace std;

#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer
{
    static int numberOfCustomer;
    string ID;
    string name;
    string phone;
public:
    Customer();
    Customer(string ID,const string &name,const string &phone);
    //Get information
    string getID() const;
    string getName() const;
    string getPhone() const;
    //Mutator functions
    void setID(string ID);
    void setName(const string &name);
    void setPhone(const string &phone);
    friend istream &operator>>(istream &is, Customer &myCustomer);
    friend ostream &operator<<(ostream &os, const Customer &myCustomer);
};

#endif // CUSTOMER_H
