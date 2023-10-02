#include"Order.h"

Order::Order() : ID(" "), customerID(" "), invoiceDate(0,0,0), amountDue(0) {}
Order::Order(string ID, string customerID, Date invoiceDate, double amountDue)
        : ID(ID), customerID(customerID), invoiceDate(invoiceDate), amountDue(amountDue) {}
//Get information
string Order::getID() const
{
    return ID;
}
string Order::getCustomerID() const
{
    return customerID;
}
Date Order::getInvoiceDate() const
{
    return invoiceDate;
}
double Order::getAmountDue() const
{
    return amountDue;
}
//Mutator functions
void Order::setID(const string &ID)
{
    this->ID = ID;
}
void Order::setCustomerID(const string &customerID)
{
    this->customerID = customerID;
}
void Order::setInvoiceDate(const Date &invoiceDate)
{
    this->invoiceDate.ngay = invoiceDate.ngay;
    this->invoiceDate.thang = invoiceDate.thang;
    this->invoiceDate.nam = invoiceDate.nam;
}
void Order::setAmountDue(const double &amountDue)
{
    this->amountDue = amountDue;
}
istream &operator>>(istream &is, Order &myOrder)
{
    getline(is, myOrder.ID, ',');
    getline(is, myOrder.customerID, ',');
    is>>myOrder.invoiceDate;
    is>>myOrder.amountDue;
    return is;
}
ostream &operator<<(ostream &os, const Order &myOrder)
{
    os<<setw(10)<<myOrder.ID<<"\t"<<myOrder.customerID<<"\t"<<myOrder.invoiceDate<<"\t"<<myOrder.amountDue<<endl;
    return os;
}
