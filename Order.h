#include<bits/stdc++.h>
#include"Date.h"
using namespace std;

#ifndef ORDER_H
#define ORDER_H

class Order
{
    string ID;
    string customerID;
    Date invoiceDate;
    double amountDue;
public:
    Order();
    Order(string ID, string customerID, Date invoiceDate, double amountDue);
    //Get information
    string getID() const;
    string getCustomerID() const;
    Date getInvoiceDate() const;
    double getAmountDue() const;
    //Mutator functions
    void setID(const string &ID);
    void setCustomerID(const string &customerID);
    void setInvoiceDate(const Date &invoiceDate);
    void setAmountDue(const double &amountDue);
    friend istream &operator>>(istream &is, Order &myOrder);
    friend ostream &operator<<(ostream &os, const Order &myOrder);
};
#endif // ORDER_H
