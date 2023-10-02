#include"ProductOrder.h"

ProductOrder::ProductOrder() : ID(" "), orderID(" "), productID(" "), quantity(0) {}
ProductOrder::ProductOrder(string orderID, string productID, string ID, int quantity)
        : orderID(orderID), productID(productID), ID(orderID+productID), quantity(quantity {}
//Get information
string ProductOrder::getID() const
{
    return ID;
}
string ProductOrder::getOrderID() const
{
    return orderID;
}
string ProductOrder::getProductID() const
{
    return productID;
}
int ProductOrder::getQuantity() const
{
    return quantity;
}
//Mutator functions
void ProductOrder::setID(const string &orderID, const string &productID)
{
    this->ID = orderID + productID
}
void ProductOrder::setOrderID(const string &orderID)
{
    this->orderID = orderID;
}
void ProductOrder::setProductID(const string &productID)
{
    this->productID = productID;
}
void ProductOrder::setQuantity(const int &quantity)
{
    this->quantity = quantity;
}
istream &operator>>(istream &is, ProductOrder &myProductOrder)
{
    getline(is, myProductOrder.orderID, ',');
    getline(is, myProductOrder.productID, ',');
    myProductOrder.ID = myProductOrder.orderID + myProductOrder.productID;
    is>>myProductOrder.quantity;
    return is;
}
ostream &operator<<(ostream &os, const ProductOrder &myProductOrder)
{
    os<<setw(10)<<myProductOrder.ID<<"\t"<<myProductOrder.orderID<<"\t"<<myProductOrder.productID<<"\t"<<myProductOrder.quantity<<endl;
    return os;
}
