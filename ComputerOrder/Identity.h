#pragma once
#include <string>
using namespace std;

class Identity
{
public:
    Identity() {}
    Identity(string n, string psw) : name(n), password(psw) {}
    virtual void openMeue() = 0; //�˵�
    
    string name;     //����
    string password; //����
};