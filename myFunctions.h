#include"Customer.h"
#include"Product.h"
#include"Order.h"
#include"ProductOrder.h"
#include"StatisticReport.h"

#ifndef MYFUNCTION_H
#define MYFUNCTION_H
//map<string, Customer> customerList;
void FilestreamCustomer(map<string, Customer> customerList);
void CreateCustomer(map<string, Customer> customerList);
void myCreateCustomer();
void ReadCustomer(map<string, Customer> customerList);
void UpdateCustomer(map<string, Customer> customerList);
void DeleteCustomer(map<string, Customer> customerList);
#endif // MYFUNCTION_H


