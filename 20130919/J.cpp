#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;

long long dp[50][1 << 15];
stack<int> sta[50];
long long a[55];
int visit[50][1 << 15];
int bit[1 << 15];

void solve(int times)
{
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i ++)
        scanf("%I64d",&a[i]);
    while(!sta[0].empty()) sta[0].pop();
    for(int i = 0; i < (1 << n); i ++) dp[0][i] = 0;
    dp[0][0] = 1;
    sta[0].push(0);
    int state = 0;
    for(int i = 0; i < n; i ++)
        if(!(a[i] & 1)) state ^= (1 << i);
    dp[0][state] += 1;
    if(state) sta[0].push(state);
    for(int i = 0; i < 45; i ++) {
        state = 0;
        for(int j = 0; j < n; j ++) {
            if(!(a[j] & (1LL << (i + 1)))) state ^= (1 << j);
        }
        while(!sta[i + 1].empty()) sta[i + 1].pop();
        while(!sta[i].empty()) {
            int u = sta[i].top();
            sta[i].pop();
            if(visit[i + 1][u] != times) {
                visit[i + 1][u] = times;
                sta[i + 1].push(u);
                dp[i + 1][u] = 0;
            }
            dp[i + 1][u] += dp[i][u];
            int uu = u;
            u |= state;
            if(visit[i + 1][u] != times) {
                visit[i + 1][u] = times;
                sta[i + 1].push(u);
                dp[i + 1][u] = 0;
            }
            dp[i + 1][u] += dp[i][uu];
        }
    }
    long long ans = 0;
    while(!sta[45].empty()) {
        int u = sta[45].top();
        sta[45].pop();
        if((n - bit[u]) & 1) ans += dp[45][u];
    }
    printf("%I64d\n",ans);
}
   
int main()
{
    memset(bit,0,sizeof(bit));
    for(int i = 0; i < (1 << 15); i ++)
        for(int j = 0; j < 15; j ++)
            if(i & (1 << j)) bit[i] ++;
    memset(visit,0,sizeof(visit));
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case #%d: ",cas);
        solve(cas);
    }
    return 0;
}


