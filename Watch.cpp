#include"Watch.h"
#include"OrderDetail.h"

int Watch::numberOfWatch = 0;
map<string, Watch> Watch::watchList;

Watch::Watch() : productID("NULL"), serie(" "), availability(false){}
Watch::Watch(const string &productID, const string &serie, const bool avail) :
    productID(productID), serie(serie), availability(avail) {}
//Get information
string Watch::getID() const
{
    return ID;
}
string Watch::getProductID() const
{
    return productID;
}
string Watch::getSerie() const
{
    return serie;
}
bool Watch::getAvailability() const
{
    return availability;
}
//Mutator functions
void Watch::setID()
{
    this->ID = productID + serie;
}
void Watch::setProductID(string productID)
{
    this->productID = productID;
}
void Watch::setSerie(string serie)
{
    this->serie = serie;
}
void Watch::setAvailability(bool avail)
{
    this->availability = avail;
}

//Functions for CRUD
istream &operator>>(istream &is, Watch &myWatch)
{
    is.ignore();
    getline(is,myWatch.productID, ',');
    getline(is,myWatch.serie, ',');
    is>>myWatch.availability;
    return is;
}
ostream &operator<<(ostream &os, const Watch &myWatch)
{
    os<<myWatch.productID<<"\t"<<myWatch.serie<<"\t"<<myWatch.availability<<endl;
    return os;
}
void Watch::WatchLoad()
{
    ifstream inputFile("Watches.txt");
    if (!inputFile)
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    Watch watch;
    while (inputFile >> watch)
    {
        watchList[watch.getID()] = watch; // Add a new watch
        numberOfWatch++;
    }
    cout << "Information uploaded from file." << endl;
    inputFile.close();
}
int Watch::getNumberOfWatch()
{
    return numberOfWatch;
}
void Watch::ReadWatch()
{
    for(const auto& pair : watchList)
        cout<<pair.second;
}
void Watch::FindWatch()
{
    cin.ignore();
    string productID, serie;
    cout<<"Enter product ID: "; getline(cin, productID);
    cout<<"Enter serie: "; getline(cin, serie);
    auto currentWatch = watchList.find(productID + serie);
    if(currentWatch != watchList.end())
    {
        cout<<currentWatch->second;
    }
    else
    {
        cout<<"Non-existing watch serie"<<endl;
        return;
    }
}
void Watch::CreateWatch()
{
    ofstream outputFile;
    outputFile.open("Watch.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of new watches
    int num;
    do
    {
        cout<<"Enter the number of new watches to create: ";
        cin>>num;
        if(num  > 100)
        {
            cout << "No more than 100 watches to create at a time" << endl;
        }
    }while(num > 100);
    //Create new watch
    cin.ignore();
    while(num--)
    {
        // add new watch's information
        Watch newWatch;
        string productID;
        cout<<"Enter watch ID "<<productID<<": ";
        getline(cin, productID);
        string serie;
        cout << "Enter watch serie: ";
        getline(cin, serie);
        bool avail;
        cout<< "Enter watch availability: ";
        cin>>avail;
        if(watchList.count(productID + serie))
        {
            cout<<"Watch already existed"<<endl;
            num++;
        }
        else
        {
            //set new watch
            newWatch.setID();
            newWatch.setProductID(productID);
            newWatch.setSerie(serie);
            newWatch.setAvailability(avail);
            watchList[newWatch.getID()] = newWatch;
            //Write new watch to file
            outputFile<<newWatch.getProductID()<<","
                      <<newWatch.getSerie()<<","
                      <<newWatch.getAvailability()<<endl;
            numberOfWatch++;
        }
    }
    outputFile.close();
    cout<<"Information written to file."<<endl;
}
int Watch::ReferenceConstraint(const string& ID)
{
    for(auto watch : OrderDetail::saleList)
    {
        if(watch.second.getIDSerie() == ID)
            return 1;
    }
    return 0;
}
void Watch::EraseWatch()
{
    ofstream outputFile;
    outputFile.open("Watch.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Enter the number of watches to erase
    int num;
    do
    {
        cout<<"Enter the number of watches to erase: ";
        cin>>num;
        if(num  > numberOfWatch)
        {
            cout << "Exceeded the number of existing watches" << endl;
        }
    }while(num > numberOfWatch);
    //Erase watches
    cin.ignore();
    for(int i=1; i<=num; i++)
    {
        string productID;
        string serie;
        cout<<"Product ID "<<i<<": "; getline(cin, productID);
        cout<<"Watch serie "<<i<<": "; getline(cin, serie);
        if(watchList.count(productID + serie))
        {
            if(!ReferenceConstraint(productID+serie))
            {
                watchList.erase(productID + serie);
                numberOfWatch--;
            }
            else cout<<"Reference constraint!"<<endl;
        }
        else
            cout<<"Non-existing watch serie"<<endl;
    }
    //Overwriting the file to erase watches
    outputFile<<endl;
    for(auto currentWatch : watchList)
    {
            outputFile<<currentWatch.second.getProductID()<<","
                      <<currentWatch.second.getSerie()<<","
                      <<currentWatch.second.getAvailability()<<endl;
    }
    outputFile.close();
    cout<<num<<" Watches have been erased."<<endl;
}
void Watch::UpdateWatch()
{
    ofstream outputFile;
    outputFile.open("Watch.txt");
    if(!outputFile.is_open())
    {
        cout<<"Error: Unable to open the file."<<endl;
        return;
    }
    //Overwriting the file to update categories
    outputFile<<endl;
    for(auto currentWatch : watchList)
    {
            outputFile<<currentWatch.second.getProductID()<<","
                      <<currentWatch.second.getSerie()<<","
                      <<currentWatch.second.getAvailability()<<endl;
    }
    outputFile<<"Watches in stock have been updated."<<endl;
    outputFile.close();
}
