void foo()
{
    int a,b,c,d;
    bool flag;
    if(flag){
        a=b+c*d+a;
    }else
    {
       a=b+c*d+a; 
    }
}

void foo2()
{
    int a,b,c,d;
    bool flag;
    if(flag){
        a=b+c*d+a;
    }else if(!flag)
    {
       a=b+c; 
    }else
    a = b+c*d+a;
}

int main()
{
    return 0;
}
