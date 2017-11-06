#include<cstddef>
void foo()
{
    int nBytes = 10;
    char* pBytes = new char[ nBytes ];
    if ( nBytes > 3 &&
       pBytes[0] == 0xEF &&
       pBytes[1] == 0xBB &&
       pBytes[2] == 0xBF )
    {
    }
}

void foo2(){
    size_t nNumChars;
    if (nNumChars > 0){
    }
}

void foo3()
{
    typedef unsigned short wint_t;
    wint_t c;
    if (c < 0){
        
    }
}

void foo4()
{
    char* s;
    if (*s > 127) *s = '~';
}
int main()
{
    
    return 0;
}
