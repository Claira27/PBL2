#include"Category.h"
#include"Product.h"

int Category::numberOfCategory=0;
map<string, Category> Category::categoryList;

//construction
Category::Category(): ID(" "), name(" ") {}
Category::Category(const string &ID, const string &name) :
    ID(ID), name(name) {}
//Get information
string Category::getID() const
{
    return ID;
}
string Category::getName() const
{
    return name;
}
//Mutator functions
void Category::setID(const string &ID)
{
    this->ID=ID;
}
void Category::setName(const string &name)
{
    this->name=name;
}
//Functions for CRUD
istream &operator>>(istream &is, Category &myCategory)
{
    is.ignore();
    getline(is,myCategory.ID, ',');
    getline(is,myCategory.name, ',');
    return is;
}
ostream &operator<<(ostream &os, const Category &myCategory)
{

    os <<setw(6)<<"|"<< ANSI_GREEN<<setw(16)<<left<<myCategory.ID
        <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_GREEN<<setw(16)<<left<<myCategory.name<<ANSI_RESET <<"|"<<endl;
    return os;
}
void Category::CategoryLoad()
{
    ifstream inputFile("Categories.txt");
    if (!inputFile)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    Category category;
    while (inputFile >> category)
    {
        categoryList[category.getID()] = category; // Add a new customer
        numberOfCategory++;
    }
    inputFile.close();
}
int Category::getNumberOfCategory()
{
    return numberOfCategory;
}
void Category::ReadCategory()
{
    system("cls");
    cout << "\t\t\t\t\t\t"<< "Fetching category data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(500); // Sleep for 2 seconds
    cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"=============Category information==========="<<ANSI_RESET<<endl;
    cout<<endl;
    cout<< "\t\t\t\t\t\t"<<setw(6)<<left<<"|"<< ANSI_CYAN <<setw(16)<<left<<"Category ID"
        <<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(16)<<left<<"Name"<< ANSI_RESET<<"|"<<endl;
    for(const auto& pair : categoryList)
    {
        cout<< "\t\t\t\t\t\t"<<"-------------------------------------------"<<endl;
        cout<< "\t\t\t\t\t\t"<<pair.second;
    }
    cout<< "\t\t\t\t\t\t"<<"-------------------------------------------"<<endl;
    getch();
}
void Category::FindCategory()
{
    //system("cls");
    string ID;
    cin.ignore();
    cout<< "\t\t\t\t\t\t"<<"Finding category ID: "; getline(cin, ID);
    system("cls");
    auto currentCategory = categoryList.find(ID);
    if(currentCategory != categoryList.end())
    {
        cout<< "\t\t\t\t\t\t"<<currentCategory->second;
        cout<<ANSI_YELLOW<<"o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o"<<ANSI_RESET<<endl;
        for(auto entry : Product::productList)
        {
            const Product& product = entry.second;
            const string& type = product.getFeature().type; // classify products by type
            const string& gender = product.getFeature().gender;// classify products by gender
            if(type == ID || gender == ID)
                cout<<product;
        }
        getch();
    }
    else
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing category ID"<<ANSI_RESET<<endl;
        Sleep(1000);
    }

}
void Category::CreateCategory()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Categories.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new categories
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of new categories to create: ";
        cin>>num;
        if(num  > 10)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "No more than 10 categories to create at a time"<<ANSI_RESET << endl;
        }
    }while(num > 10);
    //Create new category
    cin.ignore();
    while(num)
    {
        string ID;
        cout<< "\t\t\t\t\t\t"<<"Enter category ID: "; getline(cin, ID);
        if(!categoryList.count(ID))
        {
                // add new category's information
                Category newCategory;
                string name;
                cout << "\t\t\t\t\t\t"<< "Enter Category name: ";
                getline(cin, name);
                newCategory.setID(ID);
                newCategory.setName(name);
                categoryList[ID] = newCategory;
                //Write new customers to file
                outputFile<<newCategory.getID()<<","
                          <<newCategory.getName()<<","<<endl;
                numberOfCategory++;
                num--;
        }
        else
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Category ID has already existed!"<<ANSI_RESET<<endl;
            num--;
        }
    }
    cout<< "\t\t\t\t\t\t" << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 2 seconds
    outputFile.close();
    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<"Information written to file."<<ANSI_RESET<<endl;
    Sleep(1000);
}
int Category::ReferenceConstraint(string ID)
{
    system("cls");
    Category myCategory = categoryList.find(ID)->second;
    for(auto currentProduct : Product::productList)
    {
        string categoryIDbyGender = currentProduct.second.feature.gender;
        string categoryIDbyType = currentProduct.second.feature.type;
        if(categoryIDbyGender == myCategory.getID() || categoryIDbyType == myCategory.getID())
            return 1;
    }
    return 0;
}
void Category::EraseCategory()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of categories to erase
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of categories to erase: ";
        cin>>num;
        if(num  > numberOfCategory)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<< "Exceeded the number of existing categories"<<ANSI_RESET<< endl;
        }
    }while(num > numberOfCategory);
    //Erase categories
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string ID;
        cout<< "\t\t\t\t\t\t"<<"Category ID "<<i<<": "; getline(cin, ID);
        if(categoryList.count(ID))
        {
            if(!ReferenceConstraint(ID))
            {
                categoryList.erase(ID);
                numberOfCategory--;
                i++;
            }
            else
            {
                cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
                i++;
            }
        }
        else
            {cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing category ID"<<ANSI_RESET<<endl;
            i++;}
    }
    //Overwriting the file to erase categories
    outputFile<<endl;
    for(auto currentCategory : categoryList)
    {
        outputFile<<currentCategory.second.getID()<<","
                  <<currentCategory.second.getName()<<","<<endl;
    }
    outputFile.close();
    cout<< "\t\t\t\t\t\t" << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 2 seconds
    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<" Categories have been erased."<<ANSI_RESET<<endl;
    Sleep(1000);
}
void Category::UpdateCategory()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of categories to update
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of categories to update: ";
        cin>>num;
        if(num  > numberOfCategory)
        {
            cout<< "\t\t\t\t\t\t" <<ANSI_YELLOW<< "Exceeded the number of existing customers" <<ANSI_RESET<< endl;
        }
    }while(num > numberOfCategory);
    //Update categories
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string ID;
        cout<< "\t\t\t\t\t\t"<<"Category ID "<<i<<": "; getline(cin, ID);
        if(!categoryList.count(ID))
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Non-existing category ID"<<ANSI_RESET<<endl;
        }
        else
        {
            if(!ReferenceConstraint(ID))
            {
                // erase and create new to update category's new information
                categoryList.erase(ID);
                string name;
                cout<< "\t\t\t\t\t\t" << "Enter category name: "; getline(cin, name);
                Category newCategory;
                newCategory.setID(ID);
                newCategory.setName(name);
                categoryList[ID] = newCategory;
            }
            else
            {
                cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
            }
        }
        i++;
    }
    //Overwriting the file to update categories
    outputFile<<endl;
    for(auto currentCategogy : categoryList)
        outputFile<<currentCategogy.second.getID()<<","
                  <<currentCategogy.second.getName()<<","<<endl;
    outputFile.close();
    cout << "\t\t\t\t\t\t"<< "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    Sleep(1000); // Sleep for 2 seconds
    cout<< "\t\t\t\t\t\t"<<ANSI_GREEN<<" Updates have been made."<<ANSI_RESET<<endl;
    Sleep(1000);
}
