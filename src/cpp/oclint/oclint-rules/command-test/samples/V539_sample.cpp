#include<vector>
using namespace std;
void test(vector<int>::iterator it){}
void foo(){vector<int> a;test(a.begin()+1);}
int main()
{
    vector<int> a;
    a.erase(a.end()+5);
    return 0;
}
