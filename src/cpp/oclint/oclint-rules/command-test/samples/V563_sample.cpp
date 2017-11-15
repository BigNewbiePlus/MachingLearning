void Foo(){}

void false_1()
{
    bool X,Y;
    int z;
    if (X)
        if (Y) Foo();
    else
        z = 1;
}

void true_1(){
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
