#ifndef CATEGORY_H
#define CATEGORY_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<vector>

using namespace std;

class Product;
class Category
{
    //Type and sex
    string ID;
    string name;
public:
    friend class Product;
    Category();
    Category(const string &ID, const string &name);
    //Get information
    string getID() const;
    string getName() const;
    void setID(const string &ID);
    void setName(const string &name);
    friend istream &operator>>(istream &is, Category &myCategory);


};
#endif // CATEGORY_H
