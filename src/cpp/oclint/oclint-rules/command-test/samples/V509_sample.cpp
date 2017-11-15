#include<exception>
class A{
public:
    ~A();
};

A::~A(){
    try{
        throw "exception";
    }catch(char* &e){
    }
    
}
int main()
{
    return 0;    
}