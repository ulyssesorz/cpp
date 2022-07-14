#include"StrVec.h"

int main()
{
    StrVec sv;
    sv.push_back("hello");
    sv.push_back("world");
    sv.push_back("!");
    cout << *sv.begin() << endl;
    cout << sv.size() << endl;
    cout << sv.capacity() << endl;
    return 0;
}