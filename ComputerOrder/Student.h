#pragma once
#include "Identity.h"
#include "Computer.h"
#include "globalFile.h"
#include "Order.h"
#include <vector>
#include <fstream>
using namespace std;

class Student : public Identity
{
    friend void initVector();

public:
    Student(){};
    Student(int id, string n, string psw) : Identity(n, psw), stu_id(id) {initVector();}
    void openMeue() override; //菜单
    void applyOrder();        //申请预约
    void showMyOrder();       //查看自身预约
    void showAllOrder();      //查看所有预约
    void cancelOrder();       //取消预约
    void initVector();

    int stu_id;
    vector<Computer> vCpt;
};

void Student::openMeue() //菜单
{
    cout << "\t=========欢迎学生" << name << "来到机房预约系统=========" << endl;
    cout << endl
         << "请输入您的选择：" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        1、申请预约        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        2、查看我的预约    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        3、查看所有预约    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        4、取消预约        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        0、注销登录        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";
}

void Student::applyOrder() //申请预约
{
    int date = 0;//日期
    int interval = 0;//时间段
    int room = 0;//机房编号

    cout << "请输入申请预约的时间：" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;
    while(true)
    {
        cin >> date;
        if(date >= 1 && date <= 5)
            break;
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "请输入申请的时间段" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;
    while(true)
    {
        cin >> interval;
        if(interval == 1 || interval == 2)
            break;
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "请输入申请的机房编号" << endl;
    for(int i = 0; i < vCpt.size(); i++)
    {
        cout << vCpt[i].cpt_id << " 号机房容量为 " << vCpt[i].max_num << endl; 
    }
    while(true)
    {
        cin >> room;
        if(room >= 1 && room <= vCpt.size())
            break;
        cout << "输入有误，请重新输入" << endl; 
    }
    cout << "预约成功，审核中" << endl;

    //写入文件中
    ofstream ofs;
    ofs.open(ORDER_FIILE, ios::app);
    ofs << "stu_id:" << stu_id << " ";
    ofs << "name:" << name << " ";
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "room:" << room << " ";
    ofs << "status:" << 1 << endl;
    ofs.close();
    system("pause");
    system("cls");
}

void Student::showMyOrder() //查看自身预约
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i = 0; i < o.m_size; i++)
    {
        if(stu_id == atoi(o.orderData[i]["stu_id"].c_str()))
        {
            cout << "预约时间：周" << o.orderData[i]["date"];
            cout << " 预约时间段：" << (o.orderData[i]["interval"] ==
                 "1" ? "上午" : "下午");
            cout << " 机房编号：" << o.orderData[i]["room"];
            string status = " 状态：";
            //1审核中， 2预约成功， -1预约失败，0取消预约
            if(o.orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if(o.orderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if(o.orderData[i]["status"] == "-1")
            {
                status += "预约失败";
            }
            else
            {
                status += "预约已取消";
            }   
            cout << status << endl;     
        }
    }
    system("pause");
    system("cls");
}

void Student::showAllOrder() //查看所有预约
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i = 0; i < o.m_size; i++)
    {
        cout << "学号：" << o.orderData[i]["stu_id"];
        cout << " 姓名：" << o.orderData[i]["name"];
        cout << " 预约时间：周" << o.orderData[i]["date"];
        cout << " 预约时间段：" << (o.orderData[i]["interval"] ==
                "1" ? "上午" : "下午");
        cout << " 机房编号：" << o.orderData[i]["room"];
        string status = " 状态：";
        //1审核中， 2预约成功， -1预约失败，0取消预约
        if(o.orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if(o.orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if(o.orderData[i]["status"] == "-1")
        {
            status += "预约失败";
        }
        else
        {
            status += "预约已取消";
        }   
        cout << status << endl;     
    }
    system("pause");
    system("cls"); 
}

void Student::cancelOrder() //取消预约
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "审核中或预约成功的记录可以取消:" << endl;
    int idx = 1;
    vector<int> vec;//存放编号
    for(int i = 0; i < o.m_size; i++)
    {
        if(stu_id == atoi(o.orderData[i]["stu_id"].c_str()))
        {
            if(o.orderData[i]["status"] == "1" || o.orderData[i]["status"] == "2")
            {
                vec.push_back(i);
                cout << idx++ << "、";
                cout << "预约时间：周" << o.orderData[i]["date"];
                cout << " 预约时间段：" << (o.orderData[i]["interval"] ==
                "1" ? "上午" : "下午");
                cout << " 机房编号：" << o.orderData[i]["room"];                
                string status = " 状态：";
                if(o.orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                if(o.orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;
            }        
        }
    }
    cout << "请输入你的选择，0代表返回" << endl;
    int select;
    while(true)
    {
        cin >> select;
        if(select >= 0 && select <= vec.size())
        {
            if(select == 0)
            {
                break;
            }
            else
            {
                o.orderData[vec[select - 1]]["status"] = "0";
                o.updateOrder();
                cout << "已取消预约" << endl;
                break;
            }
        }
       cout << "输入有误，请重新输入" << endl;
    }
    system("pause");
    system("cls");
}

void Student::initVector()
{
    vCpt.clear();
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "打开文件失败" << endl;
        return;
    }

    Computer c;
    while(ifs >> c.cpt_id && ifs >> c.max_num)
    {
        vCpt.push_back(c);
    }
    ifs.close();
}