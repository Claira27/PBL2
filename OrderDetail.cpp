#include"OrderDetail.h"

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
istream &operator>>(istream &is, OrderDetail &myOrderDetail)
{
    getline(is,myOrderDetail.orderID, '|');
    getline(is,myOrderDetail.IDserie, '|');
    getline(is,myOrderDetail.warranty.expiry, '|');
    getline(is,myOrderDetail.warranty.coverage, '|');
    is.ignore();
    return is;
}
