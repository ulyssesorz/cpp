#ifndef QUERY_H_
#define QEURY_H_
#include "TextQuery.h"
#include <algorithm>

//�������
class Query_base
{
    friend class Query; // Query����Ҫ����eval��rep

protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual string rep() const = 0;
};

class Query
{
    //�������Ҫ����˽�й��캯��������Ϊ��Ԫ
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);

public:
    Query(const string &);
    QueryResult eval(const TextQuery &t) const { return q->eval(t); } //��ָ��ʵ�ֶ�̬��
    string rep() const { return q->rep(); }

private:
    Query(shared_ptr<Query_base> query) : q(query) {}
    shared_ptr<Query_base> q; //���ڵ����麯��
};
ostream &operator<<(ostream &os, const Query &query)
{
    return os << query.rep();
}

//���ʲ�ѯ
class WordQuery : public Query_base
{
    friend class Query;
    WordQuery(const string &s) : query_word(s) {}
    //����ѯһ�����ʳ��ֵ�����������TextQuery��query��������
    QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
    string rep() const { return query_word; }
    string query_word;
};
//Query�Ĺ��캯����ʼ��һ��WordQuery�������ڵ��ʲ�ѯ
inline Query::Query(const string &s) : q(new WordQuery(s)) {}

//�ǲ�ѯ
class NotQuery : public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}
    QueryResult eval(const TextQuery &t) const;
    string rep() const { return "~(" + query.rep() + ")"; }
    Query query;
};
inline Query operator~(const Query &operand)//����~�����������һ��NotQuery����
{
    auto tmp = shared_ptr<Query_base>(new NotQuery(operand));
    return Query(tmp);
}

//��Ԫ�����
class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, const string &s) : lhs(l), rhs(r), opsym(s) {}
    string rep() const { return "(" + lhs.rep() + " " + opsym + " " + rhs.rep() + ")"; }
    Query lhs, rhs;
    string opsym;
};

//������
class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") {}
    QueryResult eval(const TextQuery &) const;
};
inline Query operator&(const Query &l, const Query &r)
{
    auto tmp = shared_ptr<Query_base>(new AndQuery(l, r));//����һ��AndQuery����
    return Query(tmp);
}

//������
class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "|") {}
    QueryResult eval(const TextQuery &) const;
};
inline Query operator|(const Query &l, const Query &r)
{
    auto tmp = shared_ptr<Query_base>(new OrQuery(l, r));//����һ��OrQuery����
    return Query(tmp);
}

QueryResult OrQuery::eval(const TextQuery &t) const
{
    auto left = lhs.eval(t), right = rhs.eval(t);
    //�õ�������ʼ���кż���
    auto ret_lines = make_shared<set<TextQuery::line_no>>(left.begin(), left.end());
    //������һ����ѯ���кż���
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}
QueryResult AndQuery::eval(const TextQuery &t) const
{
    auto left = lhs.eval(t), right = rhs.eval(t);
    auto ret_lines = make_shared<set<TextQuery::line_no>>();
    //�ϲ�������ѯ���
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
            ret_lines->insert(i);//����û�г��ֵ��к�
        else if (beg != end)
            beg++;
    }
    return QueryResult(rep(), ret_lines, res.get_file());
}
#endif