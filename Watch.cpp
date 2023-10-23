#include"Watch.h"
#include"OrderDetail.h"
// ANSI color codes for text
const string ANSI_RESET = "\033[0m";
const string ANSI_RED = "\033[31m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_YELLOW = "\033[33m";
const string ANSI_CYAN = "\033[36m";
const string ANSI_BOLD = "\033[1m";
const string ANSI_BLINK = "\033[5m";
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
    os<< ANSI_GREEN<<myWatch.productID<<"\t"<<myWatch.serie<<"\t"<<myWatch.availability<< ANSI_RESET<<endl;
    return os;
}
void Watch::WatchLoad()
{
    ifstream inputFile("Watches.txt");
    if (!inputFile)
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    Watch watch;
    while (inputFile >> watch)
    {
        watchList[watch.getID()] = watch; // Add a new watch
        numberOfWatch++;
    }
    inputFile.close();
}
int Watch::getNumberOfWatch()
{
    return numberOfWatch;
}
void Watch::ReadWatch(const string &productID)
{
    cout << "Fetching watch data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;
    sleep(2000000); // Sleep for 2 seconds
    cout<< ANSI_CYAN <<"Product ID\tSerie\tAvailability"<< ANSI_RESET<<endl;
    for(const auto& pair : watchList)
        cout<<pair.second;
}

void Watch::CreateWatch(const string &productID)
{
    ofstream outputFile;
    outputFile.open("Watch.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
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
            cout<<ANSI_YELLOW << "No more than 100 watches to create at a time"<<ANSI_RESET << endl;
        }
    }while(num > 100);
    //Create new watch
    cin.ignore();
    while(num--)
    {
        // add new watch's information
        Watch newWatch;
        string serie;
        cout << "Enter watch serie: ";
        getline(cin, serie);
        bool avail;
        cout<< "Enter watch availability: ";
        cin>>avail;
        if(watchList.count(productID + serie))
        {
            cout<<ANSI_YELLOW<<"Watch already existed"<<ANSI_RESET<<endl;
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
void Watch::EraseWatch(const string &productID)
{
    ofstream outputFile;
    outputFile.open("Watch.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    for(auto watch : watchList)
    {
        if(watch.second.getProductID() == productID)
        {
            if(!ReferenceConstraint(watch.first))
                {
                    watchList.erase(watch.first);
                    numberOfWatch--;
                }
        }
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
}
void Watch::UpdateWatch(const string &productID)
{
    ofstream outputFile;
    outputFile.open("Watch.txt");
    if(!outputFile.is_open())
    {
        cout<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    string serie;
    cout<<"Enter serie of watch: "; getline(cin, serie);
    for(auto watch : watchList)
    {
        if(watch.first == productID + serie)
        {
            if(!ReferenceConstraint(watch.first))
            {
                Watch newWatch;
                newWatch.setProductID(productID);
                newWatch.setSerie(serie);
                newWatch.setID();
                bool avail;
                cout<<"Enter new availability state of watch: "; cin>>avail;
                newWatch.setAvailability(avail);
                watchList.erase(productID + serie);
                watchList[productID + serie] = newWatch;
            }
            else cout<<ANSI_YELLOW<<"Reference constraint!"<<ANSI_RESET<<endl;
        }
    }
    //Overwriting the file to update categories
    outputFile<<endl;
    for(auto currentWatch : watchList)
    {
            outputFile<<currentWatch.second.getProductID()<<","
                      <<currentWatch.second.getSerie()<<","
                      <<currentWatch.second.getAvailability()<<endl;
    }
    outputFile<<ANSI_YELLOW<<"Watches in stock have been updated."<<ANSI_RESET<<endl;
    outputFile.close();
}
