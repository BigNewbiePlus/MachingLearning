#include<stdio.h>
#include<stdlib.h>
    
#define CS_ALLOC_STACK_ARRAY(type, var, size) \
  type *var = (type *)alloca ((size) * sizeof (type))

struct csVector3{
};

int main()
{
    int a;
    for(int i=0;i<10;i++)
        CS_ALLOC_STACK_ARRAY(csVector3,
      tmpVertices, 10);
    
    for(int i=0;i<10;i++){
        CS_ALLOC_STACK_ARRAY(csVector3,
      tmpVertices, 10);
    }
        
    
    while(a<10){
       CS_ALLOC_STACK_ARRAY(csVector3,
      tmpVertices, 10); 
    }
    
    do{
        struct csVector3* csvector3;
        csvector3 = (csVector3 *)alloca(10);
    }while(a<10);
        
    return 0;
    
}