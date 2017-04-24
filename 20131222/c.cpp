#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1010;
const int mod = 10086;
struct edge
{
    int v,next;
}e[N * 2];

int head[N],cnt;

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

int dp[N][2],f[N][N],fa[N],fat[N],maxn;

void dfs1(int u,int pre)
{
    fat[u] = pre;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(pre == e[i].v) continue;
        dfs1(e[i].v,u);
        if(dp[e[i].v][0] + 1 > dp[u][0]) {
            dp[u][1] = dp[u][0];
            dp[u][0] = dp[e[i].v][0] + 1;
        }
        else if(dp[e[i].v][0] + 1 > dp[u][1])
            dp[u][1] = dp[e[i].v][0] + 1;
    }
}

void dfs2(int u,int pre)
{
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(e[i].v == pre) continue;
        fa[e[i].v] = fa[u] + 1;
        if(dp[e[i].v][0] + 1 != dp[u][0]) fa[e[i].v] = max(fa[e[i].v],dp[u][0] + 1);
        else fa[e[i].v] = max(fa[e[i].v],dp[u][1] + 1);
        dfs2(e[i].v,u);
    }
}

void dfs(int u,int pre)
{
    for(int i = 0; i <= maxn; i ++) f[u][i] = 1;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(e[i].v == pre) continue;
        dfs(e[i].v,u);
        for(int j = 1; j <= maxn; j ++)
            f[u][j] = f[u][j] * (1 + f[e[i].v][j - 1]) % mod;
    }
}
        
int pl[N],pr[N];
void solve()
{
    int n,x,y;
    scanf("%d",&n);
    memset(head,-1,sizeof(head));
    cnt = 0;
    for(int i = 1; i < n; i ++) {
        scanf("%d%d",&x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    if(n <= 2) {
        cout << 1 << endl;
        return;
    }
    memset(dp,0,sizeof(dp));
    memset(fa,0,sizeof(fa));
    dfs1(1,0);
    dfs2(1,0);
    maxn = 0x7fffffff;
    int id1 = -1,id2 = -1;
    for(int i = 1; i <= n; i ++)
        if(max(dp[i][0],fa[i]) < maxn) {
            maxn = max(dp[i][0],fa[i]);
            id1 = i;
            id2 = -1;
        }
        else if(max(dp[i][0],fa[i]) == maxn) {
            id2 = id1;
            id1 = i;
        }
    int ans = 0;
    //cout << id1 << " " << id2 << endl;
    if(id2 != -1) {
        maxn --;
        dfs(id1,id2);
        dfs(id2,id1);
        for(int i = maxn - 1; i >= 0; i --) {
            f[id1][i + 1] -= f[id1][i];
            f[id2][i + 1] -= f[id2][i];
            if(f[id1][i + 1] < 0) f[id1][i + 1] += mod;
            if(f[id2][i + 1] < 0) f[id2][i + 1] += mod;
        }
        for(int i = 0; i <= maxn; i ++)
            ans = (ans + f[id1][i] * f[id2][i]) % mod;
        cout << ans << endl;
    }
    else {
        for(int i = head[id1]; i != -1; i = e[i].next)
            dfs(e[i].v,id1);
        ans = 1;
        int a[N],c = 0;
        for(int i = head[id1]; i != -1; i = e[i].next)
            a[++ c] = e[i].v;
        for(int i = 0; i < maxn; i ++) {
            pl[0] = pr[c + 1] = 1;
            int tmp = 1;
            for(int j = 1; j <= c; j ++) {
                tmp = tmp * (1 + f[a[j]][i]) % mod;
            }
            if(i) {
                for(int j = 1; j <= c; j ++) 
                    pl[j] = pl[j - 1] * (1 + f[a[j]][i - 1]) % mod;
                for(int j = c; j >= 1; j --) {
                    pr[j] = pr[j + 1] * (1 + f[a[j]][i - 1]) % mod;
                }
            }
            else {
                for(int j = 0; j <= c + 1; j ++) pl[j] = pr[j] = 1;
            }
            int tt = 1;
            if(i) {
                for(int j = 1; j <= c; j ++) {
                    tt = tt * (1 + f[a[j]][i - 1]) % mod;
                }
            }
            tmp -= tt;
                
            for(int j = 1; j <= c; j ++) {
                tmp = (tmp - pl[j - 1] * pr[j + 1] % mod * (f[a[j]][i] - f[a[j]][i - 1])) % mod;
            }
                        
            ans = (ans + tmp) % mod;
            if(ans < 0) ans += mod;
        }
        cout << ans << endl;
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case %d: ",cas);
        solve();
    }
    return 0;
}
/*
7
1 2
2 3
2 4
4 5
5 6
5 7
*/

