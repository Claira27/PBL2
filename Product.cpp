#include"Product.h"

Product::Product() : ID(" "), categoryID(" "), name(" "), price(0), availability(false) {}
Product::Product(const string ID, const string categoryID, const string &name, const double &price, const bool availability)
    : ID(ID), categoryID(categoryID), name(name), price(price), availability(availability) {}
//Get information
string Product::getID() const
{
    return ID;
}
string Product::getCategoryID() const
{
    return categoryID;
}
string Product::getName() const
{
    return name;
}
double Product::getPrice() const
{
    return price;
}
bool Product::getAvailability() const
{
    return availability;
}
//Mutator functions
void Product::setID(const string &ID)
{
    this->ID = ID;
}
void Product::setCategoryID(const string &categoryID)
{
    this->categoryID = categoryID;
}
void Product::setName(const string &name)
{
    this->name = name;
}
void Product::setPrice(const double &price)
{
    this->price = price;
}
void Product::ProductsetAvailability(const bool availability)
{
    this->availability = availability;
}
Watch::Watch() : Product()
{
    feature.size = 0;
    feature.color = " ";
    feature.parameter = " ";
}
Watch::Watch(const string ID, const string categoryID, const string &name,const double &price, const bool availability, const Description &feature)
        : Product(const string ID, const string categoryID, const string &name,const double &price, const bool availability)
{
    this->feature.size = feature.size;
    this->feature.color = feature.color
    this->feature.parameter = feature.parameter;
}
Description Watch::getFeature() const
{
    return feature;
}
void Watch::setFeature(const Description &feature)
{
    this->feature.size = feature.size;
    this->feature.color = feature.color
    this->feature.parameter = feature.parameter;
}
istream &operator>>(istream &is, Watch &myWatch)
{
    getline(is, myWatch.ID, ',');
    getline(is, myWatch.categoryID, ',');
    getline(is,myWatch.name, ',');
    is>>myWatch.price;
    is>>myWatch.availability;
    getline(is, myWatch.feature.parameter, ',');
    is>>myWatch.feature.size;
    getline(is, myWatch.feature.color, ',');
    return is;
}
ostream &operator<<(ostream &os, const Watch &myWatch)
{
    os<<setw(10)<<myWatch.ID<<"\t"<<myWatch.categoryID<<"\t"<<myWatch.name<<"\t"<<myWatch.price<<"\t"<<myWatch.availability;
    os<<"\t"<<myWatch.feature.parameter<<"\t"<<myWatch.feature.size<<"\t"<<myWatch.feature.color<<endl;
    return os;
}
