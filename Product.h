#include<bits/stdc++.h>
using namespace std;

#ifndef PRODUCT_H
#define PRODUCT_H
struct Description
{
    string parameter;
    double size;//in milimeter
    string color;
};
class Product
{
    string ID;
    string categoryID;
    string name;
    double price;
    bool availability;
public:
    Product();
    Product(const string ID, const string categoryID, const string &name,const double &price, const bool availability);
    //Get information
    string getID() const;
    string getCategoryID() const;
    string getName() const;
    double getPrice() const;
    bool getAvailability() const;
    //Mutator functions
    void setID(const string &ID);
    void setCategoryID(const string &categoryID);
    void setName(const string &name);
    void setPrice(const double &price);
    void setAvailability(const bool availability);
};
class Watch : public Product
{
   Description feature;
public:
    Watch();
    Watch(const string ID, const string CategoryID, const string &name,const double &price, const bool availability, const Description &feature);
    //Get information
    Description getFeature() const;
    //Mutator functions
    void setFeature(const Description &feature);
    friend istream &operator>>(istream &is, Watch &myWatch);
    friend ostream &operator<<(ostream &os, const Watch &myWatch);
};
#endif // PRODUCT_H
