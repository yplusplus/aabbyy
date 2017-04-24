#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
long long sum[N];
int f[100010];

int main()
{
    int n,m,x;
    while(scanf("%d%d",&n,&m) != EOF) {
        sum[0] = 0;
        for(int i = 0; i <= m; i ++)
            f[i] = -1;
        f[0] = 0;
        int ans = 0;
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&x);
            sum[i] = (sum[i - 1] + x) % m;
            if(sum[i] < 0) sum[i] += m;
            if(f[sum[i]] == -1) f[sum[i]] = i;
            else ans = max(ans,i - f[sum[i]]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

