#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "globalFile.h"
using namespace std;

class Order
{
public:
    Order() : m_size(0) { initMap(); }
    void updateOrder(); //更新预约
    void initMap();

    int m_size; //预约条数
    map<int, map<string, string>> orderData;
    // key为记录编号，value为具体信息
};

pair<string, string> getInfo(const string &item)
{
    string key;
    string value;
    int pos = item.find(":");
    if(pos != -1)
    {
        key = item.substr(0, pos);
        value = item.substr(pos + 1, item.size() - pos - 1);
        return make_pair(key, value);
    }
    return {"", ""};
}
void Order::initMap()
{
    ifstream ifs;
    ifs.open(ORDER_FIILE, ios::in);

    //预约信息
    string stu_id;
    string name;
    string date;
    string interval;
    string room;
    string status;

    while (ifs >> stu_id && ifs >> name && ifs >> date 
    && ifs >> interval && ifs >> room && ifs >> status)
    {
        //处理预约信息
        map<string, string> m;
        m.insert(getInfo(stu_id));
        m.insert(getInfo(name));
        m.insert(getInfo(date));
        m.insert(getInfo(interval));
        m.insert(getInfo(room));
        m.insert(getInfo(status));

        orderData.insert(make_pair(m_size, m));
        m_size++;
    }
    ifs.close();
}

void Order::updateOrder()
{
    if(m_size == 0)
        return;
    ofstream ofs(ORDER_FIILE, ios::out | ios::trunc);
    for(int i = 0; i < m_size; i++)
    {
        ofs << "stu_id:" << orderData[i]["stu_id"] << " ";
        ofs << "name:" << orderData[i]["name"] << " ";
        ofs << "date:" << orderData[i]["date"] << " ";
        ofs << "interval:" << orderData[i]["interval"] << " ";
        ofs << "room:" << orderData[i]["room"] << " ";
        ofs << "status:" << orderData[i]["status"] << endl;
    }
    ofs.close();
}