#include<iostream>
#include<fstream>
#include<cstring>
#include<map>
#include<ctime>
using namespace std;

#ifndef WATCH_H
#define WATCH_H
class Watch
{
    string ID;
    string productID;
    string serie;
    bool availability;
public:
    static map<string, Watch> watchList;
    static int numberOfWatch;
    friend class Product;
    friend class Order;
    friend class OrderDetail;
    Watch();
    Watch(const string &ProductID, const string &serie, const bool avail = true);
    //Get information
    string getID() const;
    string getProductID() const;
    string getSerie() const;
    bool getAvailability () const;
    //Mutator functions
    void setID();
    void setProductID(string productID);
    void setSerie(string serie);
    void setAvailability(bool avail);
    //Functions for CRUD
    friend istream &operator>>(istream &is, Watch &myWatch);
    friend ostream &operator<<(ostream &os, const Watch &myWatch);
    static void WatchLoad();
    static int getNumberOfWatch();
    static void ReadWatch();
    static void FindWatch();
    static void CreateWatch();
    static int ReferenceConstraint(const string& ID);
    static void EraseWatch();
    static void UpdateWatch();
};

#endif // CUSTOMER_H
