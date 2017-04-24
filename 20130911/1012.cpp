#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
long long a[N];

int solve(int n)
{
    int pos = -1;
    /*
    for(int i = 1; i <= n; i ++)
        cout << a[i] << " ";
    cout << endl;*/
    for(int i = 2; i <= n; i ++) {
        if(a[i] != a[i - 1] + 1) {
            pos = i;
            break;
        }
    }
    //cout << pos << endl;
    if(pos == -1) return 1;
    return pos;
}
    
int main()
{
    int t,n;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++)
            scanf("%I64d",&a[i]);
        printf("Case #%d: %d\n",cas,solve(n));
    }
    return 0;
}
    

