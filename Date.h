#include<bits/stdc++.h>
using namespace std;
#ifndef Date_h
#define Date_h
class Date
{
    int ngay, thang, nam;
public:
    Date(int d=0, int m=0, int y=0): ngay(d), thang(m), nam(y){}
    Date(Date &D): ngay(D.ngay), thang(D.thang), nam(D.nam){}
    void input();
    void display();
    Date nextDate();
    Date prevDate();
};
#endif
