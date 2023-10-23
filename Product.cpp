#include"Product.h"
#include"Category.h"
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
    int check1=0, check2=0;
    this->feature.gender = "NULL";
    for(auto genderID : Category::categoryList)
        if(gender == genderID.second.getName())
        {
            this->feature.gender = gender;
            check1 = 1;
        }

    this->feature.type = "NULL";
    for(auto typeID : Category::categoryList)
        if(type == typeID.second.getName())
        {
            this->feature.type = type;
            check2 = 1;
        }

    this->feature.strap = strap;
    this->feature.color = color;
    this->feature.brand = brand;
    this->feature.origin = origin;
    if(!check1 || !check2 )
        cout<<ANSI_YELLOW<<"The features of this product do not match any classifying category. They will be set NULL value instead"<<ANSI_RESET<<endl;
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
    os<< ANSI_GREEN<<myProduct.ID<<"\t"<<myProduct.name<<"\t"<<myProduct.price<<"\t"<<myProduct.quantity<<"\t"
      <<myProduct.feature.strap<<"\t"<<myProduct.feature.color<<"\t"<<myProduct.feature.brand<<"\t"<<myProduct.feature.origin<<"\t"
      <<myProduct.feature.gender<<"\t"<<myProduct.feature.type<< ANSI_RESET<<endl;
    return os;
}
void Product::ProductLoad()
{
    ifstream inputFile("Products.txt");
    if (!inputFile)
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    Product product;
    while (inputFile >> product)
    {
        Product::productList[product.getID()] = product; // Add a new customer
        Product::numberOfProduct++;
    }
    inputFile.close();
}
int Product::getNumberOfProduct()
{
    return Product::numberOfProduct;
}
void Product::ReadProduct()
{
    system("cls");
    cout << "Fetching product data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<< ANSI_CYAN <<"Product ID\tName\tPrice\tQuantity\tStrap Material\tColor\tBrand\tOrigin\tGender\tType"<< ANSI_RESET<<endl;
    for(const auto& pair : Product::productList)
        cout<<pair.second;
}
void Product::FindProduct()
{
    system("cls");
    string ID;
    cout<<"Enter product ID: "; getline(cin, ID);
    auto currentProduct = Product::productList.find(ID);
    if(currentProduct != Product::productList.end() && currentProduct->second.getID() != " ")
    {
        cout<<currentProduct->second;
        Watch::ReadWatch(ID);
    }
    else
    {
        cout<<ANSI_YELLOW<<"Non-existing product ID"<<ANSI_RESET<<endl;
        return;
    }
}
void Product::CreateProduct()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Products.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
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
            cout<<ANSI_YELLOW << "No more than 10 products to create at a time"<<ANSI_RESET << endl;
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
            cout<<ANSI_YELLOW<<"Product ID already existed"<<ANSI_RESET<<endl;
            num++;
        }
        else
        {
            cout<<"Enter product name: "; getline(cin, name);
            cout<<"Enter product price: "; cin>>price;
            //create new watches with serie and availability
            Watch::CreateWatch(ID);

            //set information of new product
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
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    outputFile.close();
    cout<<ANSI_GREEN<<"Information written to file."<<ANSI_RESET<<endl;
}
int Product::ReferenceConstraint(string ID)
{
    Product product = Product::productList.find(ID)->second;
    product.setQuantity();
    if(product.getQuantity()) return 1;
    return 0;
}
void Product::Eraseproduct()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
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
            cout<<ANSI_YELLOW << "Exceeded the number of existing products" <<ANSI_RESET<< endl;
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
            cout<<ANSI_YELLOW<<"Non-existing product ID"<<ANSI_RESET<<endl;
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
                cout<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
                int choice;
                cout<<ANSI_GREEN<<"Do you want to erase individual watches of this product? (YES/NO):(1/0)"<<ANSI_RESET<<endl;
                cin>>choice;
                if(choice)
                    Watch::EraseWatch(ID);
                else
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
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    outputFile.close();
    cout<<ANSI_YELLOW<<num<<" products have been erased."<<ANSI_RESET<<endl;
}
void Product::UpdateProduct()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Product.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
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
            cout<<ANSI_YELLOW << "Exceeded the number of existing products" <<ANSI_RESET<< endl;
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
            cout<<ANSI_YELLOW<<"Non-existing product ID"<<ANSI_RESET<<endl;
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
                if(!Product::productList.count(ID))
                {
                    cout<<ANSI_YELLOW<<"Product ID does not exist, try again!"<<ANSI_RESET<<endl;
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
                    int choice;
                    cout<<ANSI_GREEN<<"Do you want to update individual watches of this product? (YES/NO):(1/0)"<<ANSI_RESET<<endl;
                    cin>>choice;
                    if(choice) Watch::UpdateWatch(ID);
                }
            }
            else
            {
                cout<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
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
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    outputFile.close();
    cout<<ANSI_YELLOW<<num<<" Updates have been made."<<ANSI_RESET<<endl;
}
