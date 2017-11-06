void Foo(){}

void foo()
{
    bool X,Y;
    int z;
    if (X)
        if (Y) Foo();
    else
        z = 1;
}

void foo3(){
     bool X,Y;
    int z;   
    if (X)
        if (Y)
            Foo();
        else
            z = 1;
}
int main()
{   
    return 0;
}
