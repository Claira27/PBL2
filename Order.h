    #ifndef ORDER_H
    #define ORDER_H

    #include<iostream>
    #include<fstream>
    #include<cstring>
    #include<ctime>
    #include<iomanip>
    #include<sstream>
    #include<vector>
    using namespace std;

    class Order
    {
        string ID;
        string customerID;
        string invoiceDate;
        double amountDue;
    public:
        //Get information
        string getID() const;
        string getCustomerID() const;
        string getInvoiceDate() const;
        double getAmountDue();
        //Mutator functions
        void setID(const string &ID);
        void setCustomerID(const string &customerID);
        time_t customStrToTime(const char* timeStr, const char* format);
        time_t setInvoiceDate(const string &invoiceDate);
        void setAmountDue(double amountDue);

        friend istream &operator>>(istream &is, Order &myOrder);


    };
    #endif // ORDER_H
