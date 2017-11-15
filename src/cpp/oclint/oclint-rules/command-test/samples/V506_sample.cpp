int main()
{
    int *a;
    {
        int b,*c;
        a=&b;
        a=c;
    }
        
    return 0;
    
}