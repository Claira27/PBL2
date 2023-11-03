#include"Product.h"
#include"Manage.h"

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
void Product::setQuantity()
{
    int count = 0;
    for(auto watch : Manage::watchList)
        if(watch.getAvailability())
            count++;
    this->quantity = count;
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
    int check1=0, check2=0;
    this->feature.gender = "NULL";
    for(auto genderID : Manage::categoryList)
        if(feature.gender == genderID.getName())
        {
            this->feature.gender = genderID.getID();
            check1 = 1;
        }

    this->feature.type = "NULL";
    for(auto typeID : Manage::categoryList)
        if(feature.type == typeID.getName())
        {
            this->feature.type = typeID.getID();
            check2 = 1;
        }

    this->feature.strap = feature.strap;
    this->feature.color = feature.color;
    this->feature.brand = feature.brand;
    this->feature.origin = feature.origin;
}
istream &operator>>(istream &is, Product &myProduct)
{
    is.ignore();
    getline(is,myProduct.ID, ',');
    getline(is,myProduct.name, ',');
    is>>myProduct.price>>myProduct.quantity;
    getline(is, myProduct.feature.strap, ',');
    getline(is, myProduct.feature.color, ',');
    getline(is, myProduct.feature.brand, ',');
    getline(is, myProduct.feature.origin, ',');
    getline(is, myProduct.feature.gender, ',');
    getline(is, myProduct.feature.type, ',');
    return is;
}
