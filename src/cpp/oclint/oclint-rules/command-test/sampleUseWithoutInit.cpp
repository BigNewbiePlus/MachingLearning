void foo(int d){
    int e=d;
}

void foo2(int& a){
    a=1;
}

void foo3(int a){
    int b = a;
    a=1;
}
int main()
{
    int b;
    int c=b;
    b=0;
    c=b;
    int d;
    foo(d);
    int e=d;
    foo2(d);
    e=d;
    int f;
    foo3(f);
    int g=f;
    
    if((b=c)>(c+d)){
        b++, b+=1;
        d=1,b=2,c=3;
    }
    
    for(int i=0;i<10;i++, i+=1){
    
    }
    
    while(c<b){
    }
    
    do{
        
    }while(c<b);
    
    return 0;
}
