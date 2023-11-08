#include"Manage.h"

Manage::Manage()
{
    CategoryLoad();
    WatchLoad();
    ProductLoad();
    CustomerLoad();
    OrderLoad();
    SaleLoad();
}

//Category
bool Manage::CategoryLoad()
{
    numberOfCategory = 0;
    ifstream inputFile("Categories.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        Category category;
        while (inputFile >> category)
        {
            categoryList.push_back(category); // Add a new category
            numberOfCategory++;
        }
        inputFile.close();
        return 1;
    }
}
int Manage::getNumberOfCategory()
{
    return numberOfCategory;
}
vector<Category> Manage::getCategoryList()
{
    return categoryList;
}
vector<Category> Manage::ReadCategory()
{
    return categoryList;
}
bool Manage::FindCategory(string categoryID)
{
    for (const Category &category : categoryList) {
        if (category.getID() == categoryID) {
            return 1;
        }
    }
    return 0;
}
vector<Category> Manage::SearchCategory(string name)
{
    vector<Category> result;
    for(auto  category : categoryList)
    {
        if(category.getName().find(name) != string::npos)
            result.push_back(category);
    }
    return result;
}
bool Manage::CreateCategory(string categoryID, string name)
{
    ofstream outputFile;
    outputFile.open("Categories.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(FindCategory(categoryID))
            return 0;
        else
        {
            // add new category's information
            Category newCategory;
            newCategory.setID(categoryID);
            newCategory.setName(name);
            categoryList.push_back(newCategory);
            //write file
            outputFile<<newCategory.getID()<<"|"
                      <<newCategory.getName()<<"|"<<endl;
            numberOfCategory++;
            outputFile.close();
            return 1;
        }
    }
}
bool Manage::ReferenceConstraint_Category(string ID)
{
    for(auto product : productList)
        if(product.getFeature().gender == ID || product.getFeature().type == ID)
            return 1;
    return 0;
}
bool Manage::EraseCategory(string categoryID)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(outputFile.is_open())
    {
        if(!ReferenceConstraint_Category(categoryID))
        {
            auto category = categoryList.begin();
            while(category != categoryList.end() && (*category).getID() != categoryID)
            {
                category++;
            }
            if(category != categoryList.end())
            {
                categoryList.erase(category);
                numberOfCategory--;
                check = 1;
            }
        }

        //Overwriting the file to erase categories
        for(auto currentCategory : categoryList)
        {
            outputFile<<currentCategory.getID()<<"|"
                      <<currentCategory.getName()<<"|"<<endl;
        }
    }
    outputFile.close();
    return check;
}
bool Manage::UpdateCategory(string categoryID, string name)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(outputFile.is_open())
    {
        if(!ReferenceConstraint_Category(categoryID))
        {
            auto category = categoryList.begin();
            while(category != categoryList.end() && (*category).getID() != categoryID)
            {
                category++;
            }
            if(category != categoryList.end())
            {
                (*category).setName(name);
                check = 1;
            }
        }
        //Overwriting the file to update categories
        for(auto currentCategory : categoryList)
        {
            outputFile<<currentCategory.getID()<<"|"
                      <<currentCategory.getName()<<"|"<<endl;
        }
    }
    outputFile.close();
    return check;
}
bool Manage::ClearData_Category()
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(outputFile.is_open())
    {
        if(!numberOfProduct)
        {
            categoryList.clear();
            check = 1;
            numberOfCategory = 0;
        }
        //Overwriting the file to update categories
        for(auto currentCategory : categoryList)
        {
            outputFile<<currentCategory.getID()<<"|"
                      <<currentCategory.getName()<<"|"<<endl;
        }
    }
    outputFile.close();
    return check;
}

//Product
bool Manage::ProductLoad()
{
    numberOfProduct = 0;
    ifstream inputFile("Products.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        Product product;
        // quantity
        while (inputFile >> product)
        {
            int count = 0;
            for(auto watch : watchList)
                if(watch.getProductID() == product.getID())
                    count++;
            product.setQuantity(count);
            productList.push_back(product);
            numberOfProduct++;
        }
        inputFile.close();
        ofstream outputFile;
        outputFile.open("Products.txt");
        //Overwriting the file to update quantity of product
        for(auto product : productList)
        {
            outputFile<<product.getID()<<"|"
                      <<product.getName()<<"|"
                      <<product.getPrice()<<"|"
                      <<product.getQuantity()<<"|"
                      <<product.getFeature().strap<<"|"
                      <<product.getFeature().color<<"|"
                      <<product.getFeature().brand<<"|"
                      <<product.getFeature().origin<<"|"
                      <<product.getFeature().coverage<<"|"
                      <<product.getFeature().gender<<"|"
                      <<product.getFeature().type<<"|"<<endl;
        }
        outputFile.close();
        return 1;
    }
}
int Manage::getNumberOfProduct()
{
    return numberOfProduct;
}
vector<Product> Manage::getProductList()
{
    return productList;
}
bool Manage::ReferenceConstraint_Product(string ID)
{
    for(auto watch : watchList)
        if(watch.getProductID() == ID)
        return 1;
    return 0;
}
vector<Product> Manage::ReadProduct()
{
    return productList;
}
bool Manage::FindProduct(string ID)
{
    for (auto product : productList) {
    if (product.getID() == ID) {
        return 1;
    }
}
    return 0;
}
vector<Product> Manage::SearchProduct(string name)
{
    vector<Product> result;
    for(auto  product : productList)
    {
        if(product.getName().find(name) != string::npos)
            result.push_back(product);
    }
    return result;
}
bool Manage::CreateProduct(string ID, string name, double price, Description feature, vector<string> series)
{
    bool check = 0;
    ofstream watchFile;
    watchFile.open("Watches.txt", std::ios::app);
    if(watchFile.is_open())
    {
        ofstream outputFile;
        outputFile.open("Products.txt", std::ios::app);
        if(outputFile.is_open())
        {
            if(!FindProduct(ID))
            {
                // add new product's information
                Product newProduct;
                newProduct.setID(ID);
                newProduct.setName(name);
                newProduct.setPrice(price);
                newProduct.setFeature(feature);
                newProduct.setQuantity(0);
                productList.push_back(newProduct);
                numberOfProduct++;
                //write file
                outputFile<<newProduct.getID()<<"|"
                          <<newProduct.getName()<<"|"
                          <<newProduct.getPrice()<<"|"
                          <<newProduct.getQuantity()<<"|"
                          <<newProduct.getFeature().strap<<"|"
                          <<newProduct.getFeature().color<<"|"
                          <<newProduct.getFeature().brand<<"|"
                          <<newProduct.getFeature().origin<<"|"
                          <<newProduct.getFeature().coverage<<"|"
                          <<newProduct.getFeature().gender<<"|"
                          <<newProduct.getFeature().type<<"|"<<endl;
                // add new watch's information
                for(auto serie : series)
                {
                    Watch newWatch;
                    newWatch.setProductID(ID);
                    newWatch.setSerie(serie);
                    newWatch.setID();
                    newWatch.setAvailability(1);
                    watchList.push_back(newWatch);
                    //write file
                    watchFile<<newWatch.getProductID()<<"|"
                              <<newWatch.getSerie()<<"|"
                              <<newWatch.getAvailability()<<"|"<<endl;
                    numberOfWatch++;
                }
                check = 1;
            }
        }
        outputFile.close();
    }
    watchFile.close();
    productList.clear();
    ProductLoad();
    return check;
}
bool Manage::Eraseproduct(string ID)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(outputFile.is_open())
    {
        if(!ReferenceConstraint_Product(ID))
        {
            auto product = productList.begin();
            while(product != productList.end() && (*product).getID() != ID)
            {
                product++;
            }
            if(product != productList.end())
            {
                    productList.erase(product);
                    numberOfProduct--;
                    check = 1;
            }
        }
    }
    //Overwriting the file to erase product
    for(auto product : productList)
    {
        outputFile<<product.getID()<<"|"
                  <<product.getName()<<"|"
                  <<product.getPrice()<<"|"
                  <<product.getQuantity()<<"|"
                  <<product.getFeature().strap<<"|"
                  <<product.getFeature().color<<"|"
                  <<product.getFeature().brand<<"|"
                  <<product.getFeature().origin<<"|"
                  <<product.getFeature().coverage<<"|"
                  <<product.getFeature().gender<<"|"
                  <<product.getFeature().type<<"|"<<endl;
    }
    outputFile.close();
    return check;
}
bool Manage::UpdateProduct(string ID, string name, double price, Description feature)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(outputFile.is_open())
    {
        if(!ReferenceConstraint_Product(ID))
        {
            auto product = productList.begin();
            while(product != productList.end() && (*product).getID() != ID)
            {
                product++;
            }
            if(product != productList.end())
            {
                    (*product).setName(name);
                    (*product).setPrice(price);
                    (*product).setFeature(feature);
                    check = 1;
            }
        }
    }
    //Overwriting the file to erase categories
    for(auto product : productList)
    {
        outputFile<<product.getID()<<"|"
                  <<product.getName()<<"|"
                  <<product.getPrice()<<"|"
                  <<product.getQuantity()<<"|"
                  <<product.getFeature().strap<<"|"
                  <<product.getFeature().color<<"|"
                  <<product.getFeature().brand<<"|"
                  <<product.getFeature().origin<<"|"
                  <<product.getFeature().coverage<<"|"
                  <<product.getFeature().gender<<"|"
                  <<product.getFeature().type<<"|"<<endl;
    }
    outputFile.close();
    return check;
}
bool Manage::ClearData_Product()
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(outputFile.is_open())
    {
        ofstream watchFile;
        watchFile.open("Watches.txt");
        if(watchFile.is_open())
        {
            if(!numberOfSales)
            {
                watchList.clear();
                productList.clear();
                check = 1;
                numberOfProduct = 0;
                numberOfWatch = 0;
            }
        }
        //Overwriting the file to watch
        for(auto watch : watchList)
        {
            watchFile<<watch.getProductID()<<"|"
                     <<watch.getSerie()<<"|"
                     <<watch.getAvailability()<<"|"<<endl;
        }
        watchFile.close();
    }
    //Overwriting the file to product
    for(auto product : productList)
    {
        outputFile<<product.getID()<<"|"
                  <<product.getName()<<"|"
                  <<product.getPrice()<<"|"
                  <<product.getQuantity()<<"|"
                  <<product.getFeature().strap<<"|"
                  <<product.getFeature().color<<"|"
                  <<product.getFeature().brand<<"|"
                  <<product.getFeature().origin<<"|"
                  <<product.getFeature().coverage<<"|"
                  <<product.getFeature().gender<<"|"
                  <<product.getFeature().type<<"|"<<endl;
    }
    outputFile.close();
    return check;
}
//Product detail
bool Manage::WatchLoad()
{
    numberOfWatch = 0;
    ifstream inputFile("Watches.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        Watch watch;
        while (inputFile >> watch)
        {
            watch.setID();
            watchList.push_back(watch); // Add a new watch
            numberOfWatch++;
        }
        inputFile.close();
        return 1;
    }
}
int Manage::getNumberOfWatch()
{
    return numberOfWatch;
}
vector<Watch> Manage::getWatchList()
{
    return watchList;
}
vector<Watch> Manage::ReadWatch(string productID)
{
    vector<Watch> currentWatchList;
    for(auto watch : watchList)
        if(watch.getProductID() == productID)
            currentWatchList.push_back(watch);
    return currentWatchList;
}
bool Manage::FindWatch(string ID)
{
    for (auto watch : watchList) {
    if (watch.getID() == ID) {
        return 1;
    }
}
    return 0;
}

//Customer
bool Manage::CustomerLoad()
{
    numberOfCustomer = 0;
    ifstream inputFile("Customers.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        lastID_customer = "0000";
        Customer customer;
        while (inputFile >> customer)
        {
            customerList.push_back(customer); // Add a new customer
            numberOfCustomer++;
            lastID_customer = customer.getID();
        }
        inputFile.close();
        return 1;
    }
}
int Manage::getNumberOfCustomer()
{
    return numberOfCustomer;
}
vector<Customer> Manage::getCustomerList()
{
    return customerList;
}
vector<Customer> Manage::ReadCustomer()
{
    return customerList;
}
bool Manage::FindCustomer(const string &phone)
{
    for (const Customer &customer : customerList) {
        if (customer.getPhone() == phone) {
            return 1;
        }
    }
    return 0;
}
vector<Customer> Manage::SearchCustomer(string phone)
{
    vector<Customer> result;
    for(auto  customer : customerList)
    {
        if(customer.getPhone().find(phone) != string::npos)
            result.push_back(customer);
    }
    return result;
}
bool Manage::CreateCustomer(const string &phone, const string &name)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Customers.txt", std::ios::app);
    if(outputFile.is_open())
    {
        if(!FindCustomer(phone))
        {
            string customerID = generateOrderID(lastID_customer);
            // add new customer's information
            Customer newCustomer;
            newCustomer.setID(customerID);
            newCustomer.setPhone(phone);
            newCustomer.setName(name);
            customerList.push_back(newCustomer);
            lastID_customer = customerID;
            //write file
            outputFile<<newCustomer.getID()<<"|"
                      <<newCustomer.getPhone()<<"|"
                      <<newCustomer.getName()<<"|"<<endl;
            numberOfCustomer++;
            check = 1;
        }
    }
    outputFile.close();
    return check;
}
bool Manage::ReferConstraint_Customer(const string &ID)
{
    for(auto order : orderList)
        if(order.getCustomerID() == ID)
            return 1;
    return 0;
}
bool Manage::EraseCustomer(const string &phone)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(outputFile.is_open())
    {
        for(auto customer : customerList)
            if(customer.getPhone() == phone)
                if(!ReferConstraint_Customer(customer.getID()))
                {
                    auto customer = customerList.begin();
                    while(customer != customerList.end() && (*customer).getPhone() != phone)
                    {
                        customer++;
                    }
                    if(customer != customerList.end())
                    {
                        customerList.erase(customer);
                        numberOfCustomer--;
                        check = 1;
                    }
                }
    }
    //Overwriting the file to erase customer
    for(auto currentCustomer : customerList)
    {
        outputFile<<currentCustomer.getID()<<"|"
                  <<currentCustomer.getPhone()<<"|"
                  <<currentCustomer.getName()<<"|"<<endl;
    }
    outputFile.close();
    return check;
}
bool Manage::UpdateCustomer(const string &phone, const string &newPhone, const string &name)
{
    bool check = 0;
    for(auto customer : customerList)
        if(customer.getPhone() == newPhone)
            return check;
    ofstream outputFile;
    outputFile.open("Customers.txt");
    if(outputFile.is_open())
    {
        for(auto customer : customerList)
            if(customer.getPhone() == phone)
                if(!ReferConstraint_Customer(customer.getID()))
                {
                    auto customer = customerList.begin();
                    while(customer != customerList.end() && (*customer).getPhone() != phone)
                    {
                        customer++;
                    }
                    if(customer != customerList.end())
                    {
                        (*customer).setPhone(newPhone);
                        (*customer).setName(name);
                        check = 1;
                    }
                }
    }
    //Overwriting the file to erase customer
    for(auto currentCustomer : customerList)
    {
        outputFile<<currentCustomer.getID()<<"|"
                  <<currentCustomer.getPhone()<<"|"
                  <<currentCustomer.getName()<<"|"<<endl;
    }
    outputFile.close();
    return check;
}

//Order
bool Manage::OrderLoad()
{
    numberOfOrder = 0;
    ifstream inputFile("Orders.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        lastID_order = "0000";
        Order order;
        while (inputFile >> order)
        {
            orderList.push_back(order); // Add a new customer
            numberOfOrder++;
            lastID_order = order.getID();
        }
        inputFile.close();
        return 1;
    }
}
int Manage::getNumberOfOrder()
{
    return numberOfOrder;
}
vector<Order> Manage::getOrderList()
{
    return orderList;
}
string Manage::generateOrderID(const string &myid)
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
        return myid;
    }
}
vector<Order> Manage::ReadOrder()
{
    return orderList;
}
bool Manage::FindOrder(const string &ID)
{
    for(auto order : orderList)
        if(order.getID() == ID)
            return 1;
    return 0;
}

double Manage::AmountDue(vector<myOrder> order)
{
    double sum = 0;
    for(auto current : order)
    {
        for(auto product : productList)
        {
            if(current.ID == product.getID())
                sum += current.number*product.getPrice();
        }
    }
    return sum;
}
bool Manage::CreateOrder(const string &customerPhone, const string &customerName, vector<myOrder> order)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Orders.txt", std::ios::app);
    if(outputFile.is_open())
    {
        string orderID = generateOrderID(lastID_order);
        //create order
        Order newOrder;
        if(!FindCustomer(customerPhone))
            CreateCustomer(customerPhone, customerName);
        // current time of generating the invoice
        time_t current_time = time(nullptr);
        string invoiceDate = ctime(&current_time);
        // cut out last line feed character of time string
        if (!invoiceDate.empty() && invoiceDate.back() == '\n')
            invoiceDate.pop_back();

        newOrder.setInvoiceDate(invoiceDate);

        //CREATE ORDER DETAIL
        for(auto current : order)
        {
            string coverage = "none";
            for(auto product : productList)
                if(current.ID == product.getID())
                {
                    coverage = product.getFeature().coverage;
                }
            CreateSale(orderID, current.ID, current.number, current_time, coverage);
        }

        //set new order
        newOrder.setID(orderID);
        string customerID;
        for(auto customer : customerList)
            if(customer.getPhone() == customerPhone)
                customerID = customer.getID();
        newOrder.setCustomerID(customerID);
        newOrder.setAmountDue(AmountDue(order));
        orderList.push_back(newOrder);
        //update orderList state
        numberOfOrder++;
        lastID_order = orderID;
        //write file
        outputFile<<newOrder.getID()<<"|"
                 <<newOrder.getCustomerID()<<"|"
                 <<newOrder.getInvoiceDate()<<"|"
                 <<newOrder.getAmountDue()<<"|"<<endl;
        check = 1;
    }
    outputFile.close();
    productList.clear();
    ProductLoad();
    return check;
}
bool Manage::ReferConstraint_Order(const string &ID)
{
    for(auto sale : saleList)
    {
        if(ID == sale.getOrderID())
            return 1;
    }
    return 0;
}
bool Manage::EraseOrder(const string &ID)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Orders.txt");
    if(outputFile.is_open())
    {
        if(!ReferConstraint_Order(ID))
        {
            auto order = orderList.begin();
            while(order != orderList.end() &&  (*order).getID() != ID)
            {
                order++;
            }
            if(order != orderList.end())
            {
                orderList.erase(order);
                numberOfOrder--;
                check = 1;
            }
        }
    }
    for(auto order : orderList)
    {
        outputFile<<order.getID()<<"|"
                  <<order.getCustomerID()<<"|"
                  <<order.getInvoiceDate()<<"|"
                  <<order.getAmountDue()<<"|"<<endl;
    }
    outputFile.close();
    return  check;
}
bool Manage::CancelOrder(const string &ID)
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Orders.txt");
    if(outputFile.is_open())
    {
        auto order = orderList.begin();
        while(order != orderList.end() &&  (*order).getID() != ID)
        {
            order++;
        }
        if(order != orderList.end())
        {
            orderList.erase(order);
            EraseSale(ID);
            check = 1;
        }
    }
    for(auto order : orderList)
    {
        outputFile<<order.getID()<<"|"
                  <<order.getCustomerID()<<"|"
                  <<order.getInvoiceDate()<<"|"
                  <<order.getAmountDue()<<"|"<<endl;
    }
    outputFile.close();
    return  check;
}
bool Manage::ClearData_Order()
{
    bool check = 0;
    ofstream outputFile;
    outputFile.open("Orders.txt");
    if(outputFile.is_open())
    {
        ofstream customerFile;
        customerFile.open("Customers.txt");
        if(customerFile.is_open())
        {
            ofstream orderDetailFile;
            orderDetailFile.open("Sales.txt");
            if(orderDetailFile.is_open())
            {
                saleList.clear();
                customerList.clear();
                orderList.clear();
                check = 1;
                numberOfCustomer = 0;
                numberOfOrder = 0;
                numberOfSales = 0;
            }
            for(auto sale : saleList)
                orderDetailFile<<sale.getOrderID();
            orderDetailFile.close();
        }
        for(auto customer : customerList)
            customerFile<<customer.getID();
        customerFile.close();
    }
    for(auto order : orderList)
        outputFile<<order.getID();
    outputFile.close();
    return check;
}
//OrderDetail
bool Manage::SaleLoad()
{
    numberOfSales = 0;
    ifstream inputFile("Sales.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        OrderDetail sale;
        while (inputFile >> sale)
        {
            sale.setID();
            saleList.push_back(sale); // Add a new customer
            numberOfSales++;
        }
        inputFile.close();
        return 1;
    }
}
int Manage::getNumberOfSales()
{
    return numberOfSales;
}
vector<OrderDetail> Manage::getSaleList()
{
    return saleList;
}
vector<OrderDetail> Manage::ReadSale(string orderID)
{
    vector<OrderDetail> currentSaleList;
    for(auto sale : saleList)
        if(sale.getOrderID() == orderID)
            currentSaleList.push_back(sale);
    return currentSaleList;
}
bool Manage::FindSale(string ID)
{
    for (auto sale : saleList) {
        if (sale.getID() == ID) {
            return 1;
        }
    }
    return 0;
}
Warranty Manage::myWarranty(time_t time, string coverage)
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
    warranty.coverage = coverage;
    return warranty;
}
bool Manage::CreateSale(const string &orderID, const string &productID, const int number, time_t time, string coverage)
{
    bool check = 0;
    //overwrite watch data
    ofstream watchFile;
    watchFile.open("Watch.txt");
    if(watchFile.is_open())
    {
        ofstream outputFile;
        outputFile.open("Sales.txt", std::ios::app);
        if(outputFile.is_open())
        {
            auto product = productList.begin();
            while(product != productList.end() && (*product).getID() != productID)
                product++;
            if(product != productList.end())
            {
                if((*product).getQuantity() >= number)
                {
                    int add = number;
                    auto it = watchList.begin();
                    while(it++ != watchList.end() && add)
                    {
                        if((*it).getProductID() == productID && (*it).getAvailability() == 1 )
                        {
                            (*it).setAvailability(0);
                            Warranty currentWarranty = myWarranty(time, coverage);
                            OrderDetail newSale;
                            newSale.setOrderID(orderID);
                            newSale.setIDSerie((*it).getID());
                            newSale.setID();
                            newSale.setWarranty(currentWarranty);
                            saleList.push_back(newSale);
                            add--;
                            //Write new sales to file
                            outputFile<<newSale.getOrderID()<<"|"
                                      <<newSale.getIDSerie()<<"|"
                                      <<newSale.getWarranty().expiry<<"|"
                                      <<newSale.getWarranty().coverage<<"|"<<endl;
                            numberOfSales++;
                        }
                    }
                check = 1;
                }
            }
        }
        outputFile.close();
    }
    //overwrite watch data
    for(auto currentWatch : watchList)
    {
            watchFile<<currentWatch.getProductID()<<"|"
                      <<currentWatch.getSerie()<<"|"
                      <<currentWatch.getAvailability()<<"|"<<endl;
    }
    watchFile.close();
    return check;
}

bool Manage::EraseSale(const string &ID)
{
    bool check = 0;
    ofstream watchFile;
    watchFile.open("Watches.txt");
    if(watchFile.is_open())
    {
        ofstream outputFile;
        outputFile.open("Sales.txt");
        if(outputFile.is_open())
        {
            auto sale = saleList.begin();
            while (sale != saleList.end()) {
                if ((*sale).getOrderID() == ID) {
                    string IDserie = (*sale).getIDSerie();
                    for (auto watch = watchList.begin(); watch != watchList.end(); ++watch) {
                        if (watch->getID() == IDserie) {
                            watch->setAvailability(1);
                        }
                    }
                    sale = saleList.erase(sale);  // Erase the current element and get the next iterator
                    numberOfSales--;
                    check = 1;
                } else {
                    ++sale;  // Move to the next element
                }
            }
        }
        for(auto currentSale : saleList)
        outputFile<<currentSale.getOrderID()<<"|"
                  <<currentSale.getIDSerie()<<"|"
                  <<currentSale.getWarranty().expiry<<"|"
                  <<currentSale.getWarranty().coverage<<"|"<<endl;
        outputFile.close();
    }
    //overwrite watch data
    for(auto currentWatch : watchList)
    {
            watchFile<<currentWatch.getProductID()<<"|"
                      <<currentWatch.getSerie()<<"|"
                      <<currentWatch.getAvailability()<<"|"<<endl;
    }
    watchFile.close();
    return check;
}
bool Manage::ClearData()
{
    if(ClearData_Order())
    if(ClearData_Product())
    if(ClearData_Category())
    return 1;
}

//SatisticReport
// Report the quantity of products by category
vector<productByCategory> Manage::ProductByCategory()
{
    vector<productByCategory> result;
    for(auto category : categoryList)
    {
        productByCategory current;
        vector<Product> products;
        string categoryID = category.getID();
        for(auto product : productList)
        {
            const string& type = product.getFeature().type; // classify products by type
            const string& gender = product.getFeature().gender;// classify products by gender
            if(type == categoryID || gender == categoryID)
            {
                products.push_back(product);
            }
        }
    current.products = products;
    current.category = category;
    result.push_back(current);
    }
    return result;
}
// Report the number of customers and the total number of orders
customerAndOrder Manage::CustomerAndOrderStatistics()
{
    customerAndOrder result;
    result.numberOfCustomer = numberOfCustomer;
    result.numberOfSale = numberOfSales;
    return result;
}
// Report the number of orders by each day
vector<ordersByDay> Manage::OrdersByDay()
{
    vector<ordersByDay> result;
    for (const auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
        string day = invoiceDate.substr(0, 8); // Lấy tháng từ vị trí 4, chiều dài 3 ký tự
        string year = invoiceDate.substr(20, 4);  // Lấy năm từ vị trí 19, chiều dài 4 ký tự
        string time = day + year;
        bool check = 0;
        for(auto current : result)
            if(current.day == time)
            {
                current.numberOfOrder++;
                check = 1;
                break;
            }
        if(!check)
        {
            ordersByDay order;
            order.numberOfOrder = 1;
            order.day = time;
            result.push_back(order);
        }
    }
    return result;
}
int Manage::monthSwitch(string month) {
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
// Report the number of orders by each month
vector<ordersByMonth> Manage::OrdersByMonth()
{
    vector<ordersByMonth> result;
    for (const auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Lấy tháng từ vị trí 4, chiều dài 3 ký tự
        string year = invoiceDate.substr(20, 4);  // Lấy năm từ vị trí 19, chiều dài 4 ký tự
        string time = month + year;

        bool check = 0;
        for(auto current : result)
            if(current.month == time)
            {
                current.numberOfOrder++;
                check = 1;
                break;
            }
        if(!check)
        {
            ordersByMonth order;
            order.numberOfOrder = 1;
            order.month = time;
            result.push_back(order);
        }
    }
    return result;
}
// Report the number of orders by each quarter
vector<ordersByQuarter> Manage::OrdersByQuarter()
{
    vector<ordersByQuarter> result;
    for (const auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Extract the month from position 4, 2 characters long.
        if (!month.empty())
            month = month.substr(1);
        if (!month.empty())
            month.pop_back();
        string year = invoiceDate.substr(20, 4);  // Extract the year from position 7, 4 characters long.
        // Calculate the quarter
        int quarter = monthSwitch(month)/3;
        string time = to_string(quarter) + " " +  year;

        bool check = 0;
        for(auto current : result)
            if(current.quarter == time)
            {
                current.numberOfOrder++;
                check = 1;
                break;
            }
        if(!check)
        {
            ordersByQuarter order;
            order.numberOfOrder = 1;
            order.quarter = time;
            result.push_back(order);
        }
    }
    return result;
}
// Report the number of orders by each year
vector<ordersByYear> Manage::OrdersByYear()
{
    vector<ordersByYear> result;
    for (const auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
        string time = invoiceDate.substr(20, 4);

        bool check = 0;
        for(auto current : result)
            if(current.year == time)
            {
                current.numberOfOrder++;
                check = 1;
                break;
            }
        if(!check)
        {
            ordersByYear order;
            order.numberOfOrder = 1;
            order.year = time;
            result.push_back(order);
        }
    }
    return result;
}
// Revenue report by each month
vector<revenueByMonth> Manage::RevenueByMonth()
{
    vector<revenueByMonth> result;
    for (auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
        string month = invoiceDate.substr(3, 5); // Lấy tháng từ vị trí 4, chiều dài 3 ký tự
        string year = invoiceDate.substr(20, 4);  // Lấy năm từ vị trí 19, chiều dài 4 ký tự
        string time = month + year;

        bool check = 0;
        for(auto current : result)
            if(current.month == time)
            {
                current.revenue += entry.getAmountDue();
                check = 1;
                break;
            }
        if(!check)
        {
            revenueByMonth revenue;
            revenue.revenue = entry.getAmountDue();
            revenue.month = time;
            result.push_back(revenue);
        }
    }
    return result;
}
// Revenue report by each quarter
vector<revenueByQuarter> Manage::RevenueByQuarter()
{
    vector<revenueByQuarter> result;
    for (auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
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

        bool check = 0;
        for(auto current : result)
            if(current.quarter == time)
            {
                current.revenue += entry.getAmountDue();
                check = 1;
                break;
            }
        if(!check)
        {
            revenueByQuarter revenue;
            revenue.revenue = entry.getAmountDue();
            revenue.quarter = time;
            result.push_back(revenue);
        }
    }
    return result;
}
//Revenue report by each year
vector<revenueByYear> Manage::RevenueByYear()
{
    vector<revenueByYear> result;
    for (auto& entry : orderList)
    {
        string invoiceDate = entry.getInvoiceDate();
        string time = invoiceDate.substr(20, 4);

        bool check = 0;
        for(auto current : result)
            if(current.year == time)
            {
                current.revenue += entry.getAmountDue();
                check = 1;
                break;
            }
        if(!check)
        {
            revenueByYear revenue;
            revenue.revenue = entry.getAmountDue();
            revenue.year = time;
            result.push_back(revenue);
        }
    }
    return result;
}
//Best-selling product of the year
Product Manage::BestSellingProductInYear(string year)
{
    vector<myOrder> productSales;
    for (auto& sale : saleList)
    {
        string orderID = sale.getOrderID();
        string productID;
        for(auto watch : watchList)
            if(watch.getID() == sale.getIDSerie())
            {
                productID = watch.getProductID();
                break;
            }
        string invoiceDate;
        for(auto order : orderList)
            if(order.getID() == orderID)
                invoiceDate = order.getInvoiceDate();
        // extract year
        string saleYear = invoiceDate.substr(20, 4);

        if(saleYear == year)
        {
            bool check = 0;
            for(auto current : productSales)
            if(current.ID == productID)
            {
                current.number++;
                check = 1;
                break;
            }
            if(!check)
            {
                myOrder numberOfSoldProduct; // record the quantity of watches sold for each product
                numberOfSoldProduct.number = 1;
                numberOfSoldProduct.ID = productID;
                productSales.push_back(numberOfSoldProduct);
            }
        }
    }

    // figure out the bestseller
    string bestSellingProduct;
    int maxSales = 0;
    for (const auto& entry : productSales) {
        if (entry.number > maxSales) {
            maxSales = entry.number;
            bestSellingProduct = entry.ID;
        }
    }
    Product result;
    for(auto product : productList)
        if(product.getID() == bestSellingProduct)
            result = product;
    return result;
}
//manage inventory quantity by product
vector<inventoryByProduct> Manage::InventoryByProduct()
{
    vector<inventoryByProduct> result;
    ProductLoad();
    for(auto product : productList)
    {
        inventoryByProduct current;
        current.product = product;
        current.quantity = product.getQuantity();
    }
    return result;
}
