//#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "globalFile.h"
#include "Identity.h"
#include "Student.h"
#include "Teacher.h"
#include "Manager.h"
#include "Student.h"
using namespace std;

//������
void show()
{
    cout << "\t=============��ӭ��������ԤԼϵͳ=============" << endl;
    cout << endl
         << "����������ѡ��" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         1��ѧ��           |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         2����ʦ           |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         3������Ա         |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         0���˳�           |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";
}

//����Ա���Ӳ˵�
void managerMeue(Identity *manager)
{
    while (true)
    {
        manager->openMeue();
        Manager *m = (Manager *)manager; //ת��Ϊ������ָ��
        int select;
        cout << "�������ѡ�" << endl;
        cin >> select;
        switch (select)
        {
        case 1:
            // cout << "����˺�" << endl;
            m->addPerson();
            break;
        case 2:
            // cout << "�鿴�˺�" << endl;
            m->showPerson();
            break;
            ;
        case 3:
            // cout << "�鿴������Ϣ" << endl;
            m->showComputer();
            break;
        case 4:
            // cout << "���ԤԼ��¼" << endl;
            m->cleanFile();
            break;
        default:
            delete manager;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//ѧ�����Ӳ˵�
void studentMeue(Identity *student)
{
    while (true)
    {
        student->openMeue();
        Student *s = (Student *)student;
        cout << "�������ѡ�" << endl;
        int select;
        cin >> select;
        switch (select)
        {
        case 1:
            s->applyOrder();
            break;
        case 2:
            s->showMyOrder();
            break;
        case 3:
            s->showAllOrder();
            break;
        case 4:
            s->cancelOrder();
            break;
        default:
            delete student;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//��ʦ���Ӳ˵�
void teacherMeue(Identity *teacher)
{
    while (true)
    {
        teacher->openMeue();
        Teacher *t = (Teacher *)teacher;
        cout << "�������ѡ�" << endl;
        int select;
        cin >> select;
        switch (select)
        {
        case 1:
            t->showAllOrder();
            break;
        case 2:
            t->validOrder();
            break;
        default:
            delete teacher;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//��¼���ܣ������ļ������������
void logIn(string filename, int type)
{
    Identity *person = nullptr;
    ifstream ifs;
    ifs.open(filename, ios::in); //���ļ�
    if (!ifs.is_open())          //����ļ��Ƿ���Ч
    {
        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }
    int id;
    string name;
    string password;
    if (type == 1) //ѧ��
    {
        cout << "���������ѧ�ţ�" << endl;
        cin >> id;
    }
    else if (type == 2) //��ʦ
    {
        cout << "���������ְ���ţ�" << endl;
        cin >> id;
    }
    cout << "�������û�����" << endl;
    cin >> name;
    cout << "���������룺" << endl;
    cin >> password;
    if (type == 1) //ѧ�������֤
    {
        //���ļ��ж�ȡ����Ϣ
        int fid;
        string fname;
        string fpassword;
        while (ifs >> fid && ifs >> fname && ifs >> fpassword)
        {
            if (fid == id && fname == name && fpassword == password)
            {
                cout << "ѧ�������֤�ɹ�" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, password);
                //����ѧ���Ӳ˵�
                studentMeue(person);
                return;
            }
        }
    }
    else if (type == 2) //��ʦ�����֤
    {
        //���ļ��ж�ȡ����Ϣ
        int fid;
        string fname;
        string fpassword;
        while (ifs >> fid && ifs >> fname && ifs >> fpassword)
        {
            if (fid == id && fname == name && fpassword == password)
            {
                cout << "��ʦ�����֤�ɹ�" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, password);
                //�����ʦ�Ӳ˵�
                teacherMeue(person);
                return;
            }
        }
    }
    else if (type == 3) //����Ա�����֤
    {
        //���ļ��ж�ȡ����Ϣ
        string fname;
        string fpassword;
        while (ifs >> fname && ifs >> fpassword)
        {
            if (fname == name && fpassword == password)
            {
                cout << "����Ա�����֤�ɹ�" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, password);
                //�������Ա�Ӳ˵�
                managerMeue(person);
                return;
            }
        }
    }
    cout << "�����֤ʧ��" << endl;
    system("pause");
    system("cls");
    return;
}

int main()
{
    while (true)
    {
        show();
        int select;
        cin >> select;
        switch (select)
        {
        case 1: //ѧ��
            logIn(STUDENT_FILE, 1);
            break;
        case 2: //��ʦ
            logIn(TEACHER_FILE, 2);
            break;
        case 3: //����Ա
            logIn(ADMIN_FILE, 3);
            break;
        case 0:
            cout << "��ӭ�´�ʹ��" << endl;
            return 0;
        default:
            cout << "������������������" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}