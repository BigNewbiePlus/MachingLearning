#include<stdio.h>
int main()
{
    FILE *fp = NULL;
    fp=fopen("c:\\myfile\\file.data", "r");
    fclose(fp);
    return 0;
}
