#include <bits/stdc++.h>
using namespace std;

vector<int> v[25];
char s[25][25];
int visit[25];
int dp[1 << 8];

int cal(int state,int n)
{
    int vv[n + 1];
    int map[2 * n];
    int ct = 0;
    for(int i = 0; i < 2 * n; i ++)
        if(state & (1 << i)) {
            map[i] = ct ++;
        }
        else map[i] = -1;
    memset(vv,0,sizeof(vv));
    for(int i = 0; i < 2 * n; i ++)
        if(map[i] == -1) continue;
        else {
            for(int j = 0; j < v[i].size(); j ++)
                vv[map[v[i][j]]] ^= (1 << map[i]);
        }
    for(int i = 0; i < (1 << n); i ++) dp[i] = 0;
    dp[0] = 1;
    for(int i = 0; i < (1 << n); i ++) {
        if(!dp[i]) continue;
        for(int j = 0; j < n; j ++) {
            if(i & (1 << j)) continue;
            if((vv[j] & i) != vv[j]) continue;
            dp[i ^ (1 << j)] += dp[i];
        }
    }
    return dp[(1 << n) - 1];
}

void solve()
{
    long long ans = 0;
    int n;
    scanf("%d",&n);
    for(int i = 0; i < 2 * n; i ++) {
        scanf("%s",s[i]);
        v[i].clear();
    }
    for(int i = 0; i < 2 * n; i ++)
        for(int j = 0; j < 2 * n; j ++)
            if(s[i][j] == 'Y') v[j].push_back(i);
    
    for(int i = 0; i < (1 << (2 * n)); i ++) {
        int tot = 0;
        for(int j = 0; j < 2 * n; j ++)
            if(i & (1 << j)) tot ++;
        if(tot != n) continue;
        memset(visit,0,sizeof(visit));
        for(int j = 0; j < 2 * n; j ++)
            if(i & (1 << j)) visit[j] = 1;
        bool flag = true;
        for(int j = 0; j < 2 * n && flag; j ++)
            for(int k = 0; k < 2 * n && flag; k ++)
                if(s[j][k] == 'Y' && ((visit[j] + visit[k]) & 1)) flag = false;
        if(!flag) continue;
        ans += (long long)cal(i,n) * cal(((1 << (2 * n)) - 1) ^ i,n);
        //cout << i << " " << (((1 << n) - 1) ^ i) << endl;
    }
    cout << ans << endl;
}
        
int main()
{
    int t;
    scanf("%d",&t);
    while(t --) solve();
    return 0;
}

