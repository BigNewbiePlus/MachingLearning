#include<stdio.h>
#include<stdlib.h>
struct Pointer{
    bool m_a;
    bool x(){return true;}
};
void m(){
    Pointer* pointer;
    
    if (pointer != 0 || pointer->m_a) {}
    if (pointer == 0 && pointer->x()) {} 
    if (!pointer && pointer->x()) {}
    
    int array[10]; 
    if (array == 0 && array[3]) { }
    int* DI;
    if(DI==0 && *DI){}
}

void m3(){
    int* DI;
    if (DI == 0) {
    printf("%d",*DI);
    }
    if (DI) {}
    else if(DI){}
    else
        printf("%d",*DI);
}

int main()
{
    return 0;
}
