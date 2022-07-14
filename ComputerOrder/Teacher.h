#pragma once
#include"Identity.h"
using namespace std;

class Teacher : public Identity
{
public:
    Teacher() {};
    Teacher(int id, string n, string psw) : Identity(n, psw), tch_id(id) {}
    void openMeue() override;
    void showAllOrder();//�鿴����ԤԼ
    void validOrder();//���ԤԼ
    
    int tch_id;
};

void Teacher::openMeue()//�˵�
{
    cout << "\t=========��ӭ��ʦ" << name << "��������ԤԼϵͳ=========" << endl;
    cout << endl
         << "����������ѡ��" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        1���鿴����ԤԼ    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        2�����ԤԼ        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        0��ע����¼        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";

}
void Teacher::showAllOrder()//�鿴����ԤԼ
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

void Teacher::validOrder()//���ԤԼ
{
    Order o;
    if(o.m_size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����˵�ԤԼ���£�" << endl;
    vector<int> vec;
    int idx = 1;
    for(int i = 0; i < o.m_size; i++)
    {
        if(o.orderData[i]["status"] == "1")
        {
            vec.push_back(i);
            cout << idx++ << "��" ;
            cout << "ѧ�ţ�" << o.orderData[i]["stu_id"];
            cout << " ������" << o.orderData[i]["name"];
            cout << " ԤԼʱ�䣺��" << o.orderData[i]["date"];
            cout << " ԤԼʱ��Σ�" << (o.orderData[i]["interval"] ==
            "1" ? "����" : "����");
            cout << "״̬�������" << endl;
        }
    }

    cout << "��������˵�ԤԼ�����0������" << endl;
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
                cout << "��������˽��" << endl;
                cout << "1��ͨ��" << endl;
                cout << "2����ͨ��" << endl;
                cin >> ret;
                if(ret == 1)
                {
                    o.orderData[vec[select - 1]]["status"] = "2";
                }
                else
                {
                    o.orderData[vec[select - 1]]["status"] = "-1";
                }
                o.updateOrder();//������˺������
                cout << "������" << endl;
                break;
            }
        }
    }
    system("pause");
    system("cls");
}