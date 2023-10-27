#ifndef STATISTICREPORT_H
#define STATISTICREPORT_H

#include"Order.h"
#include"Category.h"
#include"Customer.h"
#include"OrderDetail.h"
#include"Product.h"
#include"Watch.h"
class StatisticsReport :public Order, public Category, public Customer, public OrderDetail, public Product, public Watch
{
public:
    // Report the quantity of products by category
    static void ProductByCategory();
    // Report the number of customers and the total number of orders
    static void CustomerAndOrderStatistics();
    // Report the number of orders by each day
    static void OrdersByDay();
    // Report the number of orders by each month
    static void OrdersByMonth();
    // Report the number of orders by each quarter
    static void OrdersByQuarter();
    // Report the number of orders by each year
    static void OrdersByYear();
    // Revenue report by each month
    static void RevenueByMonth();
    // Revenue report by each quarter
    static void RevenueByQuarter();
    //Revenue report by each year
    static void RevenueByYear();
    //Best-selling product of the year
    static void BestSellingProductInYear();
    //manage inventory quantity by product
    static void InventoryByProduct();
};

#endif // STATISTICREPORT_H
