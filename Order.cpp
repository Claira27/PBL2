#include"Order.h"
#include"Customer.h"
#include"Watch.h"
#include"OrderDetail.h"
#include"Product.h"
// ANSI color codes for text
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[31m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_YELLOW = "\033[33m";
const string ANSI_CYAN = "\033[36m";
const string ANSI_BOLD = "\033[1m";
const string ANSI_BLINK = "\033[5m";

int Order::numberOfOrder = 0;
map<string, Order> Order::orderList;
string Order::lastID = orderList.rbegin()->first;
Order::Order() : ID(" "), customerPhone(" "), invoiceDate(" "), amountDue(0) {}
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
    setAmountDue();
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
time_t customStrToTime(const char* timeStr, const char* format) {
    struct tm timeStruct = {};
    istringstream ss(timeStr);
    ss >> get_time(&timeStruct, format);
    return mktime(&timeStruct);
}
time_t Order::setInvoiceDate(const string &invoiceDate)
{
    // Chuyển đổi chuỗi ctime thành biến time_t
    this->invoiceDate = invoiceDate;
    const char* format = "%Y-%m-%d";
    return customStrToTime(invoiceDate.c_str(), format);
}
void Order::setAmountDue()
{
    double sum = 0;
    for(auto sale : OrderDetail::saleList)
    {
        string orderID = sale.second.getOrderID();
        if(this->ID == orderID)
        {
            //refer to primary key of watch through foreign key ID Serie in order detail
            string watchID = sale.second.getIDSerie();
            //refer to primary key of product through foreign key product ID in watch
            string productID = Watch::watchList.find(watchID)->second.getProductID();
            //get price of product
            sum += Product::productList.find(productID)->second.getPrice();
        }
    }
    this->amountDue = sum;
}
//Functions for CRUD
istream &operator>>(istream &is, Order &myOrder)
{
    is.ignore();
    getline(is,myOrder.ID, ',');
    getline(is,myOrder.customerPhone, ',');
    getline(is,myOrder.invoiceDate, ',');
    return is;
}
ostream &operator<<(ostream &os, Order &myOrder)
{
    string customerName = Customer::customerList.find(myOrder.getCustomerPhone())->second.getName();
    os<< ANSI_GREEN << myOrder.getID()<<"\t"<<myOrder.getCustomerPhone()<<"\t"<<customerName
    <<"\t"<<myOrder.getInvoiceDate()<<"\t"<<myOrder.getAmountDue()<< ANSI_RESET<<endl;
    return os;
}
void Order::OrderLoad()
{
    ifstream inputFile("Orders.txt");
    if (!inputFile)
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    Order order;
    while (inputFile >> order)
    {
        Order::orderList[order.getID()] = order; // Add a new order
    }
    inputFile.close();
}
int Order::getNumberOfOrder() {
    return numberOfOrder;
}
string Order::generateOrderID(const string &myid)
{
    int max_size = 6;
    string ID = "000000";
    int i = max_size - 1;
    while (i >= 0 && myid[i] == '9') i--;
    if (i >= 0)
    {
        ID[i] = myid[i] +1;
        for (int j = i + 1; j < max_size; j++) ID[j] = '0';
        return ID;
    }
    else
    {
        cout <<ANSI_YELLOW<< "Exceeded the allowed number of order" <<ANSI_RESET<< endl;
        return myid;
    }
}
void Order::ReadOrder()
{
    system("cls");
    cout << "Fetching order data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<< ANSI_CYAN <<"Order ID\tCustomer Phone\tCustomer name\tInvoice date\tAmount Due(VND)"<< ANSI_RESET<<endl;
    for(auto& pair : Order::orderList)
        cout<<pair.second;
}
void Order::FindOrder()
{
    system("cls");
    string ID;
    cout<<"Enter order ID: "; getline(cin, ID);
    auto currentOrder = Order::orderList.find(ID);
    if(currentOrder != Order::orderList.end())
    {
        cout<<currentOrder->second;
    }
    else
    {
        cout<<ANSI_YELLOW<<"Non-existing Order!"<<ANSI_RESET<<endl;
        return;
    }
}
void Order::CreateOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Orders.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new order
    int num;
    do
    {
        cout<<"Enter the number of new orders to create: ";
        cin>>num;
        if(num + stoi(orderList.rbegin()->first) > 999999)
        {
            cout<<ANSI_YELLOW << "Exceeded the allowed number of orders"<<ANSI_RESET << endl;
        }
    }while(num + stoi(lastID) > 999999);
    //Create new orders
    cin.ignore();
    while(num--)
    {
        // Get ID by generation
        string ID;
        if(Customer::customerList.empty())//initiate first order with ID 000000
            ID = "000000";
        else
            ID = generateOrderID(lastID);
        cout<<"Order "<<ID<<": "<<endl;

        // add new order's information
        Order newOrder;
        string customerPhone, invoiceDate;
        cout << "Enter customer Phone: ";
        getline(cin, customerPhone);

        //create a new customer if customer does not already exist
        if(!Customer::customerList.count(customerPhone))
        {
            cout<<ANSI_CYAN<<"This is new customer. Create new customer"<<ANSI_RESET<<endl;
            Customer::createNewCustomer(customerPhone);
        }

        //CREATE ORDER DETAIL
        OrderDetail::CreateSale(ID);

        // current time of generating the invoice
        time_t current_time = time(nullptr);
        invoiceDate = ctime(&current_time);

        //set new order
        newOrder.setID(ID);
        newOrder.setCustomerPhone(customerPhone);
        newOrder.setInvoiceDate(invoiceDate);
        newOrder.setAmountDue();
        orderList[ID] = newOrder;

        //Write new orders to file
        outputFile<<newOrder.getID()<<","
                  <<newOrder.getCustomerPhone()<<","
                  <<newOrder.getInvoiceDate()<<","
                  <<newOrder.getAmountDue()<<endl;
        lastID = orderList.rbegin()->first;
        numberOfOrder++;

    }

    outputFile.close();
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<<ANSI_GREEN<<"Information written to file."<<ANSI_RESET<<endl;
}
int Order::ReferenceConstraint(const string &ID)
{
    for(auto orderDetail : OrderDetail::saleList)
        if(orderDetail.second.getOrderID() == ID)
            return 1;
    return 0;
}
void Order::EraseOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Orders.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new order
    int num;
    do
    {
        cout<<"Enter the number of orders to erase: ";
        cin>>num;
        if(num > Order::numberOfOrder)
        {
            cout<<ANSI_YELLOW << "Exceeded the number of existing orders"<<ANSI_RESET << endl;
        }
    }while(num > Order::numberOfOrder);
    //erase order
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string ID;
        cout<<i<<". Order ID : "; getline(cin, ID);
        if(Order::orderList.count(ID))
        {
            if(!ReferenceConstraint(ID))
            {
                Order::orderList.erase(ID);
                Order::numberOfOrder--;
                i++;
            }
            else cout<<ANSI_YELLOW<<"Reference constraint!"<<ANSI_RESET<<endl;
        }
        else
        {
            cout<<ANSI_YELLOW<<"Non-existing order!"<<ANSI_RESET<<endl;
        }
    }
    //Overwriting the file to erase order
    outputFile<<endl;
    for(auto currentOrder : Order::orderList)
    {
        outputFile<<currentOrder.second.getID()<<","
                  <<currentOrder.second.getCustomerPhone()<<","
                  <<currentOrder.second.getInvoiceDate()<<","
                  <<currentOrder.second.getAmountDue()<<endl;
    }
    outputFile.close();
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<<ANSI_YELLOW<<num<<" Orders have been erased."<<ANSI_RESET<<endl;
}
void Order::UpdateOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Orders.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of order
    int num;
    do
    {
        cout<<"Enter the number of orders to update: ";
        cin>>num;
        if(num > Order::numberOfOrder)
        {
            cout<<ANSI_YELLOW << "Exceeded the number of existing orders"<<ANSI_RESET << endl;
        }
    }while(num > Order::numberOfOrder);
    //erase order
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string ID;
        cout<<i<<". Order ID : "; getline(cin, ID);
        if(Order::orderList.count(ID))
        {
            if(!ReferenceConstraint(ID))
            {
                Order newOrder;
                newOrder.setID(ID);
                newOrder.setCustomerPhone(Order::orderList.find(ID)->second.getCustomerPhone());
                newOrder.setInvoiceDate(Order::orderList.find(ID)->second.getInvoiceDate());
                OrderDetail::UpdateSale(ID);
                newOrder.setAmountDue();
                Order::orderList.erase(ID);
                Order::orderList[ID] = newOrder;
                i++;
            }
            else cout<<ANSI_YELLOW<<"Reference constraint!"<<ANSI_RESET<<endl;
        }
        else
        {
            cout<<ANSI_YELLOW<<"Non-existing order!"<<ANSI_RESET<<endl;
        }
    }
    //Overwriting the file to erase order
    outputFile<<endl;
    for(auto currentOrder : Order::orderList)
    {
        outputFile<<currentOrder.second.getID()<<","
                  <<currentOrder.second.getCustomerPhone()<<","
                  <<currentOrder.second.getInvoiceDate()<<","
                  <<currentOrder.second.getAmountDue()<<endl;
    }
    outputFile.close();
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<<ANSI_GREEN<<num<<" Orders have been erased."<<ANSI_RESET<<endl;
}
void Order::DeleteOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("OrderDetail.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    if(OrderDetail::saleList.empty())
    {
        orderList.clear();
        outputFile<<endl;
        cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
        sleep(2000000); // Sleep for 2 seconds
        cout<<ANSI_GREEN<<"You are order data is clear now!"<<ANSI_RESET<<endl;
    }
    else
    {
        int choice;
        cout<<ANSI_RED<<"Sale list is not empty, make sure you want to delete all sales data? (YES/NO):(1/0)"<<ANSI_RESET<<endl;
        cin>>choice;
        if(choice)
        {
                OrderDetail::DeleteSale();
                if(!OrderDetail::saleList.empty())
                {
                    cout<<ANSI_RED<<"Order data can not be cleared as sale list is still not empty!"<<ANSI_RESET<<endl;
                }
                else
                {
                    orderList.clear();
                    outputFile<<endl;
                    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
                    sleep(2000000); // Sleep for 2 seconds
                    cout<<ANSI_GREEN<<"You are order data is clear now!"<<ANSI_RESET<<endl;
                }
        }
        else return;
    }
    outputFile.close();
}
