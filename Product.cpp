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
    cout<< "\t\t\t\t\t\t"<<"Enter strap material: "; getline(cin, strap);
    cout<< "\t\t\t\t\t\t"<<"Enter color: "; getline(cin, color);
    cout<< "\t\t\t\t\t\t"<<"Enter brand: "; getline(cin, brand);
    cout<< "\t\t\t\t\t\t"<<"Enter origin: "; getline(cin, origin);
    cout<< "\t\t\t\t\t\t"<<"Enter gender: "; getline(cin, gender);
    cout<< "\t\t\t\t\t\t"<<"Enter type: "; getline(cin, type);
    int check1=0, check2=0;
    this->feature.gender = "NULL";
    for(auto genderID : Category::categoryList)
        if(gender == genderID.second.getName())
        {
            this->feature.gender = genderID.second.getID();
            check1 = 1;
        }

    this->feature.type = "NULL";
    for(auto typeID : Category::categoryList)
        if(type == typeID.second.getName())
        {
            this->feature.type = typeID.second.getID();
            check2 = 1;
        }

    this->feature.strap = strap;
    this->feature.color = color;
    this->feature.brand = brand;
    this->feature.origin = origin;
    if(!check1 || !check2 )
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"The features of this product do not match any classifying category. They will be set NULL value instead"<<ANSI_RESET<<endl;
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

void Product::ProductLoad()
{
    ifstream inputFile("Products.txt");
    if (!inputFile)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    Product product;
    while (inputFile >> product)
    {
        productList[product.getID()] = product; // Add a new customer
        numberOfProduct++;
    }
    inputFile.close();
}
int Product::getNumberOfProduct()
{
    return numberOfProduct;
}
ostream &operator<<(ostream &os, const Product &myProduct)
{

    os<<setw(2)<<"|"<< ANSI_GREEN<<setw(10)<<left<<myProduct.ID
        <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_GREEN<<setw(24)<<left<<myProduct.name
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_GREEN<<setw(8)<<left<<myProduct.price
        <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_GREEN<<setw(6)<<left<<myProduct.quantity
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_GREEN<<setw(20)<<left<<myProduct.feature.strap
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_GREEN<<setw(14)<<left<<myProduct.feature.color
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_GREEN<<setw(18)<<left<<myProduct.feature.brand
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_GREEN<<setw(16)<<left<<myProduct.feature.origin<< ANSI_RESET <<"|"<< endl;
    return os;
}
void Product::ReadProduct()
{
    //system("cls");
    cout << "\t\t\t\t\t\t"<< "Fetching product data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(500); // Sleep for 2 seconds
    cout<<ANSI_YELLOW<<setw(25)<<" "<<"======================Product information===================="<<ANSI_RESET<<endl;
    cout<<endl;
    cout<<setw(2)<<left<<"|"<< ANSI_CYAN <<setw(10)<<left<<"Product ID"
        <<ANSI_RESET<<setw(8)<<left<<"|"<< ANSI_CYAN<<setw(20)<<left<<"Name"
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_CYAN<<setw(8)<<left<<"Price"
        <<ANSI_RESET<<setw(2)<<left<<"|"<< ANSI_CYAN<<setw(6)<<left<<"Quantity"
        <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_CYAN<<setw(18)<<left<<"Strap Material"
        <<ANSI_RESET<<setw(4)<<left<<"|"<< ANSI_CYAN<<setw(12)<<left<<"Color"
        <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(14)<<left<<"Brand"
        <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(12)<<left<<"Origin"<< ANSI_RESET<<"|"<<endl;
    for(const auto& pair : productList)
    {
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<pair.second;
    }

    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    getch();
}
void Product::FindProduct()
{
    //system("cls");
    string ID;
    cin.ignore();
    cout<< "\t\t\t\t\t\t"<<"Enter product ID: "; getline(cin, ID);
    auto currentProduct = productList.find(ID);
    if(currentProduct != productList.end())
    {
        system("cls");
        cout<< "\t\t\t\t"<<ANSI_YELLOW<<"======================Watch information===================="<<ANSI_RESET<<endl;
        cout<< "\t\t\t"<<currentProduct->second<<endl;
        Watch::ReadWatch(ID);
        Sleep(50);
    }
    else
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing product ID"<<ANSI_RESET<<endl;
        Sleep(2000);
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
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new products
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of new products to create: ";
        cin>>num;
        if(num > 10)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "No more than 10 products to create at a time"<<ANSI_RESET << endl;
        }
    }while(num > 10);
    //Create new product
    cin.ignore();
    while(num--)
    {
        Product product;
        string ID, name;
        double price;
        int quantity;
        cout<< "\t\t\t\t\t\t"<<"Enter product ID: "; getline(cin, ID);
        if(Product::productList.count(ID))
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Product ID already existed"<<ANSI_RESET<<endl;
            num++;
        }
        else
        {
            cout<< "\t\t\t\t\t\t"<<"Enter product name: "; getline(cin, name);
            cout<< "\t\t\t\t\t\t"<<"Enter product price: "; cin>>price;

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
            //create new watches with serie and availability
            Watch::CreateWatch(ID);
        }
    }
    cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 2 seconds
    outputFile.close();
    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"Information written to file."<<ANSI_RESET<<endl;
    Sleep(1000);
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
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of Products to erase
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of products to erase: ";
        cin>>num;
        if(num  > Product::numberOfProduct)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Exceeded the number of existing products" <<ANSI_RESET<< endl;
        }
    }while(num > Product::numberOfProduct);
    //erase products
    cin.ignore();
    int i = num;
    while(i--)
    {
        string ID;
        cout<< "\t\t\t\t\t\t"<<"Enter product ID: "; getline(cin, ID);
        if(!Product::productList.count(ID))
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing product ID"<<ANSI_RESET<<endl;
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
                cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
                int choice;
                cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"Do you want to erase individual watches of this product? (YES/NO):(1/0)"<<ANSI_RESET<<endl;
                cin>>choice;
                if(choice)
                    Watch::EraseWatch(ID);
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
    cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000);
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<" products have been erased."<<ANSI_RESET<<endl;
    Sleep(1000);// Sleep for 2 seconds
    outputFile.close();

}
void Product::UpdateProduct()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Product.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of products to update
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of products to update: ";
        cin>>num;
        if(num  > Product::numberOfProduct)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "Exceeded the number of existing products" <<ANSI_RESET<< endl;
        }
    }while(num > Product::numberOfProduct);
    //Update product
    cin.ignore();
    int i = num;
    while(num)
    {
        string ID;
        cout<< "\t\t\t\t\t\t"<<"Enter product ID: "; getline(cin, ID);
        if(!Product::productList.count(ID))
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing product ID"<<ANSI_RESET<<endl;
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
                cout<< "\t\t\t\t\t\t"<<"Enter product ID: "; getline(cin, ID);
                if(Product::productList.count(ID))
                {
                    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Product ID does exist, try again!"<<ANSI_RESET<<endl;
                }
                else
                {
                    cout<< "\t\t\t\t\t\t"<<"Enter product name: "; getline(cin, name);
                    cout<< "\t\t\t\t\t\t"<<"Enter product price: "; cin>>price;
                    cin.ignore();
                    product.setID(ID);
                    product.setName(name);
                    product.setPrice(price);
                    product.setQuantity();
                    product.setFeature();
                    Product::productList[ID] = product;
                    int choice;
                    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"Do you want to update individual watches of this product? (YES/NO):(1/0)"<<ANSI_RESET<<endl;
                    cin>>choice;
                    if(choice) Watch::UpdateWatch(ID);
                }
            }
            else
            {
                cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
            }
        }
        num--;
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
    cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000);
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<" Updates have been made."<<ANSI_RESET<<endl;
    Sleep(1000); // Sleep for 2 seconds
    outputFile.close();

}
