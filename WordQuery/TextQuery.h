#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include "StrVec.h"

class QueryResult;
class TextQuery
{
public:
    using line_no = vector<string>::size_type; //�����кŵ����ͳ�Ա
    TextQuery(ifstream &);                     //���캯������������map
    QueryResult query(const string &) const;   //��ѯ����QueryResult���ؽ��

private:
    shared_ptr<StrVec> file;                  //�ɹ�����ļ�����
    map<string, shared_ptr<set<line_no>>> wm; //�洢���ʺ��кŵ�ӳ���ϵ���кſɹ���
};
class QueryResult
{
    //��ӡ��ѯ�����print����Ҫ����TextQuery��˽�г�Ա��������Ϊ��Ԫ
    friend ostream &print(ostream &, const QueryResult &);

public:
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>> l, shared_ptr<StrVec> f) : sought(s), lines(l), file(f) {} //���캯���б��ʼ��
    set<TextQuery::line_no>::iterator begin() const { return lines->begin(); }
    set<TextQuery::line_no>::iterator end() const { return lines->end(); }
    shared_ptr<StrVec> get_file() const { return file; }

private:
    string sought;                             //Ҫ��ѯ�ĵ���
    shared_ptr<set<TextQuery::line_no>> lines; //������кż���
    shared_ptr<StrVec> file;                   //������ļ�����
};

TextQuery::TextQuery(ifstream &is) : file(new StrVec) //��ʼ��file���½�һ�鶯̬�ڴ�
{
    string text;
    while (getline(is, text)) //����һ�����ݵ�text��
    {
        file->push_back(text);    // fileһ��Ԫ�ؾ���һ��
        int n = file->size() - 1; //�кţ���0��ʼ
        istringstream line(text); //תΪ�����������ڷָ�Ϊ����
        string word;              //���ڴ洢ÿ������
        while (line >> word)      //ÿ��line��Ϊÿ������word
        {
            auto &lines = wm[word]; // line��ָ����word������set��shareָ��
            if (!lines)             //�����ڹ������кţ���set������һ��
            {
                lines.reset(new set<line_no>);
            }
            lines->insert(n);
        }
    }
}
QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>); // static�����ظ����룿
    auto loc = wm.find(sought);                               //��map�в�ѯ����
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file); //û�ҵ�������nodata
    }
    else
    {
        return QueryResult(sought, loc->second, file); //�ҵ��������кż���
    }
}
ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << "������" << qr.lines->size() << "��" << endl; //��ӡ���ʳ��ִ���
    for (auto num : *qr.lines)                                       //���������к�
    {
        os << "(�� " << num + 1 << ") "          //��ӡ�к�
           << *(qr.file->begin() + num) << endl; //��ӡ�����ݣ�����fileָ���ƫ�ƣ�
    }
    return os;
}
#endif