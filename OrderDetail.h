#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<vector>
using namespace std;

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
    friend istream &operator>>(istream &is, OrderDetail &myOrderDetail);



};
#endif // ORDERDETAIL_H
