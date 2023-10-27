#include"OrderDetail.h"

// ANSI color codes for text
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[31m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_YELLOW = "\033[33m";
const string ANSI_CYAN = "\033[36m";
const string ANSI_BOLD = "\033[1m";
const string ANSI_BLINK = "\033[5m";

int OrderDetail::sales = 0;// the number of watches sold out
map<string,OrderDetail> OrderDetail::saleList;

OrderDetail::OrderDetail() : ID(" "), orderID(" "), IDserie(" ") {}
//Get information
string OrderDetail::getID() const
{
    return ID;
}
string OrderDetail::getOrderID() const
{
    return orderID;
}
string OrderDetail::getIDSerie() const
{
    return IDserie;
}
Warranty OrderDetail::getWarranty()
{
    return warranty;
}
//mutator function
void OrderDetail::setID()
{
    this->ID = orderID + IDserie;
}
void OrderDetail::setOrderID(const string &orderID)
{
    this->orderID = orderID;
}
void OrderDetail::setIDSerie(const string &IDserie)
{
    this->IDserie = IDserie;
}
void OrderDetail::setWarranty(Warranty warranty)
{
    this->warranty = warranty;
}
//Functions for CRUD
istream &operator>>(istream &is, OrderDetail &myOrderDetail)
{
    is.ignore();
    getline(is,myOrderDetail.orderID, ',');
    getline(is,myOrderDetail.IDserie, ',');
    getline(is,myOrderDetail.warranty.expiry, ',');
    getline(is,myOrderDetail.warranty.coverage, ',');
    return is;
}
ostream &operator<<(ostream &os, const OrderDetail &myOrderDetail)
{
    os<<setw(2)<<"|"<< ANSI_GREEN<<setw(8)<<left<<myOrderDetail.orderID<<ANSI_RESET<<setw(3)<<left<<"|"<< ANSI_GREEN<<setw(25)<<left<<myOrderDetail.IDserie
    <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_GREEN<<setw(30)<<left<<myOrderDetail.warranty.expiry<<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_GREEN<<setw(16)<<left<<myOrderDetail.warranty.coverage<< ANSI_RESET<<"|"<<endl;
    return os;
}
void OrderDetail::SaleLoad()
{
    ifstream inputFile("OrderDetail.txt");
    if (!inputFile)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    OrderDetail orderdetail;
    while (inputFile >> orderdetail)
    {
        orderdetail.setID();
        saleList[orderdetail.getID()] = orderdetail; // Add a new customer
        sales++;
    }
    inputFile.close();
}
int OrderDetail::getSales()
{
    return sales;
}
