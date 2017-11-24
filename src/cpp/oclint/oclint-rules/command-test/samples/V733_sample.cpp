
#define MUL(a) a*10

int main()
{
    int chan;
    int off = MUL(chan);
    off = MUL(chan - 1); // <=
    return 0;
}
