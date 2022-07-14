#ifndef QUERY_H_
#define QEURY_H_
#include "TextQuery.h"
#include <algorithm>

//抽象基类
class Query_base
{
    friend class Query; // Query类需要调用eval和rep

protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual string rep() const = 0;
};

class Query
{
    //运算符需要调用私有构造函数，设置为友元
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);

public:
    Query(const string &);
    QueryResult eval(const TextQuery &t) const { return q->eval(t); } //用指针实现动态绑定
    string rep() const { return q->rep(); }

private:
    Query(shared_ptr<Query_base> query) : q(query) {}
    shared_ptr<Query_base> q; //用于调用虚函数
};
ostream &operator<<(ostream &os, const Query &query)
{
    return os << query.rep();
}

//单词查询
class WordQuery : public Query_base
{
    friend class Query;
    WordQuery(const string &s) : query_word(s) {}
    //仅查询一个单词出现的行数，调用TextQuery的query函数即可
    QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
    string rep() const { return query_word; }
    string query_word;
};
//Query的构造函数初始化一个WordQuery对象用于单词查询
inline Query::Query(const string &s) : q(new WordQuery(s)) {}

//非查询
class NotQuery : public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}
    QueryResult eval(const TextQuery &t) const;
    string rep() const { return "~(" + query.rep() + ")"; }
    Query query;
};
inline Query operator~(const Query &operand)//重载~运算符，分配一个NotQuery对象
{
    auto tmp = shared_ptr<Query_base>(new NotQuery(operand));
    return Query(tmp);
}

//二元运算符
class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, const string &s) : lhs(l), rhs(r), opsym(s) {}
    string rep() const { return "(" + lhs.rep() + " " + opsym + " " + rhs.rep() + ")"; }
    Query lhs, rhs;
    string opsym;
};

//与运算
class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") {}
    QueryResult eval(const TextQuery &) const;
};
inline Query operator&(const Query &l, const Query &r)
{
    auto tmp = shared_ptr<Query_base>(new AndQuery(l, r));//分配一个AndQuery对象
    return Query(tmp);
}

//或运算
class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "|") {}
    QueryResult eval(const TextQuery &) const;
};
inline Query operator|(const Query &l, const Query &r)
{
    auto tmp = shared_ptr<Query_base>(new OrQuery(l, r));//分配一个OrQuery对象
    return Query(tmp);
}

QueryResult OrQuery::eval(const TextQuery &t) const
{
    auto left = lhs.eval(t), right = rhs.eval(t);
    //用迭代器初始化行号集合
    auto ret_lines = make_shared<set<TextQuery::line_no>>(left.begin(), left.end());
    //插入另一个查询的行号集合
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}
QueryResult AndQuery::eval(const TextQuery &t) const
{
    auto left = lhs.eval(t), right = rhs.eval(t);
    auto ret_lines = make_shared<set<TextQuery::line_no>>();
    //合并两个查询结果
    set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}
QueryResult NotQuery::eval(const TextQuery &t) const
{
    auto res = query.eval(t);
    auto ret_lines = make_shared<set<TextQuery::line_no>>();
    auto beg = res.begin(), end = res.end();
    auto sz = res.get_file()->size();
    for (size_t i = 0; i < sz; i++)
    {
        if (*beg != i)
            ret_lines->insert(i);//插入没有出现的行号
        else if (beg != end)
            beg++;
    }
    return QueryResult(rep(), ret_lines, res.get_file());
}
#endif