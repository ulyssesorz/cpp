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

//主界面
void show()
{
    cout << "\t=============欢迎来到机房预约系统=============" << endl;
    cout << endl
         << "请输入您的选择：" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         1、学生           |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         2、教师           |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         3、管理员         |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|         0、退出           |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";
}

//管理员的子菜单
void managerMeue(Identity *manager)
{
    while (true)
    {
        manager->openMeue();
        Manager *m = (Manager *)manager; //转化为派生类指针
        int select;
        cout << "输入你的选项：" << endl;
        cin >> select;
        switch (select)
        {
        case 1:
            // cout << "添加账号" << endl;
            m->addPerson();
            break;
        case 2:
            // cout << "查看账号" << endl;
            m->showPerson();
            break;
            ;
        case 3:
            // cout << "查看机房信息" << endl;
            m->showComputer();
            break;
        case 4:
            // cout << "清空预约记录" << endl;
            m->cleanFile();
            break;
        default:
            delete manager;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//学生的子菜单
void studentMeue(Identity *student)
{
    while (true)
    {
        student->openMeue();
        Student *s = (Student *)student;
        cout << "输入你的选项：" << endl;
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
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//教师的子菜单
void teacherMeue(Identity *teacher)
{
    while (true)
    {
        teacher->openMeue();
        Teacher *t = (Teacher *)teacher;
        cout << "输入你的选项：" << endl;
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
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//登录功能，读入文件名和身份类型
void logIn(string filename, int type)
{
    Identity *person = nullptr;
    ifstream ifs;
    ifs.open(filename, ios::in); //打开文件
    if (!ifs.is_open())          //检查文件是否有效
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }
    int id;
    string name;
    string password;
    if (type == 1) //学生
    {
        cout << "请输入你的学号：" << endl;
        cin >> id;
    }
    else if (type == 2) //教师
    {
        cout << "请输入你的职工号：" << endl;
        cin >> id;
    }
    cout << "请输入用户名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> password;
    if (type == 1) //学生身份认证
    {
        //从文件中读取的信息
        int fid;
        string fname;
        string fpassword;
        while (ifs >> fid && ifs >> fname && ifs >> fpassword)
        {
            if (fid == id && fname == name && fpassword == password)
            {
                cout << "学生身份验证成功" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, password);
                //进入学生子菜单
                studentMeue(person);
                return;
            }
        }
    }
    else if (type == 2) //教师身份认证
    {
        //从文件中读取的信息
        int fid;
        string fname;
        string fpassword;
        while (ifs >> fid && ifs >> fname && ifs >> fpassword)
        {
            if (fid == id && fname == name && fpassword == password)
            {
                cout << "教师身份验证成功" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, password);
                //进入教师子菜单
                teacherMeue(person);
                return;
            }
        }
    }
    else if (type == 3) //管理员身份认证
    {
        //从文件中读取的信息
        string fname;
        string fpassword;
        while (ifs >> fname && ifs >> fpassword)
        {
            if (fname == name && fpassword == password)
            {
                cout << "管理员身份验证成功" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, password);
                //进入管理员子菜单
                managerMeue(person);
                return;
            }
        }
    }
    cout << "身份验证失败" << endl;
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
        case 1: //学生
            logIn(STUDENT_FILE, 1);
            break;
        case 2: //教师
            logIn(TEACHER_FILE, 2);
            break;
        case 3: //管理员
            logIn(ADMIN_FILE, 3);
            break;
        case 0:
            cout << "欢迎下次使用" << endl;
            return 0;
        default:
            cout << "输入有误，请重新输入" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}