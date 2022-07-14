#pragma once
#include"Identity.h"
using namespace std;

class Teacher : public Identity
{
public:
    Teacher() {};
    Teacher(int id, string n, string psw) : Identity(n, psw), tch_id(id) {}
    void openMeue() override;
    void showAllOrder();//查看所有预约
    void validOrder();//审核预约
    
    int tch_id;
};

void Teacher::openMeue()//菜单
{
    cout << "\t=========欢迎教师" << name << "来到机房预约系统=========" << endl;
    cout << endl
         << "请输入您的选择：" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        1、查看所有预约    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        2、审核预约        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        0、注销登录        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";

}
void Teacher::showAllOrder()//查看所有预约
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

void Teacher::validOrder()//审核预约
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "待审核的预约如下：" << endl;
    vector<int> vec;
    int idx = 1;
    for(int i = 0; i < o.m_size; i++)
    {
        if(o.orderData[i]["status"] == "1")
        {
            vec.push_back(i);
            cout << idx++ << "、" ;
            cout << "学号：" << o.orderData[i]["stu_id"];
            cout << " 姓名：" << o.orderData[i]["name"];
            cout << " 预约时间：周" << o.orderData[i]["date"];
            cout << " 预约时间段：" << (o.orderData[i]["interval"] ==
            "1" ? "上午" : "下午");
            cout << "状态：审核中" << endl;
        }
    }

    cout << "请输入审核的预约结果，0代表返回" << endl;
    int select;
    int ret = 0;
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
                cout << "请输入审核结果" << endl;
                cout << "1、通过" << endl;
                cout << "2、不通过" << endl;
                cin >> ret;
                if(ret == 1)
                {
                    o.orderData[vec[select - 1]]["status"] = "2";
                }
                else
                {
                    o.orderData[vec[select - 1]]["status"] = "-1";
                }
                o.updateOrder();//更新审核后的数据
                cout << "审核完成" << endl;
                break;
            }
        }
    }
    system("pause");
    system("cls");
}