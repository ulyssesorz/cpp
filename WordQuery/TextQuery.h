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
    using line_no = vector<string>::size_type; //定义行号的类型成员
    TextQuery(ifstream &);                     //构造函数：用于生成map
    QueryResult query(const string &) const;   //查询并向QueryResult返回结果

private:
    shared_ptr<StrVec> file;                  //可共享的文件数据
    map<string, shared_ptr<set<line_no>>> wm; //存储单词和行号的映射关系，行号可共享
};
class QueryResult
{
    //打印查询结果，print内需要访问TextQuery的私有成员，故设置为友元
    friend ostream &print(ostream &, const QueryResult &);

public:
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>> l, shared_ptr<StrVec> f) : sought(s), lines(l), file(f) {} //构造函数列表初始化
    set<TextQuery::line_no>::iterator begin() const { return lines->begin(); }
    set<TextQuery::line_no>::iterator end() const { return lines->end(); }
    shared_ptr<StrVec> get_file() const { return file; }

private:
    string sought;                             //要查询的单词
    shared_ptr<set<TextQuery::line_no>> lines; //共享的行号集合
    shared_ptr<StrVec> file;                   //共享的文件数据
};

TextQuery::TextQuery(ifstream &is) : file(new StrVec) //初始化file，新建一块动态内存
{
    string text;
    while (getline(is, text)) //读入一行数据到text中
    {
        file->push_back(text);    // file一个元素就是一行
        int n = file->size() - 1; //行号，从0开始
        istringstream line(text); //转为输入流，便于分割为单词
        string word;              //用于存储每个单词
        while (line >> word)      //每行line分为每个单词word
        {
            auto &lines = wm[word]; // line是指向与word关联的set的share指针
            if (!lines)             //不存在关联的行号，在set里新增一个
            {
                lines.reset(new set<line_no>);
            }
            lines->insert(n);
        }
    }
}
QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>); // static避免重复申请？
    auto loc = wm.find(sought);                               //在map中查询单词
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file); //没找到，返回nodata
    }
    else
    {
        return QueryResult(sought, loc->second, file); //找到，返回行号集合
    }
}
ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << "出现了" << qr.lines->size() << "次" << endl; //打印单词出现次数
    for (auto num : *qr.lines)                                       //遍历所有行号
    {
        os << "(行 " << num + 1 << ") "          //打印行号
           << *(qr.file->begin() + num) << endl; //打印行内容（利用file指针的偏移）
    }
    return os;
}
#endif