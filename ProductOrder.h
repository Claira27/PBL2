#include<bits/stdc++.h>
using namespace std;

#ifndef PRODUCTORDER_H
#define PRODUCTORDER_H
class ProductOrder
{
    string ID;
    string orderID;
    string productID;
    int quantity;
public:
    ProductOrder();
    ProductOrder(string ID, string orderID, string productID, int quantity);
    //Get information
    string getID() const;
    string getOrderID() const;
    string getProductID() const;
    int getQuantity() const;
    //Mutator functions
    void setID(const string &ID);
    void setOrderID(const string &orderID);
    void setProductID(const string &productID);
    void setQuantity(const int &quantity);
    friend istream &operator>>(istream &is, ProductOrder &myProductOrder);
    friend ostream &operator<<(ostream &os, const ProductOrder &myProductOrder);
};
#endif // PRODUCTORDER_H
