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
    void openMeue() override; //菜单
    void addPerson();         //添加账号
    void showPerson();        //查看账号
    void showComputer();      //查看机房信息
    void cleanFile();         //清空预约记录
    void initVector();        //初始化容器
    bool checkRepeat(int, int);//检查新增的信息是否有重复
private:
    vector<Student> vStu;
    vector<Teacher> vTea;
    vector<Computer> vCpt;
};

void Manager::openMeue() //菜单
{
    cout << "\t=========欢迎管理员" << name << "来到机房预约系统=========" << endl;
    cout << endl
         << "请输入您的选择：" << endl;
    cout << "\t\t-----------------------------\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        1、添加账号        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        2、查看账号        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        3、查看机房信息    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        4、清空预约记录    |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t|        0、注销登录        |\n";
    cout << "\t\t|                           |\n";
    cout << "\t\t-----------------------------\n";
}

void Manager::addPerson() //添加账号
{
    cout << "请输入添加的类型：" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加教师" << endl;

    int select;      //操作选项
    string filename; //文件名
    string tip;      //提示学号或职工号
    ofstream ofs;    //写文件流
    string errTip;

    cin >> select;
    if (select == 1)
    {
        filename = STUDENT_FILE;
        tip = "请输入学号：";
        errTip = "学号重复，请重新输入";
    }
    else
    {
        filename = TEACHER_FILE;
        tip = "请输入职工编号";
        errTip = "职工号重复，请重新输入";
    }
    ofs.open(filename, ios::out | ios::app); //追加写入
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
    //读入三种数据
    cout << "请输入姓名" << endl;
    cin >> name;
    cout << "请输入密码" << endl;
    cin >> password;
    //写入文件中
    ofs << id << " " << name << " " << password << endl;
    cout << "添加成功";
    system("pause");
    system("cls");
    ofs.close();
    initVector();//每次添加之后重新初始化容器
}

void printStudent(Student &s)
{
    cout << "学号为：" << s.stu_id << " 姓名为：" << s.name
    << " 密码为：" << s.password << endl;
}

void printTeacher(Teacher &t)
{
    cout << "职工号为：" << t.tch_id << " 姓名为：" << t.name
    << " 密码为：" << t.password << endl;
}

void printComputer(Computer &c)
{
    cout << "机房编号 " << c.cpt_id << 
    " 的最大容量为：" << c.max_num << endl;
}

void Manager::showPerson() //查看账号
{ 
    cout << "请输入你要查看的类型：" << endl;
    cout << "1、查看学生" << endl;
    cout << "2、查看教师" << endl;

    int select;
    cin >> select;
    if(select == 1)//学生
    {
        cout << "所有学生信息如下：" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else//教师
    {
        cout << "所有教师信息如下：" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    system("pause");
    system("cls");
}

void Manager::showComputer() //查看机房信息
{
    cout << "所有机房信息如下：" << endl;
    for_each(vCpt.begin(), vCpt.end(), printComputer);
    system("pause");
    system("cls");
}

void Manager::cleanFile() //清空预约记录
{
    ofstream ofs(ORDER_FIILE, ios::trunc);
    ofs.close();
    cout << "清空成功" << endl;
    system("pause");
    system("cls");
}

void Manager::initVector() //初始化容器
{
    vStu.clear(); //清空容器
    vTea.clear();
    vCpt.clear();
    ifstream ifs;
    //初始化学生信息
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "打开文件失败" << endl;
        return;
    }
    Student s;
    while (ifs >> s.stu_id && ifs >> s.name && ifs >> s.password)
    {
        vStu.push_back(s);
    }
    cout << "学生数量为 " << vStu.size() << endl;
    ifs.close();

    //初始化教师信息
    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "打开文件失败" << endl;
        return;
    }
    Teacher t;
    while (ifs >> t.tch_id && ifs >> t.name && ifs >> t.password)
    {
        vTea.push_back(t);
    }
    cout << "教师数量为 " << vTea.size() << endl;
    ifs.close();

    //初始化机房信息
    ifs.open(COMPUTER_FILE, ios::in);
    Computer c;
    while(ifs >> c.cpt_id && ifs >> c.max_num)
    {
        vCpt.push_back(c);
    }
    cout << "机房数量为 " << vCpt.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type)//查重
{
    if(type == 1)//学生
    {
        for(auto it = vStu.begin(); it != vStu.end(); it++)
        {
            if(id == it->stu_id)//出现重复
                return true;
        }
    }
    if(type == 2)//教师
    {
        for(auto it = vTea.begin(); it != vTea.end(); it++)
        {
            if(id == it->tch_id)
                return true;
        }
    }
    return false;
}