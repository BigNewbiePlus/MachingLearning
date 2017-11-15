#include<string.h>
    
struct unit1{
};

void foo1(){
    int buffer1[256];
    memset(buffer1,0,sizeof(*buffer1)); //wrong
    memset(buffer1,0,sizeof(buffer1)); //true 
}

void foo2(){
    unit1 buffer2[256];
    memset(buffer2,0,sizeof(*buffer2)); //wrong
    memset(buffer2,0,sizeof(buffer2)); //true  
}

void foo3(){
    int buffer1[256];
    memset(buffer1,0,256); //wrong
    memset(buffer1,0,256*sizeof(int)); //true
}

void foo4()
{
   unit1* unit;
    memset(unit, 0, sizeof(unit)); //wrong
    memset(unit, 0, sizeof(*unit)); //true` 
}

void foo5()
{
    int buffer1[256];
    int buffer3[256];
    memcpy(buffer1,buffer3, 256);//wrong
    memcpy(buffer1,buffer3, 256*sizeof(int));//true 
}
int main()
{
    return 0;    
}
