#include<iostream>
#include<cstring>
#include<map>
#include<ctime>
#include<iomanip>
#include<sstream>

using namespace std;

#ifndef ORDER_H
#define ORDER_H

class Order
{
    string ID;
    string customerPhone;
    string invoiceDate;
    double amountDue;
public:
    friend class OrderDetail;
    static int numberOfOrder;
    static string lastID;
    static map<string, Order> orderList;
    Order();
    //Get information
    string getID() const;
    string getCustomerPhone() const;
    string getInvoiceDate() const;
    double getAmountDue();
    //Mutator functions
    void setID(const string &ID);
    void setCustomerPhone(const string &customerPhone);
    time_t setInvoiceDate(const string &invoiceDate);
    void setAmountDue();
    //Functions for CRUD
    friend istream &operator>>(istream &is, Order &myOrder);
    friend ostream &operator<<(ostream &os, const Order &myOrder);
    static void OrderLoad();
    static int getNumberOfOrder();
    static string generateOrderID(const string &myid);
    static void ReadOrder();
    static void FindOrder();
    static void CreateOrder();
    static int ReferenceConstraint(const string &ID);
    static void EraseOrder();
    static void DeleteOrder();
    static void UpdateOrder();
};
#endif // ORDER_H
