#include<iostream>
using namespace std;

typedef struct person{}Person;

class Animal{
    public:
    int size(){return sizeof(*this); return sizeof(this);return sizeof this;}
};
void foo()
{
    int A;
    size_t size = sizeof(A++); 
    
    char* buff;
    sizeof(buff - 1);
    
    Person* person;
    Animal* animal;
    
    sizeof(person);
    sizeof(animal);
    
    
    //正确
    size= sizeof(A);
    size_t result = sizeof(buff)-1;
    sizeof(*person);
    sizeof(*animal);
}
int main()
{   
    return 0;
}
