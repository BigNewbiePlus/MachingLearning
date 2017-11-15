#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
int main()
{
    
    wstring myDBFName;
    printf("Cannot open database %s",myDBFName.c_str());
    
    char SendBuf[1024];
    std::string encoded_login;
    sprintf(SendBuf, "AUTH PLAIN %s",encoded_login.c_str());
    
    return 0;    
}
