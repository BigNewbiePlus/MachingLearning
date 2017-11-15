typedef unsigned char uint8_t;

struct A{
    uint8_t nf; 
};
int main()
{   
    struct A my;
    struct A you;
    my.nf = my.nf;
    my.nf = you.nf;
    int* a;
    a=a;
    return 0;
}
