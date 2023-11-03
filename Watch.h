#ifndef WATCH_H
#define WATCH_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<sstream>
#include<vector>
using namespace std;

class OrderDetail;
class Watch
{
    string ID;
    string productID;
    string serie;
    bool availability;
public:
    friend class Product;
    Watch();
    Watch(const string &ProductID, const string &serie, const bool avail = true);
    //Get information
    void setID();
    string getID();
    string getProductID() const;
    string getSerie() const;
    bool getAvailability () const;
    //Mutator functions
    void setProductID(string productID);
    void setSerie(string serie);
    void setAvailability(bool avail);
    //Functions for CRUD
    friend istream &operator>>(istream &is, Watch &myWatch);
};

#endif // CUSTOMER_H
