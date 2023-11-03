#include"Watch.h"

Watch::Watch() : productID("NULL"), serie(" "), availability(false){}
Watch::Watch(const string &productID, const string &serie, const bool avail) :
    productID(productID), serie(serie), availability(avail) {}
//Get information
void Watch::setID()
{
    this->ID = productID + serie;
}
string Watch::getID()
{
    setID();
    return ID;
}
string Watch::getProductID() const
{
    return productID;
}
string Watch::getSerie() const
{
    return serie;
}
bool Watch::getAvailability() const
{
    return availability;
}
//Mutator functions

void Watch::setProductID(string productID)
{
    this->productID = productID;
}
void Watch::setSerie(string serie)
{
    this->serie = serie;
}
void Watch::setAvailability(bool avail)
{
    this->availability = avail;
}

//Functions for CRUD
istream &operator>>(istream &is, Watch &myWatch)
{
    is.ignore();
    getline(is,myWatch.productID, ',');
    getline(is,myWatch.serie, ',');
    is>>myWatch.availability;
    return is;
}
