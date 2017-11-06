
void foo2(int* a){
    sizeof(a);
}
void foo(int a[10]){
    sizeof(a);
}
int main()
{
    int a[10];
    int b[100];
    sizeof(a);
    foo(b);
    
    return 0;    
}
