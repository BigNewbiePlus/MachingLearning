#include<string>
using namespace std;
int main()
{
    string a;
    if(a.size()){
        a+="(";
        a+",";
    }
    a+="(";
    a+"("+a+")";
    return 0;
}
