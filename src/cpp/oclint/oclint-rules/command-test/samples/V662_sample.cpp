#include<vector>
using namespace std;

int main()
{
    vector<int> a,b;
    for(vector<int>::iterator it = a.begin(); it!=b.end(); it++){}
    vector<int>::iterator it = a.begin();
    for(it = a.begin(); it!=b.end(); it++){}
    return 0;
}
