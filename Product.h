#include<iostream>
#include<fstream>
#include<cstring>
#include<map>
#include<utility>
using namespace std;

#ifndef PRODUCT_H
#define PRODUCT_H
struct Description
{
    string strap;//material
    string color;
    string brand;
    string origin;
    string gender;
    string type; // daily dress complicated pilot field dive racing travel luxury other
};
class Product
{
    string ID;
    string name;
    double price;
    int quantity;
    Description feature;
public:
    friend class OrderDetail;
    static map<string, Product> productList;
    static int numberOfProduct;
    friend class Category;
    Product();
    //Get information
    string getID() const;
    string getName() const;
    double getPrice() const;
    void setQuantity();
    int getQuantity();
    Description getFeature() const;
    //Mutator functions
    void setID(const string &ID);
    void setName(const string &name);
    void setPrice(const double &price);
    void setFeature();
    friend istream &operator>>(istream &is, Product &myProduct);
    friend ostream &operator<<(ostream &os, const Product &myProduct);
    static void ProductLoad();
    static int getNumberOfProduct();
    static void ReadProduct();
    static void FindProduct();
    static void CreateProduct();
    static int ReferenceConstraint(Product product);
    static void Eraseproduct();
    static void UpdateProduct();
};

#endif // PRODUCT_H

