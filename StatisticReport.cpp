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
        string categoryID = category.first;
        string categoryName = category.second.getName();
        for (const auto& entry : Product::productList)
        {
            const Product& product = entry.second;
            const string& type = product.getFeature().type; // classify products by type
            const string& gender = product.getFeature().gender;// classify products by gender
            if(type == categoryName || gender == categoryName)
            {
                myProduct.push_back(product.getName());
                productCountByCategory[categoryID]++;
            }
        }
        productByCategory[categoryID] = myProduct;
    }
    cout<<"Press 1: to display the report on the number of products by category"<<endl;
    cout<<"Press 2: to display the report on products by category"<<endl;
    int choice;
    cout<<"Your choice: "; cin>>choice;
    // Display the report
    if(choice == 1)
    {
        cout<<ANSI_CYAN<< "Report the number of products by category:" << endl;
        for (const auto& entry : Category::categoryList) {
            const string& categoryID = entry.first;
            const string& categoryName = entry.second.getName();
            const int productCount = productCountByCategory[categoryID];
            cout << "Category: " << categoryName << ", the number of products: " << productCount << endl;
        }
        cout<<ANSI_RESET<<endl;
    }
    else if(choice == 2)
    {
        cout<<ANSI_CYAN<<"============================================================================================"<<endl;
        cout << "Category\t|\tNumber\t|\tProducts" << endl;
        for (const auto& entry : productByCategory)
        {
            cout<<entry.first<<"\t|\t"<<productCountByCategory[entry.first]<<"\t| ";
            const vector<string>& productsInCategory = entry.second;
            for (const string& productName : productsInCategory)
            {
                cout << "- " << productName;
            }
        }
        cout<<endl<<"============================================================================================"<<endl;
        cout<<ANSI_RESET<<endl;
    }
    else cout<<ANSI_YELLOW<<"Invalid instruction!"<<ANSI_RESET<<endl;
}

// Report the number of customers and the total number of orders
void  StatisticsReport::CustomerAndOrderStatistics()
{
    system("cls");
    int totalCustomers = Customer::getNumberOfCustomer();
    int totalOrders = Order::getNumberOfOrder();

    // Display report
    cout <<ANSI_YELLOW<< "Report the number of customers and the total number of orders:" << endl;
    cout << "the number of customers: " << totalCustomers << endl;
    cout << "the total number of orders: " << totalOrders <<ANSI_RESET<< endl;
}

// Report the number of orders by each day
void  StatisticsReport::OrdersByDay()
{
    system("cls");
    map<string, int> ordersByDay;

    for (const auto& entry : Order::orderList)
    {
        string day = entry.second.getInvoiceDate();
        ordersByDay[day]++;
    }

    // display the report
    cout <<ANSI_YELLOW<< "Report the number of orders by each day:" <<ANSI_RESET<< endl;
    cout <<ANSI_CYAN<< "Day: \t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByDay)
    {
        cout << entry.first <<"\t"<< entry.second << endl;
    }
}

// Report the number of orders by each month
void  StatisticsReport::OrdersByMonth()
{
    system("cls");
    map<int, int> ordersByMonth;

    for (auto& entry : Order::orderList)
    {
        time_t time = entry.second.setInvoiceDate(entry.second.getInvoiceDate());
        struct tm timeinfo = *localtime(&time);
        int month = timeinfo.tm_mon + 1;
        ordersByMonth[month]++;
    }

    // display the report
    cout <<ANSI_YELLOW<< "Report the number of orders by each month:" <<ANSI_RESET<< endl;
    cout <<ANSI_YELLOW<< "Month: \t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByMonth)
    {
        cout<<ANSI_CYAN << entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
}
// Report the number of orders by each quarter
void  StatisticsReport::OrdersByQuarter()
{
    system("cls");
    map<int, int> ordersByQuarter;

    for (auto& entry : Order::orderList)
    {
        time_t time = entry.second.setInvoiceDate(entry.second.getInvoiceDate());
        struct tm timeinfo = *localtime(&time);
        int month = timeinfo.tm_mon;

        // calculate quater
        const int quarter = (month / 3) + 1;

        ordersByQuarter[quarter]++;
    }

    // display the report
    cout <<ANSI_YELLOW<< "Report the number of orders by each quarter:" <<ANSI_RESET<< endl;
    cout <<ANSI_YELLOW<< "Quater: \t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByQuarter)
    {
        cout <<ANSI_CYAN<< entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
}
// Report the number of orders by each year
void  StatisticsReport::OrdersByYear()
{
    system("cls");
    map<int, int> ordersByYear;

    for (auto& entry : Order::orderList)
    {
        time_t time = entry.second.setInvoiceDate(entry.second.getInvoiceDate());
        struct tm timeinfo = *localtime(&time);
        int year = timeinfo.tm_year + 1900;
        ordersByYear[year]++;
    }

    // display the report
    cout <<ANSI_YELLOW<< "Report the number of orders by each year:" <<ANSI_RESET<< endl;
    cout<<ANSI_YELLOW << "Year: \t"<< " Number of orders  "<<ANSI_RESET<<endl;
    for (const auto& entry : ordersByYear)
    {
        cout<<ANSI_CYAN << entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
}
// Revenue report by each month
void  StatisticsReport::RevenueByMonth()
{
    system("cls");
    map<int, double> revenueByMonth;

    for (auto& entry : Order::orderList)
    {
        time_t time = entry.second.setInvoiceDate(entry.second.getInvoiceDate());
        struct tm timeinfo = *localtime(&time);
        int month = timeinfo.tm_mon + 1;
        revenueByMonth[month] += entry.second.getAmountDue();
    }

    // display the report
    cout <<ANSI_YELLOW<< "Report the revenue by each month:"<<ANSI_RESET << endl;
    cout <<ANSI_YELLOW<< "Month: \t"<< " Revenue "<<ANSI_RESET<<endl;
    for (const auto& entry : revenueByMonth)
    {
        cout <<ANSI_GREEN<< entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
}
// Revenue report by each quarter
void  StatisticsReport::RevenueByQuarter()
{
    system("cls");
    map<int, double> revenueByQuarter;

    for (auto& entry : Order::orderList)
    {
        time_t time = entry.second.setInvoiceDate(entry.second.getInvoiceDate());
        struct tm timeinfo = *localtime(&time);
        int month = timeinfo.tm_mon;

        // calculate quarter
        const int quarter = (month / 3) + 1;
        revenueByQuarter[quarter] += entry.second.getAmountDue();
    }

    // display the report
    cout<<ANSI_YELLOW << "Report the revenue by each quarter:"<<ANSI_RESET << endl;
    cout <<ANSI_YELLOW<< "Quarter: \t"<< " Revenue "<<ANSI_RESET<<endl;
    for (const auto& entry : revenueByQuarter)
    {
        cout <<ANSI_GREEN<< entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
}
// Revenue report by each year
void  StatisticsReport::RevenueByYear()
{
    system("cls");
    map<int, double> revenueByYear;

    for (auto& entry : Order::orderList)
    {
        time_t time = entry.second.setInvoiceDate(entry.second.getInvoiceDate());
        struct tm timeinfo = *localtime(&time);
        int year = timeinfo.tm_year + 1900;
        revenueByYear[year] += entry.second.getAmountDue();
    }

    // display the report
    cout <<ANSI_YELLOW<< "Report the revenue by each year:" <<ANSI_RESET<< endl;
    cout <<ANSI_YELLOW<< "Year: \t"<< " Revenue "<<ANSI_RESET<<endl;
    for (const auto& entry : revenueByYear)
    {
        cout <<ANSI_GREEN<< entry.first <<"\t"<< entry.second <<ANSI_RESET<< endl;
    }
}

//  Best-selling product of the year
void StatisticsReport::BestSellingProductInYear()
{
    system("cls");
    int year;
    cout<<"Enter year of statistical analysis and data configuration: "; cin>>year;
    map<string, int> productSales; // record the quantity of watches sold for each product

    for (auto& entry : OrderDetail::saleList) {
        const OrderDetail& sale = entry.second;
        const string& orderID = sale.getOrderID();
        const string& saleDate = Order::orderList[orderID].getInvoiceDate();

        // extract year
        time_t time = Order::orderList[entry.second.getOrderID()].setInvoiceDate(saleDate);
        struct tm timeinfo = *localtime(&time);
        int saleYear = timeinfo.tm_year + 1900; // tm_year returns the number of years after 1900

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
        cout <<ANSI_GREEN<< "the bestseller of the year " << year << " is the product with ID: " << bestSellingProduct << " that was sold out " << maxSales << "." <<ANSI_RESET<< endl;
        cout<<ANSI_GREEN<<"Product information: "<<ANSI_RESET<<Product::productList[bestSellingProduct];
    }
    else
    {
        cout <<ANSI_RED<< "No products were sold in the year " << year << "." <<ANSI_RESET<< endl;
    }
}
//manage inventory quantity by product
void StatisticsReport::InventoryByProduct()
{
    system("cls");
    cout<<ANSI_YELLOW << "Report inventory quantity by product:"<<ANSI_RESET << endl;
    cout<<ANSI_YELLOW << "Product: \t\t" << " Inventory: " <<ANSI_RESET<< endl;
    for (auto& entry : Product::productList)
    {
        int inventory = entry.second.getQuantity();
        cout <<ANSI_GREEN<< entry.first<<" "<<entry.second.getName()<< "\t" <<inventory<<ANSI_RESET<< endl;
    }
}
