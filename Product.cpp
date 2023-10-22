#include"Product.h"
#include"Watch.h"

int Product::numberOfProduct = 0;
map<string, Product> Product::productList;
Product::Product() : ID(" "), name(" "), price(0), quantity(0) {}
//Get information
string Product::getID() const
{
    return ID;
}
string Product::getName() const
{
    return name;
}
double Product::getPrice() const
{
    return price;
}
void Product::setQuantity()
{
    int count = 0;
    for(auto availableWatch : Watch::watchList)
        if(availableWatch.second.getProductID() == this->ID && availableWatch.second.getAvailability() == true)
            count++;
    this->quantity = count;
}
int Product::getQuantity()
{
    //automatically call setQuantity() to update the number of watches of the product left in stock
    setQuantity();
    return quantity;
}
Description Product::getFeature() const
{
    return feature;
}
//Mutator functions
void Product::setID(const string &ID)
{
    this->ID = ID;
}
void Product::setName(const string &name)
{
    this->name = name;
}
void Product::setPrice(const double &price)
{
    this->price = price;
}
void Product::setFeature()
{
    string strap,color,brand,origin;
    string gender;
    string type;
    cin.ignore();
    cout<<"Enter strap material: "; getline(cin, strap);
    cout<<"Enter color: "; getline(cin, color);
    cout<<"Enter brand: "; getline(cin, brand);
    cout<<"Enter origin: "; getline(cin, origin);
    cout<<"Enter gender: "; getline(cin, gender);
    cout<<"Enter type: "; getline(cin, type);
    this->feature.strap = strap;
    this->feature.color = color;
    this->feature.brand = brand;
    this->feature.origin = origin;
    this->feature.gender = gender;
    this->feature.type = type;
}
istream &operator>>(istream &is, Product &myProduct)
{
    is.ignore();
    getline(is,myProduct.ID, ',');
    getline(is,myProduct.name, ',');
    is>>myProduct.price>>myProduct.quantity;
    getline(is, myProduct.feature.strap, ',');
    getline(is, myProduct.feature.color, ',');
    getline(is, myProduct.feature.brand, ',');
    getline(is, myProduct.feature.origin, ',');
    getline(is, myProduct.feature.gender, ',');
    getline(is, myProduct.feature.type, ',');
    return is;
}
ostream &operator<<(ostream &os, const Product &myProduct)
{
    os<<myProduct.ID<<"\t"<<myProduct.name<<"\t"<<myProduct.price<<"\t"<<myProduct.quantity<<"\t"
      <<myProduct.feature.strap<<"\t"<<myProduct.feature.color<<"\t"<<myProduct.feature.brand<<"\t"<<myProduct.feature.origin<<"\t"
      <<myProduct.feature.gender<<"\t"<<myProduct.feature.type<<endl;
    return os;
}
void ProductLoad()
{
    ifstream inputFile("Products.txt");
    if (!inputFile)
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    Product product;
    while (inputFile >> product)
    {
        Product::productList[product.getID()] = product; // Add a new customer
        Product::numberOfProduct++;
    }
    cout << "Information uploaded from file." << endl;
    inputFile.close();
}
int getNumberOfProduct()
{
    return Product::numberOfProduct;
}
void ReadProduct()
{
    for(const auto& pair : Product::productList)
        cout<<pair.second;
}
void FindProduct(const string &ID)
{
    auto currentProduct = Product::productList.find(ID);
    if(currentProduct != Product::productList.end() && currentProduct->second.getID() != " ")
    {
        cout<<currentProduct->second;
    }
    else
    {
        cout<<"Non-existing product ID"<<endl;
        return;
    }
}
void CreateProduct()
{
    ofstream outputFile;
    outputFile.open("Products.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of new products
    int num;
    do
    {
        cout<<"Enter the number of new products to create: ";
        cin>>num;
        if(num > 100)
        {
            cout << "No more than 10 products to create at a time" << endl;
        }
    }while(num > 100);
    //Create new product
    cin.ignore();
    while(num--)
    {
        Product product;
        string ID, name;
        double price;
        int quantity;
        cout<<"Enter product ID: "; getline(cin, ID);
        if(Product::productList.count(ID))
        {
            cout<<"Product ID already existed"<<endl;
            num++;
        }
        else
        {
            cout<<"Enter product name: "; getline(cin, name);
            cout<<"Enter product price: "; cin>>price;
            cin.ignore();
            product.setID(ID);
            product.setName(name);
            product.setPrice(price);
            product.setQuantity();
            product.setFeature();
            Product::productList[ID] = product;
            //Write new product to file
            outputFile<<product.getID()<<","
                      <<product.getName()<<","
                      <<product.getPrice()<<" "
                      <<product.getQuantity()<<" "
                      <<product.getFeature().strap<<","
                      <<product.getFeature().color<<","
                      <<product.getFeature().brand<<","
                      <<product.getFeature().origin<<","
                      <<product.getFeature().gender<<","
                      <<product.getFeature().type<<","<<endl;
            Product::numberOfProduct++;
        }
    }

    outputFile.close();
    cout<<"Information written to file."<<endl;
}
int ReferenceConstraint(string ID)
{
    Product product = Product::productList.find(ID)->second;
    product.setQuantity();
    if(product.getQuantity()) return 1;
    return 0;
}
void Eraseproduct()
{
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of Products to erase
    int num;
    do
    {
        cout<<"Enter the number of products to erase: ";
        cin>>num;
        if(num  > Product::numberOfProduct)
        {
            cout << "Exceeded the number of existing products" << endl;
        }
    }while(num > Product::numberOfProduct);
    //erase products
    cin.ignore();
    int i = num;
    while(i--)
    {
        string ID;
        cout<<"Enter product ID: "; getline(cin, ID);
        if(!Product::productList.count(ID))
        {
            cout<<"Non-existing product ID"<<endl;
            num++;
        }
        else
        {
            if(!ReferenceConstraint(ID))
            {
                Product::productList.erase(ID);
                Product::numberOfProduct--;
            }
            else
            {
                cout<<"Reference Constraint"<<endl;
                i++;
            }
        }
    }
    //Overwriting the file to erase customers
    outputFile<<endl;
    for(auto product : Product::productList)
    {
        //Rewrite the file to erase products
        outputFile<<product.second.getID()<<","
                  <<product.second.getName()<<","
                  <<product.second.getPrice()<<" "
                  <<product.second.getQuantity()<<" "
                  <<product.second.getFeature().strap<<","
                  <<product.second.getFeature().color<<","
                  <<product.second.getFeature().brand<<","
                  <<product.second.getFeature().origin<<","
                  <<product.second.getFeature().gender<<","
                  <<product.second.getFeature().type<<","<<endl;
    }
    outputFile.close();
    cout<<num<<" products have been erased."<<endl;
}
void UpdateProduct()
{
    ofstream outputFile;
    outputFile.open("Product.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of products to update
    int num;
    do
    {
        cout<<"Enter the number of products to update: ";
        cin>>num;
        if(num  > Product::numberOfProduct)
        {
            cout << "Exceeded the number of existing products" << endl;
        }
    }while(num > Product::numberOfProduct);
    //Update product
    cin.ignore();
    int i = num;
    for(int i=1; i<=num; i++)
    {
        string ID;
        cout<<"Enter product ID: "; getline(cin, ID);
        if(!Product::productList.count(ID))
        {
            cout<<"Non-existing product ID"<<endl;
            num++;
        }
        else
        {
            if(!ReferenceConstraint(ID))
            {
                Product product;
                string name;
                double price;
                int quantity;
                Product::productList.erase(ID);
                cout<<"Enter product ID: "; getline(cin, ID);
                if(Product::productList.count(ID))
                {
                    cout<<"Product ID already existed, try again!"<<endl;
                    num++;
                }
                else
                {
                    cout<<"Enter product name: "; getline(cin, name);
                    cout<<"Enter product price: "; cin>>price;
                    cin.ignore();
                    product.setID(ID);
                    product.setName(name);
                    product.setPrice(price);
                    product.setQuantity();
                    product.setFeature();
                    Product::productList[ID] = product;
                }
            }
            else
            {
                cout<<"Reference Constraint"<<endl;
                i++;
            }
        }
    }
    //Overwriting the file to update products
    outputFile<<endl;
    for(auto product : Product::productList)
    {
        //Rewrite the file to erase products
        outputFile<<product.second.getID()<<","
                  <<product.second.getName()<<","
                  <<product.second.getPrice()<<" "
                  <<product.second.getQuantity()<<" "
                  <<product.second.getFeature().strap<<","
                  <<product.second.getFeature().color<<","
                  <<product.second.getFeature().brand<<","
                  <<product.second.getFeature().origin<<","
                  <<product.second.getFeature().gender<<","
                  <<product.second.getFeature().type<<","<<endl;
    }
    outputFile.close();
    cout<<num<<" Updates have been made."<<endl;
}
