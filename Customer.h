#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<iomanip>
#include<cstdlib> // For system("cls")
#include<unistd.h> // For sleep (sleep function on Unix-like systems)
#include<windows.h>
#include<vector>
#include<map>
#include<set>
using namespace std;

class Order;
class Customer
{
    string phone;
    string name;
public:
    friend class Order;
    static int numberOfCustomer;
    static map<string, Customer> customerList;
    Customer();
    Customer(const string &phone, const string &name);
    //Get information
    string getName() const;
    string getPhone() const;
    //Mutator functions
    void setName(string name);
    void setPhone(string phone);
    //Functions for CRUD
    friend istream &operator>>(istream &is, Customer &myCustomer);
    friend ostream &operator<<(ostream &os, const Customer &myCustomer);
    static void CustomerLoad();
    static int getNumberOfCustomer();
    static void ReadCustomer();
    static void FindCustomer();
    static void CreateCustomerList();
    static void createNewCustomer(const string &phone);//using when new order with new customer
    static int ReferenceConstraint(const string &phone);
    static void EraseCustomer();
    static void UpdateCustomer();
};

#endif // CUSTOMER_H
