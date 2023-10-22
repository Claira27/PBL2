#include<iostream>
#include<iomanip>
#include<string>
#include<map>
#include<ctime>
#include<set>
using namespace std;

#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H
struct Warranty
{
    string expiry; //duration is 2 years;
    string coverage; //Battery Replacement: Some warranties for watches may cover the replacement of the battery, strap or bracelet within a specified time frame.
};
class OrderDetail
{
    string ID;
    string orderID;
    string IDserie;
    Warranty warranty;

public:
    friend class Watch;
    friend class Order;
    static int sales;// the number of watches sold out
    static map<string,OrderDetail> saleList;
    OrderDetail();
    //Get information
    string getID() const;
    string getOrderID() const;
    string getIDSerie() const;
    Warranty getWarranty() const;
    //mutator function
    void setID();
    void setOrderID(const string &orderID);
    void setIDSerie(const string &IDserie);
    void setWarranty();
    //Functions for CRUD
    friend istream &operator>>(istream &is, OrderDetail &myOrderDetail);
    friend ostream &operator<<(ostream &os, const OrderDetail &myOrderDetail);
    static void SaleLoad();
    static int getSales();
    static void ReadSale();
    static void FindSale();
    static void CreateSale(const string &orderID);
    static void EraseSale(const string &orderID);
    static void DeleteSale();
    static void UpdateSale(const string &orderID);
};
#endif // ORDERDETAIL_H
