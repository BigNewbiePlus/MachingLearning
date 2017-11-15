#include<cstring>
typedef struct person{
    int age;
}Person;

int main()
{  
    Person peter;
    memset(&peter, sizeof(peter), 0);
    memset(&peter, 0, sizeof(peter));
    return 0;
}
