#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include"StatisticReport.h"

void gotoxy(int x, int y);
void delay(int milliseconds);
void runMessage(string message);
int enterPassword();

// Function prototypes
void displayMainMenu();

void myLoad();
void myCustomer();
void myCategory();
void myProduct();
void myOrder();
void myStatisticReport();

void Execute_Menu();

#endif // MYFUNCTION_H
