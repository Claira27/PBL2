#ifndef MANAGE_H
#define MANAGE_H

#include"Order.h"
#include"Category.h"
#include"Customer.h"
#include"OrderDetail.h"
#include"Product.h"
#include"Watch.h"
struct productInf;
struct myOrder;
struct productByCategory;
struct customerAndOrder;
struct ordersByDay;
struct ordersByMonth;
struct ordersByQuarter;
struct ordersByYear;
struct revenueByMonth;
struct revenueByQuarter;
struct revenueByYear;
struct inventoryByProduct;
class Manage
{
    //Category
    vector<Category> categoryList;
    int numberOfCategory;

    //Product
    vector<Product> productList;
    int numberOfProduct;

    //Product detail
    vector<Watch> watchList;
    int numberOfWatch;

    //Customer
    int numberOfCustomer;
    string lastID_customer;
    vector<Customer> customerList;

    //Order
    int numberOfOrder;
    string lastID_order;
    vector<Order> orderList;

    //OrderDetail
    int numberOfSales;// the number of watches sold out
    vector<OrderDetail> saleList;
public:
    //Category
    Manage();
    bool CategoryLoad();
    int getNumberOfCategory();
    vector<Category> ReadCategory();
    vector<Category> getCategoryList();
    bool FindCategory(string categoryID);
    vector<Category> SearchCategory(string name);
    bool ReferenceConstraint_Product(string ID);
    bool CreateCategory(string categoryID, string name);
    bool ReferenceConstraint_Category(string ID);
    bool EraseCategory(string categoryID);
    bool UpdateCategory(string currentID, string name);
    bool ClearData_Category();

    //Product
    bool ProductLoad();
    int getNumberOfProduct();
    vector<Product> getProductList();
    vector<Product> ReadProduct();
    bool FindProduct(string ID);
    vector<Product> SearchProduct(string name);
    bool CreateProduct(string ID, string name, double price, Description feature, vector<string> series);
    bool Eraseproduct(string ID);
    bool UpdateProduct(string ID, string name, double price, Description feature);
    bool ClearData_Product();

    //Product detail
    bool WatchLoad();
    int getNumberOfWatch();
    vector<Watch> getWatchList();
    vector<Watch> ReadWatch(string productID);
    bool FindWatch(string ID);

    //Customer
    bool CustomerLoad();
    int getNumberOfCustomer();
    vector<Customer> getCustomerList();
    vector<Customer> ReadCustomer();
    bool FindCustomer(const string &phone);
    vector<Customer> SearchCustomer(string phone);
    bool ReferConstraint_Customer(const string &ID);
    bool CreateCustomer(const string &phone, const string &name);
    bool EraseCustomer(const string &phone);
    bool UpdateCustomer(const string &Phone, const string &newPhone, const string &name);

    //Order
    bool OrderLoad();
    int getNumberOfOrder();
    vector<Order> getOrderList();
    string generateOrderID(const string &myid);
    vector<Order> ReadOrder();
    bool FindOrder(const string &ID);
    double AmountDue(vector<myOrder>);
    bool CreateOrder(const string &customerPhone, const string &customerName, vector<myOrder> order);
    bool ReferConstraint_Order(const string &ID);
    bool EraseOrder(const string &ID);
    bool CancelOrder(const string &ID);
    bool ClearData_Order();

    //OrderDetail
    bool SaleLoad();
    int getNumberOfSales();
    vector<OrderDetail> getSaleList();
    vector<OrderDetail> ReadSale(string orderID);
    bool FindSale(string ID);
    Warranty myWarranty(time_t time, string coverage);
    bool CreateSale(const string &orderID, const string &productID, const int number, time_t time, string coverage);
    bool EraseSale(const string &orderID);

    bool ClearData();
    //SatisticReport
    // Report the quantity of products by category
    vector<productByCategory> ProductByCategory();
    // Report the number of customers and the total number of orders
    customerAndOrder CustomerAndOrderStatistics();
    // Report the number of orders by each day
    vector<ordersByDay> OrdersByDay();
    // Report the number of orders by each month
    int monthSwitch(string month);
    vector<ordersByMonth> OrdersByMonth();
    // Report the number of orders by each quarter
    vector<ordersByQuarter> OrdersByQuarter();
    // Report the number of orders by each year
    vector<ordersByYear> OrdersByYear();
    // Revenue report by each month
    vector<revenueByMonth> RevenueByMonth();
    // Revenue report by each quarter
    vector<revenueByQuarter> RevenueByQuarter();
    //Revenue report by each year
    vector<revenueByYear> RevenueByYear();
    //Best-selling product of the year
    Product BestSellingProductInYear(string year);
    //manage inventory quantity by product
    vector<inventoryByProduct> InventoryByProduct();
};

struct myOrder
{
    string ID;
    int number;
};
struct productByCategory
{
    Category category;
    vector<Product> products;
};
struct customerAndOrder
{
    int numberOfCustomer;
    int numberOfSale;
};
struct ordersByDay
{
    string day;
    int numberOfOrder;
};
struct ordersByMonth
{
    string month;
    int numberOfOrder;
};
struct ordersByQuarter
{
    string quarter;
    int numberOfOrder;
};
struct ordersByYear
{
    string year;
    int numberOfOrder;
};
struct revenueByMonth
{
    string month;
    double revenue;
};
struct revenueByQuarter
{
    string quarter;
    double revenue;
};
struct revenueByYear
{
    string year;
    double revenue;
};
struct inventoryByProduct
{
    Product product;
    int quantity;
};
#endif // MANAGE_H
