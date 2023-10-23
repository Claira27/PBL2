#ifndef WATCH_H
#define WATCH_H
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

class OrderDetail;
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
    static void ReadWatch(const string &productID);
    static void CreateWatch(const string &productID);
    static int ReferenceConstraint(const string& ID);
    static void EraseWatch(const string &productID);
    static void UpdateWatch(const string &productID);
};

#endif // CUSTOMER_H
