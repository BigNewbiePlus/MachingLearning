#include<string.h>
void foo(){  
    char str[1024];
    if(strcmp(str,"hello") && (strcmp(str,"world")==0)){  
    }  
}

void foo2()
{ 
    char *s1;
    char *s2;
    if(memcmp(s1, s2, 3)){   
    }  
}
int main()
{
    return 0;
}
