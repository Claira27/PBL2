#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<sstream>
#include<vector>
using namespace std;


struct Description
{
    string strap;//material
    string color;
    string brand;
    string origin;
    string gender;
    string type; // daily dress complicated pilot field dive racing travel luxury other
};
class Category;
class Watch;

class Product
{
    string ID;
    string name;
    double price;
    int quantity;
    Description feature;
public:
    friend class Manage;
    Product();
    //Get information
    string getID() const;
    string getName() const;
    double getPrice() const;
    int getQuantity();
    Description getFeature() const;
    //Mutator functions
    void setID(const string &ID);
    void setName(const string &name);
    void setPrice(const double &price);
    void setQuantity();
    void setFeature(Description feature);
    friend istream &operator>>(istream &is, Product &myProduct);
};

#endif // PRODUCT_H

