#ifndef CATEGORY_H
#define CATEGORY_H

#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<iomanip>
#include<cstdlib> // For system("cls")
#include<unistd.h> // For sleep (sleep function on Unix-like systems)
#include<windows.h>
#include<vector>
#include<map>
#include<set>
using namespace std;
// ANSI color codes for text
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[31m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_YELLOW = "\033[33m";
const string ANSI_CYAN = "\033[36m";
const string ANSI_BOLD = "\033[1m";
const string ANSI_BLINK = "\033[5m";

class Product;
class Category
{
    //Type and sex
    string ID;
    string name;
protected:
    static map<string, Category> categoryList;
    static int numberOfCategory;
public:
    friend class Product;
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
