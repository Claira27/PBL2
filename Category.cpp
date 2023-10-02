#include"Category.h"

Category::Category() : ID(" "), name(" ")
{
    general.brand = " ";
    general.origin = " ";
    general.type = " ";
}
Category::Category(string ID, string name, Description general)
        : ID(ID), name(name)
{
    this->general.brand = general.brand;
    this->general.origin = general.origin;
    this->general.type = general.type;
}
//Get information
string Category::getID() const
{
    return ID;
}
string Category::getName() const
{
    return name;
}
Description Category::getGeneral() const
{
    return general;
}
//Mutator functions
void Category::setID(const string &ID)
{
    this->ID = ID;
}
void Category::setName(const string &name)
{
    this->name = name;
}
void Category::setGeneral(const Description &general)
{
    this->general.brand = general.brand;
    this->general.origin = general.origin;
    this->general.type = general.type;
}
istream &operator>>(istream &is, Category &myCategory)
{
    getline(is, myCategory.ID, ',');
    getline(is, myCategory.name, ',');
    getline(is, myCategory.general.brand, ',');
    getline(is, myCategory.general.origin, ',');
    getline(is, myCategory.general.type, ',');
    return is;
}
ostream &operator<<(ostream &os, const Category &myCategory)
{
    os<<setw(10)<<myCategory.ID<<"\t"<<myCategory.name<<"\t"<<myCategory.general.brand<<"\t"<<myCategory.general.origin<<"\t"<<myCategory.general.type<<endl;
    return os;
}
