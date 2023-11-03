#include"Manage.h"
//Category
bool Manage::CategoryLoad()
{
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
            categoryList.push_back(category); // Add a new customer
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
vector<Category> Manage::ReadCategory()
{
    return categoryList;
}
bool Manage::FindCategory(string categoryID)
{
    auto it = std::find_if(categoryList.begin(), categoryList.end(), [categoryID](const Category& category) {}
        return category.getID() == categoryID;
        });
    return (it != categoryList.end());
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
            outputFile<<newCategory.getID()<<","
                      <<newCategory.getName()<<","<<endl;
            numberOfCategory++;
            outputFile.close();
            return 1;
        }
    }
}
bool Manage::ReferenceConstraint_Category(string ID)
{
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
bool Manage::EraseCategory(string categoryID)
{
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(ReferenceConstraint_Category(categoryID))
            return 0;
        else
        {
            for(auto category = categoryList.begin(); category != categoryList.end(); ++category)
                if(*category.getID() == categoryID)
                {
                    categoryList.erase(category);
                    numberOfCategory--;
                    //Overwriting the file to erase categories
                    outputFile<<endl;
                    for(auto currentCategory : categoryList)
                    {
                        outputFile<<currentCategory.getID()<<","
                                  <<currentCategory.getName()<<","<<endl;
                    }
                    outputFile.close();
                    return 1;
                }
            outputFile.close();
            return 0;
        }
    }
}
bool Manage::UpdateCategory(string currentID, string newID, string name)
{
    ofstream outputFile;
    outputFile.open("Categories.txt");
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(ReferenceConstraint_Category(currentID))
            return 0;
        else
        {
            for(auto category = categoryList.begin(); category != categoryList.end(); ++category)
                if(*category.getID() == currentID)
                {
                    *category.setID(newID);
                    *category.setName(name);
                    //Overwriting the file to erase categories
                    outputFile<<endl;
                    for(auto currentCategory : categoryList)
                    {
                        outputFile<<currentCategory.getID()<<","
                                  <<currentCategory.getName()<<","<<endl;
                    }
                    outputFile.close();
                    return 1;
                }
            outputFile.close();
            return 0;
        }
    }
}

//Product
bool ProductLoad()
{
    ifstream inputFile("Product.txt");
    if (!inputFile)
    {
        inputFile.close();
        return 0;
    }
    else
    {
        Product product;
        while (inputFile >> product)
        {
            productList.push_back(product); // Add a new customer
            numberOfProduct++;
        }
        inputFile.close();
        return 1;
    }
}
int getNumberOfProduct()
{
    return numberOfProduct;
}
vector<Product> ReadProduct()
{
    return productList;
}
bool FindProduct(string ID)
{
    auto it = std::find_if(productList.begin(), productList.end(), [categoryID](const Product& product) {}
        return product.getID() == ID;
        });
    return (it != productList.end());
}
bool CreateProduct(string ID, string name, double price, Description feature, int quantity = 0)
{
    ofstream outputFile;
    outputFile.open("Products.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(FindProduct(ID))
            return 0;
        else
        {
            // add new category's information
            Product newProduct;
            newProduct.setID(ID);
            newProduct.setName(name);
            newProduct.setPrice(price);
            newProduct.setFeature(feature);
            newProduct.setQuantity();
            categoryList.push_back(newProduct);
            //write file
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
            numberOfProduct++;
            outputFile.close();
            return 1;
        }
    }
}
bool Eraseproduct(string ID)
{
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(ReferenceConstraint_Product(ID))
            return 0;
        else
        {
            for(auto product = productList.begin(); Product != productList.end(); ++produ+
            ct)
                if(*product.getID() == ID)
                {
                    productList.erase(product);
                    numberOfProduct--;
                    //Overwriting the file to erase categories
                    outputFile<<endl;
                    for(auto product : productList)
                    {
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
                    }
                    outputFile.close();
                    return 1;
                }
            outputFile.close();
            return 0;
        }
    }
}
bool UpdateProduct(string currentID, string newID, string name, double price, Description feature, int quantity = 0);
{
    ofstream outputFile;
    outputFile.open("Products.txt");
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(ReferenceConstraint_Product(ID))
            return 0;
        else
        {
            for(auto product = productList.begin(); Product != productList.end(); ++product)
                if(*product.getID() == ID)
                {
                    product.setID(ID);
                    product.setName(name);
                    product.setPrice(price);
                    product.setFeature(feature);
                    product.setQuantity();
                    //Overwriting the file to erase categories
                    outputFile<<endl;
                    for(auto product : productList)
                    {
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
                    }
                    outputFile.close();
                    return 1;
                }
            outputFile.close();
            return 0;
        }
    }
}

//Product detail
bool Manage::WatchLoad()
{
    ifstream inputFile("Watch.txt");
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
vector<Watch> Manage::ReadWatch()
{
    return watchList;
}
bool Manage::FindWatch(string ID)
{
    auto it = std::find_if(watchList.begin(), watchList.end(), [ID](const Watch& watch) {}
        return watch.getID() == ID;
        });
    return (it != watchList.end());
}
bool Manage::CreateWatch(const string &productID, const string &serie, bool avail)
{
    ofstream outputFile;
    outputFile.open("Watches.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(FindWatch(productID+serie))
            return 0;
        else
        {
            // add new watch's information
            Watch newWatch
            newWatch.setProductID(productID);
            newWatch.setSerie(serie);
            newWatch.setID();
            categoryList.push_back(newWatch);
            //write file
            outputFile<<newWatch.getProductID()<<","
                      <<newWatch.getSerie()<<","
                      <<newWatch.getAvailability()<<endl;
            numberOfWatch++;
            outputFile.close();
            return 1;
        }
    }
}
bool Manage::ReferenceConstraint_Watch(const string& ID)
{
    auto it = std::find_if(watchList.begin(), watchList.end(), [ID](const Watch& watch) {}
        return watch.getID() == ID;
    });
    if(*it.getAvailability()) return 0;
    else return 1;
}
bool Manage::EraseWatch(const string &productID, const string &serie)
{
    ofstream outputFile;
    outputFile.open("Watches.txt");
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(ReferenceConstraint_Watch(productID+serie))
            return 0;
        else
        {
            for(auto watch = watchList.begin(); Watch != watchList.end(); ++watch)
                if(*watch.getID() == productID+serie)
                {
                    categoryList.erase(watch);
                    numberOfWatch--;
                    //Overwriting the file to erase categories
                    outputFile<<endl;
                    for(auto currentWatch : watchList)
                    {
                        outputFile<<currentWatch.getProductID()<<","
                                  <<currentWatch.getSerie()<<","
                                  <<currentWatch.getAvailability()<<endl;
                    }
                    outputFile.close();
                    return 1;
                }
            outputFile.close();
            return 0;
        }
    }
}
bool Manage::UpdateWatch(const string &ID, bool avail)
{
    ofstream outputFile;
    outputFile.open("Watches.txt");
    if(!outputFile.is_open())
    {
        outputFile.close();
        return 0;
    }
    else
    {
        if(ReferenceConstraint_Watch(productID+serie))
            return 0;
        else
        {
            for(auto watch = watchList.begin(); Watch != watchList.end(); ++watch)
                if(*watch.getID() == productID+serie)
                {
                    watch.setAvailability(avail);
                    //Overwriting the file to erase categories
                    outputFile<<endl;
                    for(auto currentWatch : watchList)
                    {
                        outputFile<<currentWatch.getProductID()<<","
                                  <<currentWatch.getSerie()<<","
                                  <<currentWatch.getAvailability()<<endl;
                    }
                    outputFile.close();
                    return 1;
                }
            outputFile.close();
            return 0;
        }
    }
}
