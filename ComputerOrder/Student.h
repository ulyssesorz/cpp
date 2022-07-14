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
    void openMeue() override; //�˵�
    void applyOrder();        //����ԤԼ
    void showMyOrder();       //�鿴����ԤԼ
    void showAllOrder();      //�鿴����ԤԼ
    void cancelOrder();       //ȡ��ԤԼ
    void initVector();

    int stu_id;
    vector<Computer> vCpt;
};

void Student::openMeue() //�˵�
{
    cout << "\t=========��ӭѧ��" << name << "��������ԤԼϵͳ=========" << endl;
    cout << endl
         << "����������ѡ��" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        1������ԤԼ        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        2���鿴�ҵ�ԤԼ    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        3���鿴����ԤԼ    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        4��ȡ��ԤԼ        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        0��ע����¼        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";
}

void Student::applyOrder() //����ԤԼ
{
    int date = 0;//����
    int interval = 0;//ʱ���
    int room = 0;//�������

    cout << "����������ԤԼ��ʱ�䣺" << endl;
    cout << "1����һ" << endl;
    cout << "2���ܶ�" << endl;
    cout << "3������" << endl;
    cout << "4������" << endl;
    cout << "5������" << endl;
    while(true)
    {
        cin >> date;
        if(date >= 1 && date <= 5)
            break;
        cout << "������������������" << endl;
    }

    cout << "�����������ʱ���" << endl;
    cout << "1������" << endl;
    cout << "2������" << endl;
    while(true)
    {
        cin >> interval;
        if(interval == 1 || interval == 2)
            break;
        cout << "������������������" << endl;
    }

    cout << "����������Ļ������" << endl;
    for(int i = 0; i < vCpt.size(); i++)
    {
        cout << vCpt[i].cpt_id << " �Ż�������Ϊ " << vCpt[i].max_num << endl; 
    }
    while(true)
    {
        cin >> room;
        if(room >= 1 && room <= vCpt.size())
            break;
        cout << "������������������" << endl; 
    }
    cout << "ԤԼ�ɹ��������" << endl;

    //д���ļ���
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

void Student::showMyOrder() //�鿴����ԤԼ
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i = 0; i < o.m_size; i++)
    {
        if(stu_id == atoi(o.orderData[i]["stu_id"].c_str()))
        {
            cout << "ԤԼʱ�䣺��" << o.orderData[i]["date"];
            cout << " ԤԼʱ��Σ�" << (o.orderData[i]["interval"] ==
                 "1" ? "����" : "����");
            cout << " ������ţ�" << o.orderData[i]["room"];
            string status = " ״̬��";
            //1����У� 2ԤԼ�ɹ��� -1ԤԼʧ�ܣ�0ȡ��ԤԼ
            if(o.orderData[i]["status"] == "1")
            {
                status += "�����";
            }
            else if(o.orderData[i]["status"] == "2")
            {
                status += "ԤԼ�ɹ�";
            }
            else if(o.orderData[i]["status"] == "-1")
            {
                status += "ԤԼʧ��";
            }
            else
            {
                status += "ԤԼ��ȡ��";
            }   
            cout << status << endl;     
        }
    }
    system("pause");
    system("cls");
}

void Student::showAllOrder() //�鿴����ԤԼ
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i = 0; i < o.m_size; i++)
    {
        cout << "ѧ�ţ�" << o.orderData[i]["stu_id"];
        cout << " ������" << o.orderData[i]["name"];
        cout << " ԤԼʱ�䣺��" << o.orderData[i]["date"];
        cout << " ԤԼʱ��Σ�" << (o.orderData[i]["interval"] ==
                "1" ? "����" : "����");
        cout << " ������ţ�" << o.orderData[i]["room"];
        string status = " ״̬��";
        //1����У� 2ԤԼ�ɹ��� -1ԤԼʧ�ܣ�0ȡ��ԤԼ
        if(o.orderData[i]["status"] == "1")
        {
            status += "�����";
        }
        else if(o.orderData[i]["status"] == "2")
        {
            status += "ԤԼ�ɹ�";
        }
        else if(o.orderData[i]["status"] == "-1")
        {
            status += "ԤԼʧ��";
        }
        else
        {
            status += "ԤԼ��ȡ��";
        }   
        cout << status << endl;     
    }
    system("pause");
    system("cls"); 
}

void Student::cancelOrder() //ȡ��ԤԼ
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ��:" << endl;
    int idx = 1;
    vector<int> vec;//��ű��
    for(int i = 0; i < o.m_size; i++)
    {
        if(stu_id == atoi(o.orderData[i]["stu_id"].c_str()))
        {
            if(o.orderData[i]["status"] == "1" || o.orderData[i]["status"] == "2")
            {
                vec.push_back(i);
                cout << idx++ << "��";
                cout << "ԤԼʱ�䣺��" << o.orderData[i]["date"];
                cout << " ԤԼʱ��Σ�" << (o.orderData[i]["interval"] ==
                "1" ? "����" : "����");
                cout << " ������ţ�" << o.orderData[i]["room"];                
                string status = " ״̬��";
                if(o.orderData[i]["status"] == "1")
                {
                    status += "�����";
                }
                if(o.orderData[i]["status"] == "2")
                {
                    status += "ԤԼ�ɹ�";
                }
                cout << status << endl;
            }        
        }
    }
    cout << "���������ѡ��0������" << endl;
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
                cout << "��ȡ��ԤԼ" << endl;
                break;
            }
        }
       cout << "������������������" << endl;
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
        cout << "���ļ�ʧ��" << endl;
        return;
    }

    Computer c;
    while(ifs >> c.cpt_id && ifs >> c.max_num)
    {
        vCpt.push_back(c);
    }
    ifs.close();
}