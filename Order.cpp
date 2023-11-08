#include"Order.h"

//Get information
string Order::getID() const
{
    return ID;
}
string Order::getCustomerID() const
{
    return customerID;
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
void Order::setCustomerID(const string &customerID)
{
    this->customerID = customerID;
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
    char tem;
    getline(is,myOrder.ID, '|');
    getline(is,myOrder.customerID, '|');
    getline(is,myOrder.invoiceDate, '|');
    is>>myOrder.amountDue;
    is>>tem;
    is.ignore();
    return is;
}
