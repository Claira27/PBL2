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
    os<<myCategory.ID<<"\t"<<myCategory.name<<endl;
    return os;
}
void Category::CategoryLoad()
{
    ifstream inputFile("Categories.txt");
    if (!inputFile)
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    Category category;
    while (inputFile >> category)
    {
        categoryList[category.getID()] = category; // Add a new customer
        numberOfCategory++;
    }
    cout << "Information uploaded from file." << endl;
    inputFile.close();
}
int Category::getNumberOfCategory()
{
    return numberOfCategory;
}
void Category::ReadCategory()
{
    for(const auto& pair : categoryList)
            cout<<pair.second;
}
void Category::FindCategory()
{
    string ID;
    cout<<"Finding category ID: "; getline(cin, ID);
    auto currentCategory = categoryList.find(ID);
    if(currentCategory != categoryList.end())
    {
        cout<<currentCategory->second;
    }
    else
    {
        cout<<"Non-existing category ID"<<endl;
        return;
    }
}
void Category::CreateCategory()
{
    ofstream outputFile;
    outputFile.open("Categories.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
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
            cout << "No more than 10 categories to create at a time" << endl;
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
            cout<<"Category ID has already existed!"<<endl;
        }
    }
    outputFile.close();
    cout<<"Information written to file."<<endl;
}
int Category::ReferenceConstraint(string ID)
{
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
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
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
            cout << "Exceeded the number of existing categories" << endl;
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
            else cout<<"REFERENCE CONSTRAINT"<<endl;
        }
        else
            cout<<"Non-existing category ID"<<endl;
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
    cout<<num<<" Categories have been erased."<<endl;
}
void Category::UpdateCategory()
{
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
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
            cout << "Exceeded the number of existing customers" << endl;
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
            cout<<"Non-existing category ID"<<endl;
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
            else cout<<"REFERENCE CONSTRAINT"<<endl;
        }
    }
    //Overwriting the file to update categories
    outputFile<<endl;
    for(auto currentCategogy : categoryList)
        outputFile<<currentCategogy.second.getID()<<","
                  <<currentCategogy.second.getName()<<","<<endl;
    outputFile.close();
    cout<<num<<" Updates have been made."<<endl;
}
