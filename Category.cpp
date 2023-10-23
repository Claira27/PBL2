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
    os<< ANSI_GREEN<<myCategory.ID<<"\t"<<myCategory.name<<ANSI_RESET <<endl;
    return os;
}
void Category::CategoryLoad()
{
    ifstream inputFile("Categories.txt");
    if (!inputFile)
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
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
    cout << "Fetching category data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<< ANSI_CYAN <<"Category ID\tName"<< ANSI_RESET<<endl;
    for(const auto& pair : categoryList)
            cout<<pair.second;
}
void Category::FindCategory()
{
    system("cls");
    string ID;
    cout<<"Finding category ID: "; getline(cin, ID);
    auto currentCategory = categoryList.find(ID);
    if(currentCategory != categoryList.end())
    {
        cout<<currentCategory->second;
    }
    else
    {
        cout<<ANSI_YELLOW<<"Non-existing category ID"<<ANSI_RESET<<endl;
        return;
    }
}
void Category::CreateCategory()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Categories.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new categories
    int num;
    do
    {
        cout<<"Enter the number of new categories to create: ";
        cin>>num;
        if(num  > 10)
        {
            cout<<ANSI_YELLOW << "No more than 10 categories to create at a time"<<ANSI_RESET << endl;
        }
    }while(num > 10);
    //Create new category
    cin.ignore();
    while(num--)
    {
        string ID;
        cout<<"Enter category ID: "; getline(cin, ID);
        if(!categoryList.count(ID))
        {
                // add new category's information
                Category newCategory;
                string name;
                cout << "Enter customer name: ";
                getline(cin, name);
                newCategory.setID(ID);
                newCategory.setName(name);
                categoryList[ID] = newCategory;
                //Write new customers to file
                outputFile<<newCategory.getID()<<","
                          <<newCategory.getName()<<","<<endl;
                numberOfCategory++;
        }
        else
        {
            cout<<ANSI_YELLOW<<"Category ID has already existed!"<<ANSI_RESET<<endl;
        }
    }
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    outputFile.close();
    cout<<ANSI_GREEN<<"Information written to file."<<ANSI_RESET<<endl;
}
int Category::ReferenceConstraint(string ID)
{
    system("cls");
    Category myCategory = categoryList.find(ID)->second;
    for(auto currentProduct : Product::productList)
    {
        string categoryIDbyGender = currentProduct.second.feature.gender;
        string categoryIDbyType = currentProduct.second.feature.type;
        if(categoryIDbyGender == myCategory.getName() || categoryIDbyType == myCategory.getName())
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
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of categories to erase
    int num;
    do
    {
        cout<<"Enter the number of categories to erase: ";
        cin>>num;
        if(num  > numberOfCategory)
        {
            cout<<ANSI_YELLOW<< "Exceeded the number of existing categories"<<ANSI_RESET<< endl;
        }
    }while(num > numberOfCategory);
    //Erase categories
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string ID;
        cout<<"Category ID "<<i<<": "; getline(cin, ID);
        if(categoryList.count(ID))
        {
            if(!ReferenceConstraint(ID))
            {
                map<string, Category>::iterator currentCategory = categoryList.find(ID);
                currentCategory->second.setID(" ");
                currentCategory->second.setName(" ");
                numberOfCategory--;
                i++;
            }
            else cout<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
        }
        else
            cout<<ANSI_YELLOW<<"Non-existing category ID"<<ANSI_RESET<<endl;
    }
    //Overwriting the file to erase catogories
    outputFile<<endl;
    for(auto currentCategory : categoryList)
    {
        if(currentCategory.second.getID() != " ")
            outputFile<<currentCategory.second.getID()<<","
                      <<currentCategory.second.getName()<<","<<endl;
    }
    outputFile.close();
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<<ANSI_GREEN<<num<<" Categories have been erased."<<ANSI_RESET<<endl;
}
void Category::UpdateCategory()
{
    system("cls");
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of categories to update
    int num;
    do
    {
        cout<<"Enter the number of categories to update: ";
        cin>>num;
        if(num  > numberOfCategory)
        {
            cout <<ANSI_YELLOW<< "Exceeded the number of existing customers" <<ANSI_RESET<< endl;
        }
    }while(num > numberOfCategory);
    //Update categories
    cin.ignore();
    int i = 1;
    while(i<=num)
    {
        string ID;
        cout<<"Category ID "<<i<<": "; getline(cin, ID);
        if(!categoryList.count(ID))
        {
            cout<<ANSI_YELLOW<<"Non-existing category ID"<<ANSI_RESET<<endl;
        }
        else
        {
            if(!ReferenceConstraint(ID))
            {
                // erase and create new to update category's new information
                categoryList.erase(ID);
                string ID, name;
                cout << "Enter category ID: "; getline(cin, ID);
                cout << "Enter category name: "; getline(cin, name);
                Category currentCategory;
                currentCategory.setID(ID);
                currentCategory.setName(name);
                categoryList[ID] = currentCategory;
                i++;
            }
            else cout<<ANSI_YELLOW<<"REFERENCE CONSTRAINT"<<ANSI_RESET<<endl;
        }
    }
    //Overwriting the file to update categories
    outputFile<<endl;
    for(auto currentCategogy : categoryList)
        outputFile<<currentCategogy.second.getID()<<","
                  <<currentCategogy.second.getName()<<","<<endl;
    outputFile.close();
    cout << "Generating your update..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<<ANSI_GREEN<<num<<" Updates have been made."<<ANSI_RESET<<endl;
}
