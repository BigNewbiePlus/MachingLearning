#define MONKEY 0x0012
int main()
{
    int b;
    if(b&MONKEY || MONKEY|b){}
    int c=MONKEY|b;
    return 0;
}
