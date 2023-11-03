#include"Category.h"
#include"Product.h"

//construction
Category::Category(): ID(" "), name(" ") {}
Category::Category(const string &ID, const string &name) :
    ID(ID), name(name) {}
//Get information
string Category::getID() const
{
    return ID;
}
string Category::getName() const
{
    return name;
}
//Mutator functions
void Category::setID(const string &ID)
{
    this->ID=ID;
}
void Category::setName(const string &name)
{
    this->name=name;
}
//Functions for CRUD
istream &operator>>(istream &is, Category &myCategory)
{
    is.ignore();
    getline(is,myCategory.ID, ',');
    getline(is,myCategory.name, ',');
    return is;
}
