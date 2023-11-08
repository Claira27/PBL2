#include"Manage.h"

int main()
{

    Manage myManage;
    vector<Category> category = myManage.getCategoryList();
    vector<Customer> customer = myManage.getCustomerList();
    vector<Order> order = myManage.getOrderList();
    vector<Product> product = myManage.getProductList();
    vector<Watch> watch = myManage.getWatchList();
    vector<OrderDetail> sale = myManage.getSaleList();
    /*
    for(auto current : category)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfCategory()<<endl;
    cout<<"Is successful? "<<myManage.CreateCategory("Moi","co")<<endl;
    cout<<"Is successful? "<<myManage.EraseCategory("L02")<<endl;
    cout<<"Is successful? "<<myManage.UpdateCategory("Xoa", "co")<<endl;
    cout<<myManage.getNumberOfProduct()<<endl;
    cout<<"Is successful? "<<myManage.ClearData_Category()<<endl;
    category = myManage.getCategoryList();
    for(auto current : category)
    cout<<current.getID()<<endl;
    */

    for(auto current : product)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfProduct()<<endl;
    vector<string> series;
    series.push_back("12345");
    series.push_back("12346");
    cout<<"Is successful? "<<myManage.CreateProduct("SNK807K2", "new",1000,{"strap", "color", "brand", "origin","coverage","gender","type"},series)<<endl;
    cout<<"Is successful? "<<myManage.Eraseproduct("K4E2N11N")<<endl;
    //cout<<"Is successful? "<<myManage.UpdateProduct("K4E2N11N","new",1000,{"strap", "color", "brand", "origin","coverage","gender","type"}) <<endl;
    //cout<<"Is successful? "<<myManage.ClearData_Product()<<endl;
    product = myManage.getProductList();
    for(auto current : product)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfWatch()<<endl;
    watch = myManage.getWatchList();
    for(auto current : watch)
    cout<<current.getID()<<endl;

    /*
    for(auto current : customer)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfCustomer()<<endl;
    cout<<"Is successful? "<<myManage.CreateCustomer("0123", "new")<<endl;
    //cout<<"Is successful? "<<myManage.EraseCustomer("0123")<<endl;
    cout<<"Is successful? "<<myManage.UpdateCustomer("0", "0000000000", "new")<<endl;
    customer = myManage.getCustomerList();
    for(auto current : customer)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfCustomer()<<endl;
    */
/*
    for(auto current : order)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfOrder()<<endl;
    for(auto current : sale)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfSales()<<endl;
    vector<myOrder> neworder;
    neworder.push_back({"NJ01501L", 2});
    neworder.push_back({"J9P2H37J", 0});
    //cout<<"Is successful? "<<myManage.CreateOrder("0763712043", "New", neworder)<<endl;
    //cout<<"Is successful? "<<myManage.EraseOrder("001")<<endl;
    //cout<<"Is successful? "<<myManage.CancelOrder("0011")<<endl;
    cout<<"Is successful? "<<myManage.ClearData_Order()<<endl;

    order = myManage.getOrderList();
    for(auto current : order)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfOrder()<<endl;
    sale = myManage.getSaleList();
    for(auto current : sale)
    cout<<current.getID()<<endl;
    cout<<myManage.getNumberOfSales()<<endl;

    cout<<myManage.getNumberOfWatch()<<endl;
    watch = myManage.getWatchList();
    for(auto current : watch)
    cout<<current.getID()<<endl;
    */
    cout<<"Category search by name"<<endl;
    vector<Category> a = myManage.SearchCategory("dai");
    for(auto A : a)
        cout<<A.getID()<<endl;
    cout<<"Product search by name"<<endl;
    vector<Product> b = myManage.SearchProduct("Casio");
    for(auto B : b)
        cout<<B.getID()<<endl;
    cout<<"Customer search by phone"<<endl;
    vector<Customer> c = myManage.SearchCustomer("0763712");
    for(auto C : c)
        cout<<C.getID()<<endl;
    /*========warning if you want to clear all data======*/
    //myManage.ClearData();
    return 0;
}
