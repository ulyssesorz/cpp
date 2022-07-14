#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<algorithm>
#include "globalFile.h"
#include "Identity.h"
#include "Teacher.h"
#include "Student.h"
#include "Computer.h"
using namespace std;

class Manager : public Identity
{
public:
    Manager(string n, string psw) : Identity(n, psw) { initVector(); }
    void openMeue() override; //�˵�
    void addPerson();         //����˺�
    void showPerson();        //�鿴�˺�
    void showComputer();      //�鿴������Ϣ
    void cleanFile();         //���ԤԼ��¼
    void initVector();        //��ʼ������
    bool checkRepeat(int, int);//�����������Ϣ�Ƿ����ظ�
private:
    vector<Student> vStu;
    vector<Teacher> vTea;
    vector<Computer> vCpt;
};

void Manager::openMeue() //�˵�
{
    cout << "\t=========��ӭ����Ա" << name << "��������ԤԼϵͳ=========" << endl;
    cout << endl
         << "����������ѡ��" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        1������˺�        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        2���鿴�˺�        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        3���鿴������Ϣ    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        4�����ԤԼ��¼    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        0��ע����¼        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";
}

void Manager::addPerson() //����˺�
{
    cout << "��������ӵ����ͣ�" << endl;
    cout << "1�����ѧ��" << endl;
    cout << "2����ӽ�ʦ" << endl;

    int select;      //����ѡ��
    string filename; //�ļ���
    string tip;      //��ʾѧ�Ż�ְ����
    ofstream ofs;    //д�ļ���
    string errTip;

    cin >> select;
    if (select == 1)
    {
        filename = STUDENT_FILE;
        tip = "������ѧ�ţ�";
        errTip = "ѧ���ظ�������������";
    }
    else
    {
        filename = TEACHER_FILE;
        tip = "������ְ�����";
        errTip = "ְ�����ظ�������������";
    }
    ofs.open(filename, ios::out | ios::app); //׷��д��
    int id;
    string name;
    string password;

    cout << tip << endl;
    while(true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if(ret)
        {
            cout << errTip << endl;
        }
        else
        {
            break;
        }
    }
    //������������
    cout << "����������" << endl;
    cin >> name;
    cout << "����������" << endl;
    cin >> password;
    //д���ļ���
    ofs << id << " " << name << " " << password << endl;
    cout << "��ӳɹ�";
    system("pause");
    system("cls");
    ofs.close();
    initVector();//ÿ�����֮�����³�ʼ������
}

void printStudent(Student &s)
{
    cout << "ѧ��Ϊ��" << s.stu_id << " ����Ϊ��" << s.name
    << " ����Ϊ��" << s.password << endl;
}

void printTeacher(Teacher &t)
{
    cout << "ְ����Ϊ��" << t.tch_id << " ����Ϊ��" << t.name
    << " ����Ϊ��" << t.password << endl;
}

void printComputer(Computer &c)
{
    cout << "������� " << c.cpt_id << 
    " ���������Ϊ��" << c.max_num << endl;
}

void Manager::showPerson() //�鿴�˺�
{ 
    cout << "��������Ҫ�鿴�����ͣ�" << endl;
    cout << "1���鿴ѧ��" << endl;
    cout << "2���鿴��ʦ" << endl;

    int select;
    cin >> select;
    if(select == 1)//ѧ��
    {
        cout << "����ѧ����Ϣ���£�" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else//��ʦ
    {
        cout << "���н�ʦ��Ϣ���£�" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    system("pause");
    system("cls");
}

void Manager::showComputer() //�鿴������Ϣ
{
    cout << "���л�����Ϣ���£�" << endl;
    for_each(vCpt.begin(), vCpt.end(), printComputer);
    system("pause");
    system("cls");
}

void Manager::cleanFile() //���ԤԼ��¼
{
    ofstream ofs(ORDER_FIILE, ios::trunc);
    ofs.close();
    cout << "��ճɹ�" << endl;
    system("pause");
    system("cls");
}

void Manager::initVector() //��ʼ������
{
    vStu.clear(); //�������
    vTea.clear();
    vCpt.clear();
    ifstream ifs;
    //��ʼ��ѧ����Ϣ
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "���ļ�ʧ��" << endl;
        return;
    }
    Student s;
    while (ifs >> s.stu_id && ifs >> s.name && ifs >> s.password)
    {
        vStu.push_back(s);
    }
    cout << "ѧ������Ϊ " << vStu.size() << endl;
    ifs.close();

    //��ʼ����ʦ��Ϣ
    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "���ļ�ʧ��" << endl;
        return;
    }
    Teacher t;
    while (ifs >> t.tch_id && ifs >> t.name && ifs >> t.password)
    {
        vTea.push_back(t);
    }
    cout << "��ʦ����Ϊ " << vTea.size() << endl;
    ifs.close();

    //��ʼ��������Ϣ
    ifs.open(COMPUTER_FILE, ios::in);
    Computer c;
    while(ifs >> c.cpt_id && ifs >> c.max_num)
    {
        vCpt.push_back(c);
    }
    cout << "��������Ϊ " << vCpt.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type)//����
{
    if(type == 1)//ѧ��
    {
        for(auto it = vStu.begin(); it != vStu.end(); it++)
        {
            if(id == it->stu_id)//�����ظ�
                return true;
        }
    }
    if(type == 2)//��ʦ
    {
        for(auto it = vTea.begin(); it != vTea.end(); it++)
        {
            if(id == it->tch_id)
                return true;
        }
    }
    return false;
}