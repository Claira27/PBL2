#include "myFunctions.h"
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(int milliseconds) {
    sleep(milliseconds);
}

void runMessage(string message) {
    system("cls");
    string qc = message;
    int qc_size = qc.length();
    string temp = qc; // Directly assign the string
    qc += temp; // Use += to concatenate strings
    int i = 0;
    const int temp_size = 30; // Declare temp_size here
    char hien[temp_size + 1];
    while (!kbhit()) {
        strncpy(hien, qc.c_str() + i, temp_size); // Use c_str() to access the string's characters
        hien[temp_size] = '\0';
        gotoxy(40, 15);
        cout << hien;
        delay(100);
        i++;
        if (i == qc_size)
            i = 0;
    }
}

int enterPassword()
{
    char check[]="HongVy2002";
    char password[15];
    int count_try=0;
    do
    {
        system("cls");
        /*
        gotoxy(30,9);
        cout<<"ENTER PASSWORD";
        */
        gotoxy(30,11);
        int i=0;
        while((password[i]=getch())!=13 && ++i<15)      // Enter = 13
        {
            if(password[i-1]==8)                        // Backspace = 8
            {
                i=0;
                system("cls");
                gotoxy(30,11);
            }
            else
            {
                cout<<ANSI_CYAN<<"*"<<ANSI_RESET;
            }
        }
        password[i]='\0';
        cout<<endl;
        if(!strcmp(password, check))
        {
            gotoxy(30,13);
            cout<<ANSI_GREEN<<"Your password is correct! You are in....."<< ANSI_BLINK << "..." << ANSI_RESET << endl;
            sleep(1000);
            return 1;
        }

        else
        {
            gotoxy(30,13);
            cout<<ANSI_YELLOW<<"Your password is incorrect! Try again....."<< ANSI_BLINK << "..." << ANSI_RESET <<endl;
            sleep(1000);
            count_try++;
        }
    }while(count_try<3);
    cout<<ANSI_RED<<"You have enter wrong password three times!"<<ANSI_RESET<<endl;
    return 0;
}
void myLoad()
{
    Category::CategoryLoad();
    Customer::CustomerLoad();
    Order::OrderLoad();
    OrderDetail::SaleLoad();
    Product::ProductLoad();
    Watch::WatchLoad();
}
void myCustomer()
{
    char choice;
    while(true)
    {
        system("cls");
        sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
        cout << ANSI_BOLD << "*******************************************" << endl;
        cout << "     WELCOME TO CUSTOMER MANAGEMENT SYSTEM" << endl;
        cout << "*******************************************" << ANSI_RESET << endl;
        cout << setw(45) << ANSI_YELLOW << "1. [+] Create customer" << endl;
        cout << setw(45) << "2. [>] Read customer" << endl;
        cout << setw(45) << "2. [?] Find customer" << endl;
        cout << setw(45) << "4. [~] Update customer" << endl;
        cout << setw(45) << "5. [-] Erase customer" << endl;
        cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
        cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                Customer::CreateCustomerList();
                break;
            case '2':
                Customer::ReadCustomer();
                break;
            case '3':
                Customer::FindCustomer();
            case '4':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Customer::UpdateCustomer();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '5':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Customer::EraseCustomer();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '0':
                cout << ANSI_BOLD << "Exiting the customer management system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                return;
            default:
                cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
        }
    }
}
void myCategory()
{
    char choice;
    while(true)
    {
        system("cls");
        sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
        cout << ANSI_BOLD << "*******************************************" << endl;
        cout << "     WELCOME TO CATEGORY MANAGEMENT SYSTEM" << endl;
        cout << "*******************************************" << ANSI_RESET << endl;
        cout << setw(45) << ANSI_YELLOW << "1. [+] Create category" << endl;
        cout << setw(45) << "2. [>] Read category" << endl;
        cout << setw(45) << "2. [?] Find category" << endl;
        cout << setw(45) << "4. [~] Update category" << endl;
        cout << setw(45) << "5. [-] Erase category" << endl;
        cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
        cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                Category::CreateCategory();
                break;
            case '2':
                Category::ReadCategory();
                break;
            case '3':
                Category::FindCategory();
                break;
            case '4':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Category::UpdateCategory();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '5':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Category::EraseCategory();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '0':
                cout << ANSI_BOLD << "Exiting the category data management. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                return;
            default:
                cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
        }
    }
}
void myProduct()
{
    char choice;
    while (true)
    {
        system("cls");
        sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
        cout << ANSI_BOLD << "*******************************************" << endl;
        cout << "     WELCOME TO PRODUCT MANAGEMENT SYSTEM" << endl;
        cout << "*******************************************" << ANSI_RESET << endl;
        cout << setw(45) << ANSI_YELLOW << "1. [+] Create product" << endl;
        cout << setw(45) << "2. [>] Read product" << endl;
        cout << setw(45) << "3. [?] Find product" << endl;
        cout << setw(45) << "4. [~] Update product" << endl;
        cout << setw(45) << "5. [-] Erase product" << endl;
        cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
        cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                Product::CreateProduct();
                break;
            case '2':
                Product::ReadProduct();
                break;
            case '3':
                Product::FindProduct();
                break;
            case '4':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Product::UpdateProduct();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '5':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Product::Eraseproduct();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '0':
                cout << ANSI_BOLD << "Exiting the product data management. Goodbye!" << ANSI_BLINK << "..." << ANSI_RESET << endl;
                return;
            default:
                cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
        }
    }
}

void myOrder()
{
    char choice;
    while(true)
    {
        system("cls");
        sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
        cout << ANSI_BOLD << "*******************************************" << endl;
        cout << "     WELCOME TO ORDER MANAGEMENT SYSTEM" << endl;
        cout << "*******************************************" << ANSI_RESET << endl;
        cout << setw(45) << ANSI_YELLOW << "1. [+] Create order" << endl;
        cout << setw(45) << "2. [>] Read order" << endl;
        cout << setw(45) << "2. [?] Find order" << endl;
        cout << setw(45) << "4. [~] Update order" << endl;
        cout << setw(45) << "5. [-] Erase order" << endl;
        cout << setw(45) << "6. [ ] delete order" << endl;
        cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
        cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                Order::CreateOrder();
                break;
            case '2':
                Order::ReadOrder();
                break;
            case '3':
                Order::FindOrder();
            case '4':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Order::UpdateOrder();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '5':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Order::EraseOrder();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '6':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    Order::DeleteOrder();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '0':
                cout << ANSI_BOLD << "Exiting the Order data management. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                return;
            default:
                cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
        }
    }
}
void myStatisticReport()
{
    char choice;
    while(true)
    {
        system("cls");
        sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
        cout << ANSI_BOLD << "*******************************************" << endl;
        cout << "     WELCOME TO  STATISTIC REPORT SYSTEM" << endl;
        cout << "*******************************************" << ANSI_RESET << endl;
        cout << setw(45) << ANSI_YELLOW << "1. [+] the quantity of products by category" << endl;
        cout << setw(45) << "2. [>] the number of customers and the total number of orders" << endl;
        cout << setw(45) << "3. [<] the number of orders by period" << endl;
        cout << setw(45) << "4. [$] Revenue report by period" << endl;
        cout << setw(45) << "5. [*] Best-selling product of the year" << endl;
        cout << setw(45) << "6. [#] Manage inventory quantity by product" << endl;
        cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
        cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
                StatisticsReport::ProductByCategory();
                break;
            case '2':
                StatisticsReport::CustomerAndOrderStatistics();
                break;
            case '3':
                char period1;
                while(true)
                {
                    system("cls");
                    sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
                    cout << ANSI_BOLD << "*******************************************" << endl;
                    cout << "     CHOOSE PERIOD OF REPORT" << endl;
                    cout << "*******************************************" << ANSI_RESET << endl;
                    cout << setw(45) << ANSI_YELLOW << "1. [+] the number of orders by each day" << endl;
                    cout << setw(45) << "2. [>] the number of orders by each month" << endl;
                    cout << setw(45) << "3. [<] the number of orders by each quarter" << endl;
                    cout << setw(45) << "4. [~] the number of orders by each year" << endl;
                    cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
                    cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
                    cout << "Enter your choice: ";
                    cin >> period1;
                    switch(period1)
                    {
                        case '1':
                            StatisticsReport::OrdersByDay();
                            break;
                        case '2':
                            StatisticsReport::OrdersByMonth();
                            break;
                        case '3':
                            StatisticsReport::OrdersByQuarter();
                            break;
                        case '4':
                            StatisticsReport::OrdersByYear();
                            break;
                        case '0':
                            cout << ANSI_BOLD << "Exiting the statistic report system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                            return;
                        default:
                            cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                    }
                }
                break;
            case '4':
                char period2;
                while(true)
                {
                    system("cls");
                    sleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
                    cout << ANSI_BOLD << "*******************************************" << endl;
                    cout << "     CHOOSE PERIOD OF REPORT" << endl;
                    cout << "*******************************************" << ANSI_RESET << endl;
                    cout << setw(45) << ANSI_YELLOW << "1. [+] Revenue report by each month" << endl;
                    cout << setw(45) << "2. [>] Revenue report by each quarter" << endl;
                    cout << setw(45) << "3. [<] Revenue report by each year" << endl;
                    cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
                    cout << ANSI_BOLD<< "*******************************************" << ANSI_RESET<< endl;
                    cout << "Enter your choice: ";
                    cin >> period2;
                    switch(period2)
                    {
                        case '1':
                            StatisticsReport::RevenueByMonth();
                            break;
                        case '2':
                            StatisticsReport::RevenueByQuarter();
                            break;
                        case '3':
                            StatisticsReport::RevenueByYear();
                            break;
                        case '0':
                            cout << ANSI_BOLD << "Exiting the statistic report system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                            return;
                        default:
                            cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
                    }
                }
                break;
            case '5':
                StatisticsReport::BestSellingProductInYear();
                break;
            case '6':
                StatisticsReport::InventoryByProduct();
                break;
            case '0':
                cout << ANSI_BOLD << "Exiting the statistic report system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                return;
            default:
                cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
        }
    }
}

void displayMainMenu()
{
    system("cls"); // Clear the console screen (Unix-like systems)

    cout << ANSI_CYAN << "*******************************************" << endl;
    cout << "     WELCOME TO WATCH TORE MANAGEMENT SYSTEM" << endl;
    cout << "*******************************************" << ANSI_RESET << endl;
    cout << setw(45) << ANSI_YELLOW << "1. [+] Customer site" << endl;
    cout << setw(45) << "2. [>] Category site" << endl;
    cout << setw(45) << "3. [*] Product site" << endl;
    cout << setw(45) << "4. [~] Order site" << endl;
    cout << setw(45) << "5. [$] Statistic report site" << endl;
    cout << setw(45) << "0. [X] Exit" << ANSI_RESET << endl;
    cout << ANSI_CYAN<< "*******************************************" << ANSI_RESET<< endl;
    cout << "Enter your choice: ";
}

void Execute_Menu()
{
    myLoad();
    char choice;

    while(true)
    {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case '1':
                myCustomer();
                break;
            case '2':
                myCategory();
                break;
            case '3':
                myProduct();
                break;
            case '4':
                myOrder();
                break;
            case '5':
                cout<<ANSI_GREEN<<"Enter admin password to erase or update data "<<ANSI_RESET<<endl;
                if(enterPassword())
                    myStatisticReport();
                 else
                    cout<<ANSI_YELLOW<<"Sorry! You are eligible to perform this task!"<<ANSI_RESET<<endl;
                break;
            case '0':
                cout << ANSI_BOLD << "Exiting the watch store management system. Goodbye!" << ANSI_BLINK << "..."  << ANSI_RESET << endl;
                return;
            default:
                cout << ANSI_RED << "Invalid choice. Please select again." << ANSI_RESET << endl;
        }
    }

}
