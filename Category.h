#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<map>
using namespace std;

#ifndef CATEGORY_H
#define CATEGORY_H
class Category
{
    //Type and sex
    string ID;
    string name;
public:
    static map<string, Category> categoryList;
    static int numberOfCategory;
    Category();
    Category(const string &ID, const string &name);
    //Get information
    string getID() const;
    string getName() const;
    //Mutator functions
    void setID(const string &ID);
    void setName(const string &name);
    //Functions for CRUD
    friend istream &operator>>(istream &is, Category &myCategory);
    friend ostream &operator<<(ostream &os, const Category &myCategory);
    static void CategoryLoad();
    static int getNumberOfCategory();
    static void ReadCategory();
    static void FindCategory();
    static void CreateCategory();
    static int ReferenceConstraint(string ID);
    static void EraseCategory();
    static void UpdateCategory();
};
#endif // CATEGORY_H
