    #ifndef ORDER_H
    #define ORDER_H

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

    class Order
    {
        string ID;
        string customerPhone;
        string invoiceDate;
        double amountDue;
    protected:
        static int numberOfOrder;
        static string lastID;
        static map<string, Order> orderList;
    public:
        //Get information
        string getID() const;
        string getCustomerPhone() const;
        string getInvoiceDate() const;
        double getAmountDue();
        //Mutator functions
        void setID(const string &ID);
        void setCustomerPhone(const string &customerPhone);
        time_t customStrToTime(const char* timeStr, const char* format);
        time_t setInvoiceDate(const string &invoiceDate);
        void setAmountDue(double amountDue);
        //Functions for CRUD
        friend istream &operator>>(istream &is, Order &myOrder);
        static void OrderLoad();
        static int getNumberOfOrder();

    };
    #endif // ORDER_H
