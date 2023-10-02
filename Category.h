#include"Date.h"
using namespace std;

#ifndef CATEGORY_H
#define CATEGORY_H
struct Description
{
    string brand;
    string origin;
    string type;// daily dress complicated pilot field dive racing travel luxury other
};
class Category
{
    string ID;
    string name;
    Description general;
public:
    Category();
    Category(string ID, string name, Description general);
    //Get information
    string getID() const;
    string getName() const;
    Description getGeneral() const;
    //Mutator functions
    void setID(const string &ID);
    void setName(const string &name);
    void setGeneral(const Description &general);
    friend istream &operator>>(istream &is, Category &myCategory);
    friend ostream &operator<<(ostream &os, const Category &myCategory);
};
#endif // CATEGORY_H
