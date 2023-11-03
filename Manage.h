#ifndef MANAGE_H
#define MANAGE_H

#include"Order.h"
#include"Category.h"
#include"Customer.h"
#include"OrderDetail.h"
#include"Product.h"
#include"Watch.h"

class Manage
{
    //Category
    vector<Category> categoryList;
    int numberOfCategory = 0;

    //Product
     vector<Product> productList;
    int numberOfProduct = 0;

    //Product detail
    vector<Watch> watchList;
    int numberOfWatch = 0;
public:
    //Category
    bool CategoryLoad();
    int getNumberOfCategory();
    vector<Category> ReadCategory();
    bool FindCategory(string categoryID);
    bool CreateCategory(string categoryID, string name);
    bool ReferenceConstraint_Category(string ID);
    bool EraseCategory(string categoryID);
    bool UpdateCategory(string categoryID, string name);

    //Product
    bool ProductLoad();
    int getNumberOfProduct();
    vector<Product> ReadProduct();
    bool FindProduct(string ID);
    bool CreateProduct(string ID, string name, double price, Description feature, int quantity = 0);
    bool Eraseproduct(string ID);
    bool UpdateProduct(string currentID, string newID, string name, double price, Description feature, int quantity = 0);

    //Product detail
    bool WatchLoad();
    int getNumberOfWatch();
    vector<Watch> ReadWatch();
    bool FindWatch(string ID);
    bool CreateWatch(const string &productID, const string &serie, bool avail);
    bool ReferenceConstraint_Watch(const string& ID);
    bool EraseWatch(const string &productID, const string &serie);
    bool UpdateWatch(const string &ID, bool avail);
};
#endif // MANAGE_H
