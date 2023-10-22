#include"OrderDetail.h"
#include"Order.h"
#include"Product.h"
#include"Watch.h"

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
Warranty OrderDetail::getWarranty() const
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
void OrderDetail::setWarranty()
{
//set time expire after 2 years
    map<string, Order>::iterator currentOrder = Order::orderList.find(orderID);
    //warranty period: 2 years
    int period = 2;
    time_t invoiceDate = currentOrder->second.setInvoiceDate(currentOrder->second.getInvoiceDate());//date of purchasing
    struct tm timeinfo = *localtime(&invoiceDate);
    timeinfo.tm_year += period;// add 2 years
    time_t newtime = mktime(&timeinfo);
    this->warranty.expiry = ctime(&newtime);// cout << ctime(&newtime)
//set warranty coverage
    string coverage;
    cout<<"Enter coverage of this product, enter none if this warranty does cover nothing: ";
    getline(cin, coverage);
    this->warranty.coverage = coverage;
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
    os<<myOrderDetail.ID<<"\t"<<myOrderDetail.orderID<<"\t"<<myOrderDetail.IDserie<<"\t"
    <<myOrderDetail.warranty.expiry<<"\t"<<myOrderDetail.warranty.coverage<<endl;
    return os;
}
void OrderDetail::SaleLoad()
{
    ifstream inputFile("OrderDetail.txt");
    if (!inputFile)
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    OrderDetail orderdetail;
    while (inputFile >> orderdetail)
    {
        orderdetail.setID();
        saleList[orderdetail.getID()] = orderdetail; // Add a new customer
        sales++;
    }
    cout << "Information uploaded from file." << endl;
    inputFile.close();
}
int OrderDetail::getSales()
{
    return sales;
}
void OrderDetail::ReadSale()
{
    for(const auto& pair : saleList)
        cout<<pair.second;
}
void OrderDetail::FindSale()
{
    string ID;
    cout<<"Finding sale ID: "; getline(cin, ID);
    auto currentSale = saleList.find(ID);
    if(currentSale != saleList.end())
    {
        cout<<currentSale->second;
    }
    else
    {
        cout<<"Non-existing sale ID"<<endl;
        return;
    }
}
void OrderDetail::CreateSale(const string &orderID)
{
    ofstream outputFile;
    outputFile.open("OrderDetail.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of new sales
    int num;
    do
    {
        cout<<"Enter the number of sales of order "<<orderID<<": ";
        cin>>num;
        if(num > 50)
        {
            cout << "Exceeded the allowed number of new sales to be created mutually, stream file instead!" << endl;
        }
    }while(num  > 50);
    //Create new sales

    cin.ignore();
    int i = num;
    while(i)
    {
        string productID;
        cout << "Enter productID: "; getline(cin, productID);
        if(Product::productList.count(productID))
        {
            int number;
            cout << "Enter number: ";
            cin>>number;
            if(number > i) cout<<"Exceeding the number of sales of this order"<<endl;
            else
            {
                if(number > Product::productList.find(productID)->second.getQuantity()) cout<<"Insufficient stock to sell"<<endl;
                else
                {
                    set<string> currentSales;
                    currentSales.insert(productID);
                    map<string, Watch> :: iterator watch = Watch::watchList.begin();
                    int j = number;
                    while(j)
                    {
                        if(watch->second.getProductID() == productID && watch->second.getAvailability())
                        {
                            OrderDetail newSale;
                            newSale.setOrderID(orderID);
                            newSale.setIDSerie(watch->second.getID());
                            newSale.setID();
                            saleList[newSale.getID()] = newSale;
                            watch->second.setAvailability(false);
                            //Write new sales to file
                            outputFile<<newSale.getOrderID()<<","
                                      <<newSale.getIDSerie()<<","
                                      <<newSale.getWarranty().expiry<<","
                                      <<newSale.getWarranty().coverage<<","<<endl;
                            sales++;
                            j--;
                        }
                        watch++;
                    }
                    i -= number;
                }
            }
        }
        else
            cout<<"Non-existing product!"<<endl;
    }
    Watch::UpdateWatch();
    outputFile.close();
    cout<<"Information written to file."<<endl;
}
void OrderDetail::EraseSale(const string& orderID)
{
    ofstream outputFile;
    outputFile.open("OrderDetail.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    for(auto sale : saleList)
    {
        if(sale.second.getOrderID() == orderID) saleList.erase(sale.first);
    }
    outputFile<<endl;
    for(auto currentSale : saleList)
    {
        outputFile<<currentSale.second.getOrderID()<<","
                  <<currentSale.second.getIDSerie()<<","
                  <<currentSale.second.getWarranty().expiry<<","
                  <<currentSale.second.getWarranty().coverage<<","<<endl;
    }
    outputFile.close();
}
void OrderDetail::DeleteSale()
{
    ofstream outputFile;
    outputFile.open("OrderDetail.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    saleList.clear();
    outputFile<<endl;
    outputFile.close();
}
void OrderDetail::UpdateSale(const string &orderID)
{
    for(auto sale : saleList)
    {
        if(sale.second.getOrderID() == orderID)
        {
            Watch::watchList.find(sale.second.getIDSerie())->second.setAvailability(true);
            saleList.erase(sale.first);
        }
    }
    CreateSale(orderID);
}
