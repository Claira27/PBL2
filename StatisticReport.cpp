#include"StatisticReport.h"

// Report the quantity of products by category
void StatisticsReport::ProductByCategory()
{
    system("cls");
    map<string, int> productCountByCategory;
    vector<string> myProduct;
    map<string, vector<string>>  productByCategory;
    // Browse through the list of products and count the number of products in each category
    for (const auto& category : Category::categoryList)
    {
        myProduct.clear();
        string categoryID = category.first;
        for (const auto& entry : Product::productList)
        {
            const Product& product = entry.second;
            const string& type = product.getFeature().type; // classify products by type
            const string& gender = product.getFeature().gender;// classify products by gender
            if(type == categoryID || gender == categoryID)
            {
                myProduct.push_back(product.getName());
                productCountByCategory[categoryID]++;
            }
        }
        productByCategory[categoryID] = myProduct;
    }
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Press 1: to display the report on the number of products by category"<<endl;
    cout<< "\t\t\t\t\t\t"<<"Press 2: to display the report on products by category"<<endl;
    int choice;
    cout<< "\t\t\t\t\t\t"<<"Your choice: "<<ANSI_RESET; cin>>choice;
    // Display the report
    if(choice == 1)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<< "Report the number of products by category:" <<ANSI_RESET<< endl;
        for (const auto& entry : Category::categoryList)
        {
            const string& categoryID = entry.first;
            const string& categoryName = entry.second.getName();
            const int productCount = productCountByCategory[categoryID];
            cout << "\t\t\t\t\t\t"<<ANSI_GREEN<< "Category: " << categoryName << ", the number of products: " << productCount <<ANSI_RESET<< endl;
        }
        cout<<ANSI_RESET<<endl;
    }
    else if(choice == 2)
    {
        cout<<ANSI_CYAN<<"================================================================================================================"<<endl;
        cout << "Category|   Number\t|\tProducts" << endl;
        for (const auto& entry : productByCategory)
        {
            cout<<entry.first<<"\t|\t"<<productCountByCategory[entry.first]<<"\t| ";
            vector<string> productsInCategory = entry.second;
            for (string productName : productsInCategory)
            {
                cout << " * " << productName;
            }
            cout<<endl;
        }
        cout<<endl<<"================================================================================================================"<<endl;
        cout<<ANSI_RESET<<endl;
    }
    else cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Invalid instruction!"<<ANSI_RESET<<endl;
    getch();
}

// Report the number of customers and the total number of orders
void  StatisticsReport::CustomerAndOrderStatistics()
{
    system("cls");
    int totalCustomers = Customer::getNumberOfCustomer();
    int totalOrders = Order::getNumberOfOrder();

    // Display report
    cout << "\t\t\t\t\t\t"<<ANSI_YELLOW<< "Report the number of customers and the total number of orders:"<<ANSI_RESET << endl;
    cout << "\t\t\t\t\t\t"<<ANSI_GREEN<< "the number of customers: " << totalCustomers << endl;
    cout << "\t\t\t\t\t\t"<< "the total number of orders: " << totalOrders <<ANSI_RESET<< endl;
    getch();
}

// Report the number of orders by each day
void  StatisticsReport::OrdersByDay()
{
    system("cls");
    map<string, int> ordersByDay;

    for (const auto& entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string day = invoiceDate.substr(0, 8); // Lấy tháng từ vị trí 4, chiều dài 3 ký tự
        string year = invoiceDate.substr(20, 4);  // Lấy năm từ vị trí 19, chiều dài 4 ký tự
        string time = day + year;
        ordersByDay[time]++;
    }

    // display the report
    if(ordersByDay.size())
    {
        cout << "\t\t\t\t\t\t"<<ANSI_YELLOW<< "Report the number of orders by each day:" <<ANSI_RESET<< endl;
        cout << "\t\t\t\t\t\t"<<ANSI_CYAN<< "Day: \t\t"<< " Number of orders  "<<ANSI_RESET<<endl;
        for (const auto& entry : ordersByDay)
        {
            cout<< "\t\t\t\t\t\t" << entry.first <<"\t "<< entry.second << endl;
        }
        getch();
    }
    else
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"No transactions during this time"<<ANSI_RESET<<endl;
        Sleep(1000);
    }

}

// Report the number of orders by each month
void  StatisticsReport::OrdersByMonth()
{
    system("cls");
    map<string, int> ordersByMonth;

    for (auto entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Lấy tháng từ vị trí 4, chiều dài 3 ký tự
        string year = invoiceDate.substr(20, 4);  // Lấy năm từ vị trí 19, chiều dài 4 ký tự
        string time = month + year;
        ordersByMonth[time]++;
    }
    // display the report
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Report the number of orders by each month:" <<ANSI_RESET<< endl;
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< " Month: \t\t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByMonth)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_CYAN << entry.first <<"\t\t\t"<< entry.second <<ANSI_RESET<< endl;
    }
    getch();
}
int monthSwitch(string month) {
    if (month == "Jan") {
        return 1;
    }
    else if (month == "Feb") {
        return 2;
    }
    else if (month == "Mar") {
        return 3;
    }
    else if (month == "Apr") {
        return 4;
    }
    else if (month == "May") {
        return 5;
    }
    else if (month == "Jun") {
        return 6;
    }
    else if (month == "Jul") {
        return 7;
    }
    else if (month == "Aug") {
        return 8;
    }
    else if (month == "Sep") {
        return 9;
    }
    else if (month == "Oct") {
        return 10;
    }
    else if (month == "Nov") {
        return 11;
    }
    else if (month == "Dec") {
        return 12;
    }
    else if (month == "Mar") {
        return 3;
    }
    else {
        return 0; // Handle the default case where the input doesn't match any month abbreviation.
    }
}


// Report the number of orders by each quarter
void  StatisticsReport::OrdersByQuarter()
{
    system("cls");
    map<string, int> ordersByQuarter;

    for (auto& entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Extract the month from position 4, 2 characters long.
        if (!month.empty())
            month = month.substr(1);
        if (!month.empty())
            month.pop_back();
        string year = invoiceDate.substr(20, 4);  // Extract the year from position 7, 4 characters long.
        // Calculate the quarter
        int quarter = monthSwitch(month)/3;
        string time = to_string(quarter) + " " +  year;
        ordersByQuarter[time]++;

    }

    // display the report
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Report the number of orders by each quarter:" <<ANSI_RESET<< endl;
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Quater: \t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByQuarter)
    {
        cout<< "\t\t\t\t\t\t" <<ANSI_CYAN<< entry.first <<"\t\t\t"<< entry.second <<ANSI_RESET<< endl;
    }
    getch();
}

// Report the number of orders by each year
void  StatisticsReport::OrdersByYear()
{
    system("cls");
    map<string, int> ordersByYear;

    for (auto& entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string year = invoiceDate.substr(20, 4);
        ordersByYear[year]++;
    }

    // display the report
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Report the number of orders by each year:" <<ANSI_RESET<< endl;
    cout << "\t\t\t\t\t\t" <<ANSI_YELLOW << "Year: \t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByYear)
    {
        cout<< "\t\t\t\t\t\t" <<ANSI_CYAN << entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
    getch();
}
// Revenue report by each month
void  StatisticsReport::RevenueByMonth()
{
    system("cls");
    map<string, double> revenueByMonth;

    for (auto& entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Lấy tháng từ vị trí 4, chiều dài 3 ký tự
        string year = invoiceDate.substr(20, 4);  // Lấy năm từ vị trí 19, chiều dài 4 ký tự
        string time = month + year;
        revenueByMonth[time]++;
    }

    // display the report
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Report the revenue by each month:"<<ANSI_RESET << endl;
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Month: \t\t"<< " Revenue "<<ANSI_RESET<<endl;
    for (const auto& entry : revenueByMonth)
    {
        cout<< "\t\t\t\t\t\t" <<ANSI_GREEN<< entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
    getch();
}
// Revenue report by each quarter
void  StatisticsReport::RevenueByQuarter()
{

    system("cls");
    map<string, double> revenueByQuarter;

    for (auto entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Extract the month from position 4, 2 characters long.
        if (!month.empty())
            month = month.substr(1);
        if (!month.empty())
            month.pop_back();
        string year = invoiceDate.substr(20, 4);  // Extract the year from position 7, 4 characters long.
        //cout<<month.size()<<endl;
        // Calculate the quarter
        int quarter = monthSwitch(month)/3;
        string time = to_string(quarter) + " " + year;
        revenueByQuarter[time] += entry.second.getAmountDue();
    }

    // display the report
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW << "Report the revenue by each quarter:"<<ANSI_RESET << endl;
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Quarter: \t"<< " Revenue "<<ANSI_RESET<<endl;
    for (const auto& entry : revenueByQuarter)
    {
        cout<< "\t\t\t\t\t\t" <<ANSI_GREEN<< entry.first <<"\t\t"<< entry.second <<ANSI_RESET<< endl;
    }
    getch();
}
// Revenue report by each year
void  StatisticsReport::RevenueByYear()
{
    system("cls");
    map<string, double> revenueByYear;

    for (auto& entry : Order::orderList)
    {
        string invoiceDate = entry.second.getInvoiceDate();
        string year = invoiceDate.substr(20, 4);
        revenueByYear[year] += entry.second.getAmountDue();
    }

    // display the report
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Report the revenue by each year:" <<ANSI_RESET<< endl;
    cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Year: \t"<< " Revenue "<<ANSI_RESET<<endl;
    for (const auto& entry : revenueByYear)
    {
        cout <<ANSI_GREEN<< entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
    getch();
}

//  Best-selling product of the year
void StatisticsReport::BestSellingProductInYear()
{
    system("cls");
    string year;
    cin.ignore();
    cout<<"Enter year of statistical analysis and data configuration: "; getline(cin,year);
    map<string, int> productSales; // record the quantity of watches sold for each product

    for (auto& entry : OrderDetail::saleList) {
        const OrderDetail& sale = entry.second;
        const string& orderID = sale.getOrderID();
        const string& invoiceDate = Order::orderList[orderID].getInvoiceDate();

        // extract year
        string saleYear = invoiceDate.substr(20, 4);

        if (saleYear == year) {
            const string& productID = Watch::watchList[sale.getIDSerie()].getProductID();
            productSales[productID] += 1; // increment the number of sold products
        }
    }

    // figure out the bestseller
    string bestSellingProduct;
    int maxSales = 0;

    for (const auto& entry : productSales) {
        if (entry.second > maxSales) {
            maxSales = entry.second;
            bestSellingProduct = entry.first;
        }
    }

    // Bestseller information
    if (!bestSellingProduct.empty())
    {
        cout<< "\t" <<ANSI_YELLOW<< "the bestseller of the year " << year << " is the product with ID: " << bestSellingProduct << " that was sold out " << maxSales << "." <<ANSI_RESET<< endl;
        cout<< "\t"<<ANSI_GREEN<<"Product information: "<<ANSI_RESET<<endl;
        cout<<endl;
        cout<<setw(2)<<left<<"|"<< ANSI_CYAN <<setw(10)<<left<<"Product ID"
            <<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_CYAN<<setw(20)<<left<<"Name"
            <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_CYAN<<setw(8)<<left<<"Price"
            <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_CYAN<<setw(6)<<left<<"Quantity"
            <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_CYAN<<setw(18)<<left<<"Strap Material"
            <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_CYAN<<setw(12)<<left<<"Color"
            <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(14)<<left<<"Brand"
            <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(12)<<left<<"Origin"<< ANSI_RESET<<"|"<<endl;
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<Product::productList[bestSellingProduct];
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    }
    else
    {
        cout<< "\t\t\t\t\t\t" <<ANSI_RED<< "No products were sold in the year " << year << "." <<ANSI_RESET<< endl;
    }
    getch();
}
//manage inventory quantity by product
void StatisticsReport::InventoryByProduct()
{
    system("cls");
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Report inventory quantity by product:"<<ANSI_RESET << endl;
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Product: \t\t\t\t" << " Inventory: " <<ANSI_RESET<< endl;
    for (auto& entry : Product::productList)
    {
        int inventory = entry.second.getQuantity();
        cout <<ANSI_GREEN<<setw(10)<<left<< entry.first<<setw(33)<<left<<entry.second.getName()<<setw(5)<<left<<inventory<<ANSI_RESET<< endl;
    }
    getch();
}

