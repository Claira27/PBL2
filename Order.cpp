#include"Order.h"

// ANSI color codes for text
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[31m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_YELLOW = "\033[33m";
const string ANSI_CYAN = "\033[36m";
const string ANSI_BOLD = "\033[1m";
const string ANSI_BLINK = "\033[5m";

int Order::numberOfOrder = 0;
string Order::lastID = "0000";
map<string, Order> Order::orderList;
//Get information
string Order::getID() const
{
    return ID;
}
string Order::getCustomerPhone() const
{
    return customerPhone;
}
string Order::getInvoiceDate() const
{
    return invoiceDate;
}
double Order::getAmountDue()
{
    return amountDue;
}
//Mutator functions
void Order::setID(const string &ID)
{
    this->ID = ID;
}
void Order::setCustomerPhone(const string &customerPhone)
{
    this->customerPhone= customerPhone;
}
void Order::setAmountDue(double amountDue)
{
    this->amountDue = amountDue;
}

time_t Order::customStrToTime(const char* timeStr, const char* format) {
    struct tm timeStruct = {};
    istringstream ss(timeStr);
    ss >> get_time(&timeStruct, format);
    return mktime(&timeStruct);
}
time_t Order::setInvoiceDate(const string &invoiceDate)
{
    this->invoiceDate = invoiceDate;
    const char* format = "%Y-%m-%d %H:%M:%S";
    struct tm timeStruct = {};

    if (sscanf(invoiceDate.c_str(), "%d-%d-%d %d:%d:%d",
               &timeStruct.tm_year, &timeStruct.tm_mon, &timeStruct.tm_mday,
               &timeStruct.tm_hour, &timeStruct.tm_min, &timeStruct.tm_sec) == 6) {
        // Điều chỉnh giá trị tháng và năm.
        timeStruct.tm_year -= 1900; // Năm là năm - 1900.
        timeStruct.tm_mon -= 1;    // Tháng là 0-11.

        return mktime(&timeStruct);
    } else {
        return 0; // Giá trị mặc định, có thể sửa đổi tùy ý.
    }
}

//Functions for CRUD
istream &operator>>(istream &is, Order &myOrder)
{
    is.ignore();
    getline(is,myOrder.ID, ',');
    getline(is,myOrder.customerPhone, ',');
    getline(is,myOrder.invoiceDate, ',');
    is>>myOrder.amountDue;
    return is;
}

void Order::OrderLoad()
{
    ifstream inputFile("Orders.txt");
    if (!inputFile)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
    }
    Order order;
    while (inputFile >> order)
    {
        orderList[order.getID()] = order; // Add a new order
        numberOfOrder++;
        //string lineFeed;
        //inputFile>>lineFeed;
    }
    inputFile.close();
    if (!orderList.empty())
    {
        lastID = orderList.rbegin()->first;
    }

}
int Order::getNumberOfOrder() {
    return numberOfOrder;
}
