struct A{
    char* tag;
};
void foo()
{
    struct A a;
    char* tag;
    tag = '\0';
    a.tag='\0';
}
int main()
{
    return 0;
}
