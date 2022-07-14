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
    static allocator<string> alloc;//�ڴ������
    void chk_n_alloc()//��������ڴ��Ƿ�����
    {
        if (size() == capacity())
            reallocate();
    }
    pair<string *, string *> alloc_n_copy(const string *, const string *);
    void free();
    void reallocate();
    string *elements;//�׵�ַ
    string *first_free;//���һ��Ԫ�صĵ�ַ
    string *cap;//�ѷ����ڴ��β��ַ
};
allocator<string> StrVec::alloc;

//�ƶ����캯��
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;//��ԭ�����ÿ�
}
//�ƶ���ֵ�����
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
    chk_n_alloc();//����ڴ��Ƿ��㹻
    alloc.construct(first_free++, s);//�������
}
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);//����һ���ڴ�ռ�
    return {data, uninitialized_copy(b, e, data)};//��b��e��Ԫ�ظ��Ƶ�data��
}
void StrVec::free()
{
    if (elements == nullptr)
        return;
    for (auto p = first_free; p != elements;)
    {
        alloc.destroy(--p);//���ٶ���
    }
    alloc.deallocate(elements, cap - elements);//�ͷ��ڴ�
}
//���캯��
StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());//Ϊs�����ڴ�
    elements = newdata.first;//��ʼ������ָ��
    first_free = cap = newdata.second;
}
//��������
StrVec::~StrVec()
{
    free();
}
StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free(); //���ԭ����this����
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate()
{
    auto newcap = size() ? size() * 2 : 1;//����2���ռ�
    auto newdata = alloc.allocate(newcap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); i++)
    {
        alloc.construct(dest++, move(*elem++));//�Ѿ��ڴ�������ƶ������ڴ�ռ���
    }
    //�ͷž��ڴ棬����ָ��
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcap;
}
#endif