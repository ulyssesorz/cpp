#ifndef STRVEC_H_
#define STRVEC_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

using namespace std;

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr){};
    ~StrVec();
    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(StrVec &&) noexcept;
    void push_back(const string &);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    string *begin() const { return elements; }
    string *end() const { return first_free; }

private:
    static allocator<string> alloc;//内存分配器
    void chk_n_alloc()//检查分配的内存是否已满
    {
        if (size() == capacity())
            reallocate();
    }
    pair<string *, string *> alloc_n_copy(const string *, const string *);
    void free();
    void reallocate();
    string *elements;//首地址
    string *first_free;//最后一个元素的地址
    string *cap;//已分配内存的尾地址
};
allocator<string> StrVec::alloc;

//移动构造函数
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;//把原对象置空
}
//移动赋值运算符
StrVec &StrVec::operator=(StrVec &&s) noexcept
{
    if (this != &s)
    {
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap = nullptr;
    }
    return *this;
}
void StrVec::push_back(const string &s)
{
    chk_n_alloc();//检查内存是否足够
    alloc.construct(first_free++, s);//构造对象
}
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);//申请一块内存空间
    return {data, uninitialized_copy(b, e, data)};//将b到e的元素复制到data中
}
void StrVec::free()
{
    if (elements == nullptr)
        return;
    for (auto p = first_free; p != elements;)
    {
        alloc.destroy(--p);//销毁对象
    }
    alloc.deallocate(elements, cap - elements);//释放内存
}
//构造函数
StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());//为s分配内存
    elements = newdata.first;//初始化三个指针
    first_free = cap = newdata.second;
}
//析构函数
StrVec::~StrVec()
{
    free();
}
StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free(); //清空原本的this内容
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate()
{
    auto newcap = size() ? size() * 2 : 1;//分配2倍空间
    auto newdata = alloc.allocate(newcap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); i++)
    {
        alloc.construct(dest++, move(*elem++));//把旧内存的内容移动到新内存空间内
    }
    //释放旧内存，更新指针
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcap;
}
#endif