#include<stdlib.h>
#include<string.h>
int main()
{
    char* src;
    char *p = (char *)malloc(strlen(src));//错误开辟
    p = (char *)malloc(strlen(src) + 1);//正确开辟
    p =(char*)malloc(strlen(src+1));//错误开辟
    if((p=(char *)realloc(p,strlen(src+1)))){//错误开辟
        
    }
    return 0;
}
