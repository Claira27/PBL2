#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include"StatisticReport.h"
//Customer
class myFunction : public Order, public Category, public Customer, public OrderDetail, public Product, public Watch
{
    static int ReferConstraint_Customer(const string &phone);
    static void EraseCustomer();
    static string UpdateCustomer(string phone);
    static void FindCustomer();

    //Orderdetail
    static void ReadSale();
    static void saleDetail(string orderID);
    static void CreateSale(const string &orderID, time_t time);
    static void EraseSale(const string &orderID);
    static void DeleteSale();
    //void UpdateSale(const string &orderID);

    //Order
    static string generateOrderID(const string &myid);
    static void ReadOrder();
    static void FindOrder();
    static void CreateOrder();
    static int ReferConstraint_Order(const string &ID);
    static void EraseOrder();
    static void DeleteOrder();
    //void UpdateOrder();
    static double AmountDue(string orderID);
    //Warranty myWarranty(time_t time);
    static void gotoxy(int x, int y);
    static void delay(int milliseconds);
    static void runMessage(string message);
    static int enterPassword();
    static void printOder(Order myOrder);
    // Function prototypes
    static void displayMainMenu();

    static void myLoad();
    static void myCustomer();
    static void myCategory();
    static void myProduct();
    static void myOrder();
    static void myStatisticReport();
    static void Title();
    static void Execute_Menu();
public:
    static void Run();
    static void layout(int site,int page);
    static void display();
    static void drawProductList(int page);
};

#endif // MYFUNCTION_H
