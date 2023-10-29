#include"myFunctions.h"
int myFunction::ReferConstraint_Customer(const string &phone)
{
    for(auto order : Order::orderList)
    if(phone == order.second.getCustomerPhone())
        return 1;
    return 0;
}
void myFunction::FindCustomer()
{
    //system("cls");
    string phone;
    cin.ignore();
    cout<< "\t\t\t\t\t\t"<<"Enter finding customer phone: "; getline(cin, phone);
    auto currentCustomer = customerList.find(phone);
    if(currentCustomer != customerList.end())
    {
        cout<< "\t\t\t\t\t\t"<<currentCustomer->second;
        for(auto order : Order::orderList)
        {
            Order myOrder = order.second;
            if(phone == myOrder.getCustomerPhone())
            {
                cout<< "\t\t\t\t\t\t"<< ANSI_GREEN <<setw(16)<<left<< myOrder.getID()<<setw(34)<<left<<myOrder.getInvoiceDate()
                <<setw(10)<<left<<myOrder.getAmountDue()<< ANSI_RESET<<endl;
            }
            getch();
        }
    }
    else
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing customer!"<< ANSI_RESET<<endl;
        Sleep(1000);
        return;
    }
}
void myFunction::EraseCustomer()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
        return;
    }
    //Enter the number of customers to erase
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of customers to erase: ";
        cin>>num;
        if(num  > Customer::numberOfCustomer)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Exceeded the number of existing customers" << ANSI_RESET<< endl;
        }
    }while(num > Customer::numberOfCustomer);
    //erase customers
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string phone;
        cout<< "\t\t\t\t\t\t"<<i<<". Customer phone : "; getline(cin, phone);
        if(Customer::customerList.count(phone))
        {
            if(!ReferConstraint_Customer(phone))
            {
                Customer::customerList.erase(phone);
                Customer::numberOfCustomer--;
                i++;
            }
            else
            {
                cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
                i++;
            }
        }
        else
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing customer!"<< ANSI_RESET<<endl;
            i++;
        }
    }
    //Overwriting the file to erase customers
    outputFile<<endl;
    for(auto currentCustomer : Customer::customerList)
    {
        outputFile<<currentCustomer.second.getPhone()<<","
                  <<currentCustomer.second.getName()<<","<<endl;
    }
    cout<< "\t\t\t\t\t\t" << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000);
    //cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<num<<" Customers have been erased."<< ANSI_RESET<<endl;
    //Sleep(1000); // Sleep for 2 seconds
    outputFile.close();

}

string myFunction::UpdateCustomer(string phone)
{
    //Update customers
    cin.ignore();
    Customer::customerList.erase(phone);
    Customer newCustomer;
    string name, newPhone;
    cout<< "\t\t\t\t\t\t" << "Enter customer name: ";
    getline(cin, name);
    do
    {
        cout<< "\t\t\t\t\t\t" << "Enter customer phone: ";
        getline(cin, newPhone);
        if(Customer::customerList.count(newPhone))
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"This customer phone already existed, enter another phone!"<<ANSI_RESET<<endl;
    }while(Customer::customerList.count(newPhone));
    newCustomer.setPhone(newPhone);
    newCustomer.setName(name);
    Customer::customerList[newPhone] = newCustomer;

    //Overwriting the file to update customers
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED <<"Error: Unable to open the file."<< ANSI_RESET<<endl;
        return phone;
    }

    outputFile<<endl;
    for(auto currentCustomer : Customer::customerList)
        outputFile<<currentCustomer.second.getPhone()<<","
                  <<currentCustomer.second.getName()<<","<<endl;
    outputFile.close();
    return newPhone;
}
Warranty myWarranty(time_t time)
{
    Warranty warranty;

    // Warranty period: 2 years
    int period = 2;

    // Calculate the expiry date
    time_t invoiceDate = time;
    struct tm timeinfo = *localtime(&invoiceDate);
    timeinfo.tm_year += period; // Add 2 years
    time_t newtime = mktime(&timeinfo);
    string expiryDue = ctime(&newtime);
    if (!expiryDue.empty() && expiryDue.back() == '\n') {
        // cut out last line feed character of time string
        expiryDue.pop_back();
        }
    warranty.expiry =expiryDue;

    // Set warranty coverage
    string coverage;
    cout << "\t\t\t\t\t"<< "Enter coverage of this product. Enter 'none' if this warranty does not cover anything: ";
    getline(cin, coverage);

    warranty.coverage = coverage;

    return warranty;
}
void myFunction::ReadSale()
{
    cout << "\t\t\t\t"<< "Fetching order detail data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 2 seconds
    cout<< "\t\t\t\t"<<ANSI_YELLOW<<setw(10)<<left<<"======================Sales information===================="<<ANSI_RESET<<endl;
    cout<<endl;
    cout<< "\t\t\t\t"<<setw(2)<<left<<"|"<< ANSI_CYAN <<setw(8)<<left<<"Order ID"
        <<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_CYAN<<setw(20)<<left<<"IDserie"
        <<ANSI_RESET<<setw(10)<<left<<"|"<< ANSI_CYAN<<setw(24)<<left<<"Expiry Due"
        <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(16)<<left<<"Coverage"<< ANSI_RESET<<"|"<<endl;
    for(const auto& pair : OrderDetail::saleList)
    {
        cout<< "\t\t\t\t"<<"-----------------------------------------------------------------------------------------------"<<endl;
        cout<<pair.second;
    }
    cout<< "\t\t\t\t"<<"-----------------------------------------------------------------------------------------------"<<endl;
    getch();
}

void myFunction::CreateSale(const string &orderID, time_t time)
{

    ofstream outputFile;
    outputFile.open("OrderDetail.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new sales
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of sales of order "<<orderID<<": ";
        cin>>num;
        if(num > 50)
        {
            cout<< "\t\t\t"<<ANSI_YELLOW << "Exceeded the allowed number of new sales to be created mutually, stream file instead!"<<ANSI_RESET << endl;
        }
    }while(num  > 50);
    //Create new sales

    cin.ignore();
    int i = num;
    while(i>0)
    {
        string productID;
        cout << "\t\t\t\t\t\t"<< "Enter productID: "; getline(cin, productID);
        if(Product::productList.count(productID))
        {
            int number;
            cout << "\t\t\t\t\t\t"<< "Enter number: ";
            cin>>number;
            if(number > i) cout<< "\t\t\t\t\t\t"<<ANSI_RESET<<"Exceeding the number of sales of this order"<<ANSI_RESET<<endl;
            else
            {
                if(number > Product::productList.find(productID)->second.getQuantity())
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Insufficient stock to sell"<<ANSI_RESET<<endl;
                    cin.ignore();
                }
                else
                {
                    cin.ignore();
                    set<string> currentSales;
                    currentSales.insert(productID);
                    map<string, Watch> :: iterator watch = Watch::watchList.begin();
                    int j = number;
                    Warranty currentWarranty = myWarranty(time);
                    while(j && watch != Watch::watchList.end())
                    {
                        if(watch->second.getProductID() == productID && watch->second.getAvailability())
                        {
                            //set avail for watch in stock
                            watch->second.setAvailability(0);

                            //set new sale
                            OrderDetail newSale;
                            newSale.setOrderID(orderID);
                            newSale.setIDSerie(watch->second.getID());
                            newSale.setID();
                            newSale.setWarranty(currentWarranty);
                            OrderDetail::saleList[newSale.getID()] = newSale;


                            //Write new sales to file
                            outputFile<<newSale.getOrderID()<<","
                                      <<newSale.getIDSerie()<<","
                                      <<newSale.getWarranty().expiry<<","
                                      <<newSale.getWarranty().coverage<<","<<endl;
                            OrderDetail::sales++;
                            j--;
                        }
                        watch++;
                    }
                    i -= number;
                }
            }
        }
        else
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing product!"<<ANSI_RESET<<endl;
    }
    //overwrite watch data
    ofstream watchFile;
    watchFile.open("Watch.txt");
    if(!watchFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
    }
    else
    {
        watchFile<<endl;
        for(auto currentWatch : Watch::watchList)
        {
                watchFile<<currentWatch.second.getProductID()<<","
                          <<currentWatch.second.getSerie()<<","
                          <<currentWatch.second.getAvailability()<<endl;
        }
    }

    watchFile.close();
    outputFile.close();
    Sleep(1500);
}
void myFunction::EraseSale(const string &orderID)
{
    ofstream outputFile;
    outputFile.open("OrderDetail.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    for(auto sale : OrderDetail::saleList)
    {
        if(sale.second.getOrderID() == orderID)
        {
            //update availability of watch
            string IDserie = sale.second.getIDSerie();
            Watch watch = Watch::watchList.find(IDserie)->second;
            //set avail for watch in stock
            watch.setAvailability(0);

            //erase sale
            OrderDetail::saleList.erase(sale.first);
            OrderDetail::sales--;
        }
    }
    outputFile<<endl;
    for(auto currentSale : OrderDetail::saleList)
    {
        outputFile<<currentSale.second.getOrderID()<<","
                  <<currentSale.second.getIDSerie()<<","
                  <<currentSale.second.getWarranty().expiry<<","
                  <<currentSale.second.getWarranty().coverage<<","<<endl;
    }
    outputFile.close();

    //overwrite watch data
    ofstream watchFile;
    watchFile.open("Watch.txt");
    if(!watchFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
    }
    else
    {
        watchFile<<endl;
        for(auto currentWatch : Watch::watchList)
        {
                watchFile<<currentWatch.second.getProductID()<<","
                          <<currentWatch.second.getSerie()<<","
                          <<currentWatch.second.getAvailability()<<endl;
        }
    }

    watchFile.close();
}
void myFunction::DeleteSale()
{
    ofstream outputFile;
    outputFile.open("OrderDetail.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    OrderDetail::saleList.clear();
    outputFile<<endl;
    outputFile.close();
}
/*
void UpdateSale(const string &orderID)
{
    for(auto sale : OrderDetail::saleList)
    {
        if(sale.second.getOrderID() == orderID)
        {
            Watch::watchList.find(sale.second.getIDSerie())->second.setAvailability(1);
        }
    }
    ofstream outputFile;
    outputFile.open("Watch.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Overwriting the file to update categories
    outputFile<<endl;
    for(auto currentWatch : Watch::watchList)
    {
            outputFile<<currentWatch.second.getProductID()<<","
                      <<currentWatch.second.getSerie()<<","
                      <<currentWatch.second.getAvailability()<<endl;
    }
    outputFile.close();
    //Erase and recreate information
    time_t time = Order::orderList.find(orderID)->second.setInvoiceDate(Order::orderList.find(orderID)->second.getInvoiceDate());
    EraseSale(orderID);
    CreateSale(orderID,time);
}
*/

string myFunction::generateOrderID(const string &myid)
{
    int max_size = 4;
    string ID = myid;
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
        cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Exceeded the allowed number of order" <<ANSI_RESET<< endl;
        return myid;
    }
}
void myFunction::printOder(Order myOrder)
{
    string customerName = Customer::customerList.find(myOrder.getCustomerPhone())->second.getName();
        cout<< "\t\t\t"<<setw(2)<<"|"<< ANSI_GREEN<<setw(10)<<left<< myOrder.getID()
            <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_GREEN<<setw(14)<<left<<myOrder.getCustomerPhone()
            <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_GREEN<<setw(24)<<left<<customerName
            <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_GREEN<<setw(30)<<left<<myOrder.getInvoiceDate()
            <<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_GREEN<<setw(12)<<left<<myOrder.getAmountDue()<< ANSI_RESET <<"|"<< endl;
}
void myFunction::ReadOrder()
{
    //system("cls");
    cout << "\t\t\t\t\t\t"<< "Fetching order data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(500); // Sleep for 2 seconds
    cout<< "\t\t\t"<<ANSI_YELLOW<<setw(25)<<" "<<"======================Order data===================="<<ANSI_RESET<<endl;
    cout<<endl;
    cout<< "\t\t\t"<<setw(2)<<left<<"|"<< ANSI_CYAN <<setw(10)<<left<<"Order ID"
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_CYAN<<setw(14)<<left<<"Customer Phone"
        <<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_CYAN<<setw(20)<<left<<"Customer name"
        <<ANSI_RESET<<setw(10)<<left<<"|"<< ANSI_CYAN<<setw(24)<<left<<"Invoice date"
        <<ANSI_RESET<<setw(3)<<left<<"|"<< ANSI_CYAN<<setw(17)<<left<<"Amount Due(VND)"<< ANSI_RESET<<"|"<<endl;
    for(auto pair : Order::orderList)
    {
        cout<< "\t\t\t"<<"--------------------------------------------------------------------------------------------------------------"<<endl;
        Order myOrder = pair.second;
        printOder(myOrder);
    }
    if(Order::orderList.empty())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Order data is empty"<<ANSI_RESET<<endl;
        Sleep(1000);
    }
    else
    {
        cout<< "\t\t\t"<<"--------------------------------------------------------------------------------------------------------------"<<endl;
        getch();
    }
}
struct detail
{
    int number;
    double price;
};
void myFunction::saleDetail(string orderID)
{
    int check = 0;
    //system("cls");
    cout<< "\t\t\t\t"<<ANSI_YELLOW<<setw(10)<<left<<"=================================Order Detail information================================"<<ANSI_RESET<<endl;
    cout<<endl;
    cout<< "\t\t\t\t"<<setw(2)<<left<<"|"<< ANSI_CYAN <<setw(8)<<left<<"Order ID"<<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_CYAN<<setw(20)<<left<<"IDserie"
    <<ANSI_RESET<<setw(10)<<left<<"|"<< ANSI_CYAN<<setw(24)<<left<<"Expiry Due"<<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(16)<<left<<"Coverage"<< ANSI_RESET<<"|"<<endl;
    for(auto sale : OrderDetail::saleList)
    {
        if(orderID == sale.second.getOrderID())
        {
        cout<< "\t\t\t\t"<<"-----------------------------------------------------------------------------------------------"<<endl;
        cout<< "\t\t\t\t"<<sale.second;
        check = 1;
        }
    }
    if(check)
    {
        cout<< "\t\t\t\t"<<"-----------------------------------------------------------------------------------------------"<<endl;
        Sleep(500);
    }
    else
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"There is no sales in this invoice"<<ANSI_RESET<<endl;
        Sleep(1000);
    }
}
void myFunction::FindOrder()
{
    system("cls");
    cin.ignore();
    string ID;
    cout<< "\t\t\t\t\t\t"<<"Enter order ID: "; getline(cin, ID);
    auto currentOrder = Order::orderList.find(ID);
    if(currentOrder != Order::orderList.end())
    {
        Order myOrder = currentOrder->second;
        printOder(myOrder);
        saleDetail(ID);
    }
    else
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing Order!"<<ANSI_RESET<<endl;
        Sleep(1000);
        return;
    }
    getch();
}
double myFunction::AmountDue(string orderID)
{
    double sum = 0;
    for(auto sale : OrderDetail::saleList)
    {
        string ID = sale.second.getOrderID();
        if(ID == orderID)
        {
            //refer to primary key of watch through foreign key ID Serie in order detail
            string watchID = sale.second.getIDSerie();
            //refer to primary key of product through foreign key product ID in watch
            string productID = Watch::watchList.find(watchID)->second.getProductID();
            //get price of product
            double price = Product::productList.find(productID)->second.getPrice();
            sum += price;
        }
    }
    return sum;
}
void myFunction::CreateOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Orders.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new order
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of new invoices to create: ";
        cin>>num;
        if(num + stoi(Order::lastID) > 9999 || num>10)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Exceeded the allowed number of orders"<<ANSI_RESET << endl;
        }
    }while(num + stoi(Order::lastID) > 9999 || num>10);
    //Create new orders
    cin.ignore();
    while(num)
    {
        // Get ID by generation
        string ID;
            ID = generateOrderID(Order::lastID);

        cout<< "\t\t\t\t\t\t"<<"Order "<<ID<<": "<<endl;

        // add new order's information
        Order newOrder;
        string customerPhone, invoiceDate;
        cout << "\t\t\t\t\t\t"<< "Enter customer Phone: ";
        getline(cin, customerPhone);

        //create a new customer if customer does not already exist
        if(!Customer::customerList.count(customerPhone))
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_CYAN<<"This is new customer. Create new customer"<<ANSI_RESET<<endl;
            Sleep(1000);
            Customer::createNewCustomer(customerPhone);
        }

        // current time of generating the invoice
        time_t current_time = time(nullptr);
        invoiceDate = ctime(&current_time);

        // cut out last line feed character of time string
        if (!invoiceDate.empty() && invoiceDate.back() == '\n')
            invoiceDate.pop_back();

        newOrder.setInvoiceDate(invoiceDate);

        //CREATE ORDER DETAIL
        CreateSale(ID,current_time);

        //set new order
        newOrder.setID(ID);
        newOrder.setCustomerPhone(customerPhone);
        newOrder.setAmountDue(AmountDue(ID));

        Order::orderList[ID] = newOrder;
        Order::numberOfOrder++;
        Order::lastID = Order::orderList.rbegin()->first;
        //Write new orders to file
        //if(ID=="0001") outputFile<<endl;
        outputFile<<newOrder.getID()<<","
                  <<newOrder.getCustomerPhone()<<","
                  <<newOrder.getInvoiceDate()<<","
                  <<newOrder.getAmountDue()<<endl;
        cout<<"\n";

        saleDetail(ID);
        cout<<"\n";
        cout<< "\t\t\t"<<ANSI_YELLOW<<"INVOICE ISSUED:"<<ANSI_RESET<<endl;
        cout<<endl;
        cout<< "\t\t\t"<<setw(2)<<left<<"|"<< ANSI_CYAN <<setw(10)<<left<<"Order ID"
            <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_CYAN<<setw(14)<<left<<"Customer Phone"
            <<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_CYAN<<setw(20)<<left<<"Customer name"
            <<ANSI_RESET<<setw(10)<<left<<"|"<< ANSI_CYAN<<setw(24)<<left<<"Invoice date"
            <<ANSI_RESET<<setw(3)<<left<<"|"<< ANSI_CYAN<<setw(17)<<left<<"Amount Due(VND)"<< ANSI_RESET<<"|"<<endl;
        cout<< "\t\t\t"<<"--------------------------------------------------------------------------------------------------------------"<<endl;
        printOder(newOrder);
        getch();
        num--;
    }

    outputFile.close();
    cout<< "\t\t\t\t\t\t" << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000);
    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"Information written to file."<<ANSI_RESET<<endl;
     // Sleep for 2 seconds
    Sleep(1000);
}
int myFunction::ReferConstraint_Order(const string &ID)
{
    for(auto orderDetail : OrderDetail::saleList)
        if(orderDetail.second.getOrderID() == ID)
            return 1;
    return 0;
}
void myFunction::EraseOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Orders.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new order
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of orders to erase: ";
        cin>>num;
        if(num > Order::numberOfOrder)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Exceeded the number of existing orders"<<ANSI_RESET << endl;
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
            if(!ReferConstraint_Order(ID))
            {

                Order::orderList.erase(ID);
                Order::numberOfOrder--;

            }
            else
            {
                cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Reference constraint!"<<ANSI_RESET<<endl;
                int choice;
                do
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Do you want to erase order detail (Yes/No):(1/0)?"<<ANSI_RESET<<endl;
                    cin>>choice;
                    if(choice == 1)
                    {
                        EraseSale(ID);
                        Order::orderList.erase(ID);
                        Order::numberOfOrder--;
                        cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"Order is erased"<<ANSI_RESET<<endl;
                    }
                    else if(choice == 0)
                        break;
                    else
                        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Invalid choice"<<ANSI_RESET<<endl;
                }while(true);
            }
        }
        else
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing order!"<<ANSI_RESET<<endl;
        }
        i++;
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
    cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000);
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<num<<" Orders have been erased."<<ANSI_RESET<<endl;
    Sleep(1000); // Sleep for 2 seconds

}
void myFunction::DeleteOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("OrderDetail.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    if(OrderDetail::saleList.empty())
    {
        Order::orderList.clear();
        outputFile<<endl;
        cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
        Sleep(1000); // Sleep for 2 seconds
        cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"You are order data is clear now!"<<ANSI_RESET<<endl;
        Sleep(1000);
    }
    else
    {
        int choice;
        cout<<ANSI_RED<< "\t\t\t\t"<<"Sale list is not empty, make sure you want to delete all sales data? (YES/NO):(1/0)"<<ANSI_RESET<<endl;
        cin>>choice;
        if(choice)
        {
                DeleteSale();
                if(!OrderDetail::saleList.empty())
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Order data can not be cleared as sale list is still not empty!"<<ANSI_RESET<<endl;
                }
                else
                {
                    Order::orderList.clear();
                    outputFile<<endl;
                    cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
                    Sleep(1000); // Sleep for 2 seconds
                    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"You are order data is clear now!"<<ANSI_RESET<<endl;
                    Order::numberOfOrder = 0;
                    Sleep(1000);
                }
        }
        else return;
    }
    outputFile.close();
}
/*
void UpdateOrder()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Orders.txt");
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
            if(!ReferConstraint_Order(ID))
            {
                Order newOrder;
                newOrder.setID(ID);
                string newPhone = UpdateCustomer(Order::orderList.find(ID)->second.getCustomerPhone());
                newOrder.setCustomerPhone(newPhone);
                newOrder.setInvoiceDate(Order::orderList.find(ID)->second.getInvoiceDate());
                //UPDATE SALES
                UpdateSale(ID);

                newOrder.setAmountDue(AmountDue(ID));
                Order::orderList.erase(ID);
                Order::orderList[ID] = newOrder;
            }
            else cout<<ANSI_YELLOW<<"Reference constraint!"<<ANSI_RESET<<endl;
        }
        else
        {
            cout<<ANSI_YELLOW<<"Non-existing order!"<<ANSI_RESET<<endl;
        }
        i++;
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
    Sleep(2000); // Sleep for 2 seconds
    cout<<ANSI_GREEN<<num<<" Orders have been updated."<<ANSI_RESET<<endl;
}
*/


void myFunction::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void myFunction::delay(int milliseconds) {
    Sleep(milliseconds);
}

void myFunction::runMessage(string message) {
    //system("cls");
    string qc = message;
    int qc_size = qc.length();
    string temp = qc; // Directly assign the string
    qc += temp; // Use += to concatenate strings
    int i = 0;
    const int temp_size = 30; // Declare temp_size here
    char hien[temp_size + 1];
    while (!kbhit()) {
        strncpy(hien, qc.c_str() + i, temp_size); // Use c_str() to access the string's characters
        hien[temp_size] = '\0';
        gotoxy(62, 24);
        cout <<ANSI_BOLD<< hien<<ANSI_RESET;
        delay(100);
        i++;
        if (i == qc_size)
            i = 0;
    }
}
int myFunction::enterPassword()
{
    system("cls");
    gotoxy(30,9);
    cout<<ANSI_YELLOW<<ANSI_BLINK<<"You are accessing the admin site, please enter your password to log in"<<ANSI_RESET<<endl;
    Sleep(2000);
    char check[]="HongVy2002";
    char password[15];
    int count_try=0;
    do
    {
        system("cls");
        gotoxy(40,12);
        cout<<ANSI_GREEN<<"ENTER PASSWORD:";

        gotoxy(40,14);
        int i=0;
        while((password[i]=getch())!=13 && ++i<15)      // Enter = 13
        {
            if(password[i-1]==8)                        // Backspace = 8
            {
                i=0;
                system("cls");
                gotoxy(40,12);
                cout<<ANSI_GREEN<<"ENTER PASSWORD:"<<endl;
                gotoxy(40,14);
            }
            else
            {
                cout<<"*";
            }
        }
        password[i]='\0';
        cout<<ANSI_RESET<<endl;
        if(!strcmp(password, check))
        {
            gotoxy(40,14);
            cout<<ANSI_CYAN<<"Your password is correct! You are in."<<ANSI_RESET<<endl;
            Sleep(1000);
            return 1;
        }

        else
        {
            gotoxy(40,14);
            cout<<ANSI_YELLOW<<"Your password is incorrect! Try again."<<ANSI_RESET<<endl;
            Sleep(1000);
            count_try++;
        }

    }while(count_try<3);
    return 0;
}
void myFunction::myLoad()
{
    Category::CategoryLoad();
    Product::ProductLoad();
    Watch::WatchLoad();
    Customer::CustomerLoad();
    Order::OrderLoad();
    OrderDetail::SaleLoad();
}
void myFunction::myCustomer()
{
    char choice;
    system("cls");
    cout << "\t\t\t\t\t\t"<< ANSI_GREEN<< ANSI_BLINK<<"Navigating your site....." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 1 seconds
    while(true)
    {
        system("cls");
        //Sleep(1000); // Sleep for 1 second (1,000,000 microseconds)
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
        cout << "\t\t\t\t\t\t"<< "     WELCOME TO CUSTOMER MANAGEMENT SYSTEM" << endl;
        cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
        cout << ANSI_YELLOW;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "1. [>] Read customer" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [?] Find customer" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [-] Erase customer" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                system("cls");
                Customer::ReadCustomer();
                break;
            case '2':
                system("cls");
                FindCustomer();
                break;
            case '3':
                if(enterPassword())
                {
                    EraseCustomer();
                    //Customer::ReadCustomer();
                }
                 else
                    {
                        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                        Sleep(1000);
                    }
                break;
            case '0':
                cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the customer management system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                Sleep(500);
                cout << "\t\t\t\t\t\t"<< ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                Sleep(500); // Sleep for 1 seconds
                return;
            default:
                cout<< "\t\t\t\t\t\t" << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                Sleep(1000);
        }
    }
}
void myFunction::myCategory()
{
    char choice;
    system("cls");
    cout << "\t\t\t\t\t\t"<< ANSI_GREEN<< ANSI_BLINK<<"Navigating your site....." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 1 seconds
    while(true)
    {
        system("cls");
        //Sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
        cout << "\t\t\t\t\t\t"<< "     WELCOME TO CATEGORY MANAGEMENT SYSTEM" << endl;
        cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] Create category" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] Read category" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [?] Find category" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "4. [~] Update category" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "5. [-] Erase category" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout<< "\t\t\t\t\t\t" << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                if(enterPassword())
                Category::CreateCategory();
                else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }
                break;
            case '2':
                system("cls");
                Category::ReadCategory();
                break;
            case '3':
                Category::ReadCategory();
                Category::FindCategory();
                break;
            case '4':
                //cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                {
                    Category::UpdateCategory();
                    Category::ReadCategory();
                }
                 else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }

                break;
            case '5':
                if(enterPassword())
                {
                    Category::EraseCategory();
                    Category::ReadCategory();
                }
                 else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }
                break;
            case '0':
                cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the category data management. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                cout << "\t\t\t\t\t\t"<< ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                Sleep(1000); // Sleep for 1 seconds
                return;
            default:
                cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                Sleep(1000);
        }
    }
}
void myFunction::myProduct()
{
    char choice;
    system("cls");
    cout << "\t\t\t\t\t\t"<< ANSI_GREEN<< ANSI_BLINK<<"Navigating your site....." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 1 seconds
    while (true)
    {
        system("cls");
        //Sleep(1000); // Sleep for 1 second (1,000,000 microseconds)
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
        cout << "\t\t\t\t\t\t"<< "     WELCOME TO PRODUCT MANAGEMENT SYSTEM" << endl;
        cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] Create product" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] Read product" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [?] Find product" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "4. [~] Update product" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "5. [-] Erase product" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                if(enterPassword())
                    Product::CreateProduct();
                 else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }
                break;
            case '2':
                system("cls");
                Product::ReadProduct();
                break;
            case '3':
                system("cls");
                Product::ReadProduct();
                Product::FindProduct();
                break;
            case '4':
                //cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                {
                    Product::UpdateProduct();
                    Product::ReadProduct();
                }
                else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }
                break;
            case '5':
                if(enterPassword())
                {
                    Product::Eraseproduct();
                    Product::ReadProduct();
                }
                 else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }
                break;
            case '0':
                cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the product data management. Goodbye!" << ANSI_BLINK << "..." << ANSI_RESET << endl;
                Sleep(500);
                cout<< "\t\t\t\t\t\t" << ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                Sleep(500); // Sleep for 1 seconds
                return;
            default:
                cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                Sleep(1000);
        }
    }
}

void myFunction::myOrder()
{
    char choice;
    system("cls");
    cout << "\t\t\t\t\t\t"<< ANSI_GREEN<< ANSI_BLINK<<"Navigating your site....." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 1 seconds
    while(true)
    {
        system("cls");
        //Sleep(1000); // Sleep for 1 second (1,000,000 microseconds)
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
        cout << "\t\t\t\t\t\t"<< "     WELCOME TO ORDER MANAGEMENT SYSTEM" << endl;
        cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] Create order" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] Read order" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [?] Find order" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "4. [~] Erase order" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "5. [-] delete order" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                CreateOrder();
                break;
            case '2':
                system("cls");
                ReadOrder();
                break;
            case '3':
                FindOrder();
                break;
            case '4':
                if(enterPassword())
                    EraseOrder();
                 else
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);
                }
                break;
            case '5':
                if(enterPassword())
                    DeleteOrder();
                 else
                    {
                        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                        Sleep(1000);
                    }
                break;
            case '0':
                cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the Order data management. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                Sleep(500);
                cout << "\t\t\t\t\t\t"<< ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                Sleep(500); // Sleep for 1 seconds
                return;
            default:
                cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                Sleep(1000);
        }
    }
}

void myFunction::myStatisticReport()
{
    char choice;
    system("cls");
    cout << "\t\t\t\t\t\t"<< ANSI_GREEN<< ANSI_BLINK<<"Navigating your site....." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 1 seconds
    while(true)
    {
        system("cls");
        //Sleep(1000); // Sleep for 1 second (1,000,000 microseconds)
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
        cout << "\t\t\t\t\t\t"<< "     WELCOME TO  STATISTIC REPORT SYSTEM" << endl;
        cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] the quantity of products by category" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] the number of customers and the total number of orders" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [<] the number of orders by period" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "4. [$] Revenue report by period" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "5. [*] Best-selling product of the year" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "6. [#] Manage inventory quantity by product" << endl;
        cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
        cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                StatisticsReport::ProductByCategory();
                break;
            case '2':
                StatisticsReport::CustomerAndOrderStatistics();
                break;
            case '3':
                {char period1;
                bool check1 = 1;
                while(check1)
                {
                    system("cls");
                    cout << "\t\t\t\t\t\t"<< "..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
                    Sleep(500); // Sleep for 1 second (1,000,000 microseconds)
                    cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
                    cout << "\t\t\t\t\t\t"<< "     CHOOSE PERIOD OF REPORT" << endl;
                    cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] the number of orders by each day" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] the number of orders by each month" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [<] the number of orders by each quarter" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "4. [~] the number of orders by each year" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
                    cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
                    cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
                    cin >> period1;
                    switch(period1)
                    {
                        case '1':
                            StatisticsReport::OrdersByDay();
                            break;
                        case '2':
                            StatisticsReport::OrdersByMonth();
                            break;
                        case '3':
                            StatisticsReport::OrdersByQuarter();
                            break;
                        case '4':
                            StatisticsReport::OrdersByYear();
                            break;
                        case '0':
                            cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the statistic report system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                            Sleep(500);
                            cout << "\t\t\t\t\t\t"<< ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                            Sleep(500); // Sleep for 1 seconds
                            check1 = 0;
                            break;
                        default:
                            cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                            Sleep(1000);
                    }
                }
                }
                break;
            case '4':
                {char period2;
                bool check2 = 1;
                while(check2)
                {
                    system("cls");
                    cout << "\t\t\t\t\t\t"<< "..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
                    Sleep(500); // Sleep for 1 second (1,000,000 microseconds)
                    cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "*******************************************" << endl;
                    cout << "\t\t\t\t\t\t"<< "     CHOOSE PERIOD OF REPORT" << endl;
                    cout << "\t\t\t\t\t\t"<< "*******************************************" << ANSI_RESET << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] Revenue report by each month" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] Revenue report by each quarter" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [<] Revenue report by each year" << endl;
                    cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
                    cout << "\t\t\t\t\t\t"<< ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
                    cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
                    cin >> period2;
                    switch(period2)
                    {
                        case '1':
                            StatisticsReport::RevenueByMonth();
                            break;
                        case '2':
                            StatisticsReport::RevenueByQuarter();
                            break;
                        case '3':
                            StatisticsReport::RevenueByYear();
                            break;
                        case '0':
                            cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the statistic report system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                            Sleep(500);
                            cout << "\t\t\t\t\t\t"<< ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                            Sleep(500); // Sleep for 1 seconds
                            check2 = 0;
                            break;
                        default:
                            cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                            Sleep(1000);
                    }
                }}
                break;
            case '5':
                StatisticsReport::BestSellingProductInYear();
                break;
            case '6':
                StatisticsReport::InventoryByProduct();
                break;
            case '0':
                cout << "\t\t\t\t\t\t"<< ANSI_BOLD << "Exiting the statistic report system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                Sleep(500);
                cout << "\t\t\t\t\t\t"<< ANSI_BLINK<<"Navigating your site back....." << ANSI_RESET << endl;
                Sleep(500); // Sleep for 1 seconds
                return;
            default:
                cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                Sleep(1000);
        }
    }
}

void myFunction::displayMainMenu()
{
    system("cls"); // Clear the console screen (Unix-like systems)
    cout << "\t\t\t\t\t\t"<< ANSI_CYAN << "*************************************************" << endl;
    cout << "\t\t\t\t\t\t"<< "     WELCOME TO WATCH STORE MANAGEMENT SYSTEM" << endl;
    cout << "\t\t\t\t\t\t"<< "*************************************************" << ANSI_RESET << endl;
    cout << "\t\t\t\t\t\t"<< "\t"<< left << ANSI_YELLOW << "1. [+] Customer site" << endl;
    cout << "\t\t\t\t\t\t"<< "\t"<< left << "2. [>] Category site" << endl;
    cout << "\t\t\t\t\t\t"<< "\t"<< left << "3. [*] Product site" << endl;
    cout << "\t\t\t\t\t\t"<< "\t"<< left << "4. [~] Order site" << endl;
    cout << "\t\t\t\t\t\t"<< "\t"<< left << "5. [$] Statistic report site" << endl;
    cout << "\t\t\t\t\t\t"<< "\t"<< left << "0. [X] Exit" << ANSI_RESET << endl;
    cout << "\t\t\t\t\t\t"<< ANSI_CYAN<< "*******************************************" << ANSI_RESET<< endl;
    cout << "\t\t\t\t\t\t"<< "Enter your choice: ";
}

void myFunction::Execute_Menu()
{
    char choice;
    while(true)
    {
        displayMainMenu();
        cin >> choice;
        switch (choice) {
            case '1':
                myCustomer();
                break;
            case '2':
                myCategory();
                break;
            case '3':
                myProduct();
                break;
            case '4':
                myOrder();
                break;
            case '5':
                if(enterPassword())
                    myStatisticReport();
                 else
                    {cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                    Sleep(1000);}
                break;
            case '0':
                cout << "\t\t\t\t\t\t"<< ANSI_BOLD <<ANSI_BLINK<<"Exiting the watch store management system. Goodbye!" << "..."  << ANSI_RESET << endl;
                Sleep(1000); // Sleep for 1 seconds
                system("cls");
                Title();
                runMessage("YOUR SATISFACTION IS OUR PRIORITY. GOODBYE! ");
                return;
            default:
                cout << "\t\t\t\t\t\t"<< ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                Sleep(1000);
        }
    }

}
void myFunction::Title()
{
    system("cls"); // Clear the console screen (Unix-like systems)
    string institutionLogo = "DA NANG UNIVERSITY OF SCIENCE AND TECHNOLOGY";
    string reportTitle = "A Watch Store Management Solution";
    string yourName1 = "Ho Tran Thi Hong Vy\t22T_DT5";
    string yourName2 = "Nguyen Hoang Nhat Linh\t22T_Nhat2";
    string instructorName = "Vo Duc Hoang";
    string term = "Problem based learning 2 2023";

    // Create the report cover page
    cout<<endl<<endl<<endl;
    cout << "\t\t\t\t\t\t" << "-------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t" << institutionLogo << "\n";
    cout << "\t\t\t\t\t\t" << "-------------------------------------------------------------\n\n";

    cout << "\t\t\t\t\t\t\tProject:\n";
    cout << "\t\t\t\t\t\t\t\t" << reportTitle << "\n\n";
    cout << "\t\t\t\t\t\t\tPrepared by:\n";
    cout << "\t\t\t\t\t\t\t\t" << yourName1 << "\n";
    cout << "\t\t\t\t\t\t\t\t" << yourName2 << "\n\n";

    cout << "\t\t\t\t\t\t\tInstructor:\n";
    cout << "\t\t\t\t\t\t\t\t" << instructorName << "\n\n";

    cout << "\t\t\t\t\t\t\tTerm: \t"<< term << "\n\n";

    cout << "\t\t\t\t\t\t" << "-------------------------------------------------------------\n";

}
void myFunction::Run()
{
    myLoad();
    Title();
    runMessage("WELCOME TO WATCH STORE MANAGEMENT SYSTEM ");
    Execute_Menu();
}
