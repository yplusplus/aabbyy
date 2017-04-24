#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int E = 100010;
const int oo = 0x7ffffff;
const int N = 110;

struct edge
{
	int next,v,cost;
}e[E];

int head[N],cnt;
queue<int> q;

void addedge(int u,int v,int cost)
{
	e[cnt].v = v;
	e[cnt].cost = cost;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int dp[N][N][N];

int val(int x,int y)
{
    if(x == y) return oo;
    return x;
}

void solve()
{
    int n,m,x,y,z;
    scanf("%d%d",&n,&m);
    int st[3],ed[3];
    for(int i = 0; i < 3; i ++)
        scanf("%d",&st[i]);
    for(int i = 0; i < 3; i ++)
        scanf("%d",&ed[i]);
    for(int i = 0; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            for(int k = 0; k <= n; k ++)
                dp[i][j][k] = -oo;
    cnt = 0;
    memset(head,-1,sizeof(head));
    while(m --) {
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);
    }
    dp[st[0]][st[1]][st[2]] = 0;
    for(int i = st[0]; i <= ed[0]; i ++) {
        for(int j = st[1]; j <= ed[1]; j ++) {
            for(int k = st[2]; k <= ed[2]; k ++) {
                if(dp[i][j][k] < 0) continue;
                if(i == j || i == k || j == k) continue;
                int mid = min(val(i,ed[0]),min(val(j,ed[1]),val(k,ed[2])));
                if(mid == i) {
                    for(int r = head[i]; r != -1; r = e[r].next) {
                        int v = e[r].v;
                        if(v == j || v == k || v > ed[0] || v == st[1] || v == ed[1] || v == st[2] || v == ed[2]) continue;
                        dp[v][j][k] = max(dp[v][j][k],dp[i][j][k] + e[r].cost);
                    }
                }
                if(mid == j) {
                    for(int r = head[j]; r != -1; r = e[r].next) {
                        int v = e[r].v;
                        if(v == i || v == k || v > ed[1] || v == st[0] || v == ed[0] || v == st[2] || v == ed[2]) continue;
                        dp[i][v][k] = max(dp[i][v][k],dp[i][j][k] + e[r].cost);
                    }
                }
                if(mid == k) {
                    for(int r = head[k]; r != -1; r = e[r].next) {
                        int v = e[r].v;
                        if(v == i || v == j || v > ed[2] || v == st[0] || v == ed[0] || v == st[1] || v == ed[1]) continue;
                        dp[i][j][v] = max(dp[i][j][v],dp[i][j][k] + e[r].cost);
                    }
                }
            }
        }
    }
    if(dp[ed[0]][ed[1]][ed[2]] < 0) dp[ed[0]][ed[1]][ed[2]] = 0;
    printf("%d\n",dp[ed[0]][ed[1]][ed[2]]);
}
    
int main()
{
    int Case;
    scanf("%d",&Case);
    while(Case --) {
	    solve();
    }
	return 0;
}


