#include "Date.h"

bool NamNhuan(int nam)
{
    return ((nam%400==0) || (nam%4==0 && nam%100!=0));
}
int ngayTrongThang(int thang, int nam)
{
    if(thang==2)
        return NamNhuan(nam) ? 29 : 28;
    else if(thang==4 || thang==6 || thang==9 || thang==11) return 30;
    else return 31;
}
void Date::input()
{
    do
    {
        cout<<"Nhap ngay thang nam: "<<endl;
        cin>>ngay>>thang>>nam;
        if(ngay<=0 || ngay>ngayTrongThang(thang, nam))
            cout<<"Nhap lai ngay thang nam hop le!"<<endl;
    }while(ngay<=0 || ngay>ngayTrongThang(this->thang, this->nam) || thang<1 || thang>12 || nam<0);
}
void Date::display()
{
    cout<<ngay<<"/"<<thang<<"/"<<nam<<endl;
}
Date Date::nextDate()
{
    Date kq;
    if(this->ngay==ngayTrongThang(this->thang, this->nam))
    {
        kq.ngay=1;
        if(this->thang==12)
        {
            kq.thang=1;
            kq.nam=this->nam+1;
        }
        else
        {
            kq.thang=this->thang+1;
            kq.nam=this->nam;
        }
    }
    else
    {
        kq.ngay=this->ngay+1;
        kq.thang=this->thang;
        kq.nam=this->nam;
    }
    return kq;
}
Date Date::prevDate()
{
    Date kq;
    if(this->ngay==1)
    {
        if(this->thang==1)
        {
            kq.ngay=this->nam-1;
            kq.thang=12;
            kq.ngay=this->ngay;
        }
        else
        {
            kq.thang=this->thang-1;
            kq.ngay=ngayTrongThang(kq.thang, kq.nam);
            kq.nam=this->nam;
        }
    kq.ngay=ngayTrongThang(kq.thang, kq.nam);
    }
    else
    {
        kq.ngay=this->ngay-1;
        kq.thang=this->thang;
        kq.nam=this->nam;
    }
    return kq;
}
