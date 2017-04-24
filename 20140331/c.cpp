#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int dp[N][2],out[N];
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

int ans[N],tot;

void dfs(int u)
{
    dp[u][0] = 0,dp[u][1] = 1;
    for(int i = head[u]; i != -1; i = e[i].next) {
        dfs(e[i].v);
        dp[u][0] += dp[e[i].v][0];
        dp[u][1] += dp[e[i].v][0];
    }
    int tmp = dp[u][0];
    out[u] = 0x7fffffff;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(tmp - dp[e[i].v][0] + dp[e[i].v][1] > dp[u][0]) {
            dp[u][0] = tmp - dp[e[i].v][0] + dp[e[i].v][1];
            out[u] = e[i].v;
        }
    }
}

void get_ans(int u,int flag)
{
    //cout << u << " " << flag << " " << dp[u][flag] << endl;
    if(flag) {
        ans[++ tot] = u;
        for(int i = head[u]; i != -1; i = e[i].next)
            get_ans(e[i].v,0);
    }
    else {
        for(int i = head[u]; i != -1; i = e[i].next)
            get_ans(e[i].v,e[i].v == out[u]);
    }
}

void solve()
{
    int n,x;
    cnt = 0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i = 2; i <= n; i ++) {
        scanf("%d",&x);
        addedge(x,i);
    }
    dfs(1);
    cout << dp[1][0] * 1000 << endl;
    tot = 0;
    get_ans(1,0);
    sort(ans + 1,ans + tot + 1);
    for(int i = 1; i <= tot; i ++) {
        printf("%d",ans[i]);
        if(i == tot) puts("");
        else printf(" ");
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
        if(t) puts("");
    }
    return 0;
}

