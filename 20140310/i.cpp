#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const long long mod = 1000000007;
long long c[N][N],dp[N][N];

void init()
{
    for(int i = 0; i < N; i ++) {
        c[i][i] = c[i][0] = 1;
        for(int j = 1; j < i; j ++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
}
 
long long get_val(int n)
{
    for(int i = 0; i <= n; i ++)
        for(int j = 0; j <= n; j ++)
            dp[i][j] = 0;
    dp[0][0] = 1;
    for(int i = 1; i <= n; i ++) {
        for(int j = i; j <= n; j ++) {
            for(int k = i - 1; k <= j; k ++) {
                dp[i][j] += dp[i - 1][k] * c[n - k][j - k];
                if(dp[i][j] >= mod) dp[i][j] %= mod;
            }
        }
    }
    return dp[n][n];
}

int ind[N],cnt,visit[N];
vector<int> v[N];

void dfs(int u)
{
    visit[u] = 1;
    cnt ++;
    for(int i = 0; i < v[u].size(); i ++)
        if(!visit[v[u][i]]) dfs(v[u][i]);
}

void solve()
{
    int n,m,x,y;
    memset(ind,0,sizeof(ind));
    for(int i = 0; i < N; i ++) v[i].clear();
    scanf("%d%d",&n,&m);
    while(m --) {
        scanf("%d%d",&x,&y);
        x ++,y ++;
        v[x].push_back(y);
        ind[y] ++;
    }
    memset(visit,0,sizeof(visit));
    int tot = n;
    long long ans = 1;
    for(int i = 1; i <= n; i ++)
        if(!ind[i]) {
            cnt = 0;
            dfs(i);
            ans = ans * get_val(cnt) % mod * c[tot][cnt] % mod;
            tot -= cnt;
        }
    for(int i = 1; i <= n; i ++)
        if(!visit[i]) {
            cnt = 0;
            dfs(i);
            ans = ans * c[tot][cnt] % mod;
            for(int i = 1; i <= cnt; i ++) ans = ans * cnt % mod;
            tot -= cnt;
        }
    cout << ans << endl;
}

int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
    }
    return 0;
}

