#include<iostream>
#include<exception>
using namespace std;    
void foo()
{
    try{
    }catch(std::exception &e){
        cout<<"hello world";
    }
    
    try{
    }catch(std::exception &e){
    }
    
}
int main()
{   
    return 0;
}
