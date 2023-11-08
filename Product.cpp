#include"Product.h"

Product::Product() : ID(" "), name(" "), price(0), quantity(0) {}
//Get information
string Product::getID() const
{
    return ID;
}
string Product::getName() const
{
    return name;
}
double Product::getPrice() const
{
    return price;
}
void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}
int Product::getQuantity()
{
    return quantity;
}
Description Product::getFeature() const
{
    return feature;
}
//Mutator functions
void Product::setID(const string &ID)
{
    this->ID = ID;
}
void Product::setName(const string &name)
{
    this->name = name;
}
void Product::setPrice(const double &price)
{
    this->price = price;
}
void Product::setFeature(Description feature)
{
    //int check1=0, check2=0;
    this->feature.gender = feature.gender;
    this->feature.type = feature.type;
    this->feature.strap = feature.strap;
    this->feature.color = feature.color;
    this->feature.brand = feature.brand;
    this->feature.origin = feature.origin;
    this->feature.coverage = feature.coverage;
}
istream &operator>>(istream &is, Product &myProduct) {
    char tem;
    getline(is, myProduct.ID, '|');
    getline(is, myProduct.name, '|');
    is >> myProduct.price;
    is >> tem;
    is >> myProduct.quantity;
    is >> tem;
    getline(is, myProduct.feature.strap, '|');
    getline(is, myProduct.feature.color, '|');
    getline(is, myProduct.feature.brand, '|');
    getline(is, myProduct.feature.origin, '|');
    getline(is, myProduct.feature.coverage, '|');
    getline(is, myProduct.feature.gender, '|');
    getline(is, myProduct.feature.type, '|');
    is.ignore();
    return is;
}
