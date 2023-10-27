#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H
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

struct Warranty
{
    string expiry; //duration is 2 years;
    string coverage; //Battery Replacement: Some warranties for watches may cover the replacement of the battery, strap or bracelet within a specified time frame.
};
class Order;
class OrderDetail
{
    string ID;
    string orderID;
    string IDserie;
    Warranty warranty;
protected:
    static int sales;// the number of watches sold out
    static map<string,OrderDetail> saleList;
public:
    OrderDetail();
    //Get information
    string getID() const;
    string getOrderID() const;
    string getIDSerie() const;
    Warranty getWarranty();
    //mutator function
    void setID();
    void setOrderID(const string &orderID);
    void setIDSerie(const string &IDserie);
    void setWarranty(Warranty warrant);
    //Functions for CRUD
    friend istream &operator>>(istream &is, OrderDetail &myOrderDetail);
    friend ostream &operator<<(ostream &os, const OrderDetail &myOrderDetail);
    static void SaleLoad();
    static int getSales();

};
#endif // ORDERDETAIL_H
