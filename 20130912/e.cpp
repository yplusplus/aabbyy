#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1000010;
struct edge
{
    int v,next;
}e[N * 2];

int fa[N],dp[N][2],visit[N];
int head[N],cnt;
int E,W,n;

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

void dfs(int u,int pre)
{
    fa[u] = pre;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(e[i].v == pre) continue;
        dfs(e[i].v,u);
        dp[u][0] += dp[e[i].v][0];
        dp[u][1] += dp[e[i].v][1];
    }
    if(u <= E) dp[u][0] ++;
    if(u >= n - W + 1) dp[u][1] ++;
}

int a[N],b[N];
bool vis[N];
struct point
{
    int x,step;
    point() {}
    point(int x,int step):x(x),step(step) {}
};
queue<point> q;
void bfs1(int u,int pre)
{
    int ct = 0;
    while(!q.empty()) q.pop();
    for(int i = 0; i <= n; i ++) vis[i] = false;
    vis[u] = vis[pre] = true;
    q.push(point(u,0));
    while(!q.empty()) {
        point u = q.front();
        q.pop();
        if(visit[u.x]) a[++ ct] = u.step;
        for(int i = head[u.x]; i != -1; i = e[i].next) {
            if(vis[e[i].v]) continue;
            vis[e[i].v] = true;
            q.push(point(e[i].v,u.step + 1));
        }
    }
}

void bfs2(int u,int pre)
{
    int ct = 0;
    while(!q.empty()) q.pop();
    for(int i = 0; i <= n; i ++) vis[i] = false;
    vis[u] = vis[pre] = true;
    q.push(point(u,0));
    while(!q.empty()) {
        point u = q.front();
        q.pop();
        if(u.x >= n - W + 1) b[++ ct] = u.step;
        for(int i = head[u.x]; i != -1; i = e[i].next) {
            if(vis[e[i].v]) continue;
            vis[e[i].v] = true;
            q.push(point(e[i].v,u.step + 1));
        }
    }
}

int main()
{
     int SIZE=1<<27;
     char *p=(char*)malloc(SIZE)+SIZE;
        __asm__("movl %0, %%esp\n" :: "r"(p));
     int m,x,y;
     while(scanf("%d%d%d%d",&n,&m,&E,&W) != EOF) {
         for(int i = 0; i <= n; i ++) {
             dp[i][0] = dp[i][1] = visit[i] = 0;
             head[i] = -1;
         }
         cnt = 0;
         for(int i = 1; i <= m; i ++) {
             scanf("%d%d",&x,&y);
             addedge(x,y);
             addedge(y,x);
         }
         scanf("%d",&m);
         for(int i = 1; i <= m; i ++) {
             scanf("%d",&y);
             visit[y] = 1;
         }
         dfs(1,0);
         int rootx,rooty;
         for(int i = 1; i <= n; i ++)
             if(dp[i][1] == W && dp[i][0] == 0) {
                 rootx = i;
                 rooty = fa[i];
                 break;
             }
         bfs1(rootx,rooty);
         bfs2(rootx,rooty);
         int ans = 0;
         int pret = -1;
         //cout << a[1] << " " << b[1] << endl;
         for(int i = 1; i <= m; i ++) {
             pret = max(pret + 1,a[i]);
             ans = max(ans,pret + b[m - i + 1] + 1);
         }
         printf("%d\n",ans);
     }
     return 0;
}

