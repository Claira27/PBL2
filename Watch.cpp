#include"Watch.h"
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
void Watch::setID()
{
    this->ID = productID + serie;
}
string Watch::getID()
{
    setID();
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

void Watch::WatchLoad()
{
    ifstream inputFile("Watch.txt");
    if (!inputFile)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
    }
    else
    {
        Watch watch;
        while (inputFile >> watch)
        {
            watchList[watch.getID()] = watch; // Add a new watch
            numberOfWatch++;
        }
    }
    inputFile.close();
}
int Watch::getNumberOfWatch()
{
    return numberOfWatch;
}
ostream &operator<<(ostream &os, const Watch &myWatch)
{
    cout<<"---------------------------------------------------------------"<<endl;
    os<<setw(6)<<"|"<< ANSI_GREEN<<setw(16)<<left<<myWatch.productID<<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_GREEN<<setw(16)<<left<<myWatch.serie<<ANSI_RESET<<setw(3)<<left<<"|"<< ANSI_GREEN<<setw(13)<<left<<myWatch.availability<< ANSI_RESET<<"|"<<endl;
    return os;
}
void Watch::ReadWatch(const string &productID)
{
    int check;
    //cout << "Fetching watch data..." << ANSI_BLINK << "..." << ANSI_RESET << endl;

    cout<<endl;
    cout<< "\t\t\t\t\t\t"<<setw(6)<<left<<"|"<< ANSI_CYAN <<setw(16)<<left<<"Product ID"<<ANSI_RESET<<setw(6)<<left<<"|"<< ANSI_CYAN<<setw(16)<<left<<"Serie"<<ANSI_RESET<<setw(3)<<left<<"|"<< ANSI_CYAN<<setw(13)<<left<<"Availability"<< ANSI_RESET<<"|"<<endl;
    for(auto watch : watchList)
        if(watch.second.getProductID() == productID)
        {
            cout<< "\t\t\t\t\t\t"<<watch.second;
            check =1;
        }
    if(!check)
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"There are no items of product "<<productID<<" in stock!"<<ANSI_RESET<<endl;
        Sleep(1000);
    }
    else
    {
         cout<< "\t\t\t\t\t\t"<<"---------------------------------------------------------------"<<endl;
         getch();
    }
}

void Watch::CreateWatch(const string &productID)
{
    ofstream outputFile;
    outputFile.open("Watch.txt", std::ios::app);
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    //Enter the number of new watches
    int num;
    do
    {
        cout<< "\t\t\t\t\t\t"<<"Enter the number of new watches to create: ";
        cin>>num;
        if(num  > 10)
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW << "No more than 10 watches to create at a time"<<ANSI_RESET << endl;
        }
    }while(num > 10);
    //Create new watch
    cin.ignore();
    int i=num;
    while(i)
    {
        // add new watch's information
        Watch newWatch;
        string serie;
        cout<< "\t\t\t\t\t\t" << "Enter watch serie: ";
        getline(cin, serie);
        bool avail;
        cout<< "\t\t\t\t\t\t"<< "Enter watch availability: ";
        cin>>avail;
        if(watchList.count(productID + serie))
        {
            cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Watch already existed"<<ANSI_RESET<<endl;
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
            num--;
        }
    }
    if(!num) cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"There are no items in your stock! Add items later"<<ANSI_RESET<<endl;
    outputFile.close();

}
int Watch::ReferenceConstraint(const string& ID)
{
    //for(auto watch : OrderDetail::saleList)
    //    if(watch.second.getIDSerie() == ID)
            return 1;
    return 0;
}
void Watch::EraseWatch(const string &productID)
{
    ofstream outputFile;
    outputFile.open("Watch.txt");
    if(!outputFile.is_open())
    {
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    auto it = watchList.begin();
    while (it != watchList.end())
    {
        if (it->second.getProductID() == productID)
        {
            if (!ReferenceConstraint(it->first))
            {
                it = watchList.erase(it);
                numberOfWatch--;
            }
            else
            {
                ++it;
            }
        }
        else
        {
            ++it;
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
        cout<< "\t\t\t\t\t\t"<<ANSI_RED<<"Error: Unable to open the file."<<ANSI_RESET<<endl;
        return;
    }
    string serie;
    cout<< "\t\t\t\t\t\t"<<"Enter serie of watch: "; getline(cin, serie);
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
                cout<< "\t\t\t\t\t\t"<<"Enter new availability state of watch: "; cin>>avail;
                newWatch.setAvailability(avail);
                watchList.erase(productID + serie);
                watchList[productID + serie] = newWatch;
            }
            else cout<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Reference constraint!"<<ANSI_RESET<<endl;
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
    outputFile<< "\t\t\t\t\t\t"<<ANSI_YELLOW<<"Watches in stock have been updated."<<ANSI_RESET<<endl;
    outputFile.close();
}
