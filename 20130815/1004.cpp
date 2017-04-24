#pragma comment(linker, "/STACK:10006777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
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

struct point
{
    int x,y,z;
    point() {}
    point(int x,int y,int z):x(x),y(y),z(z) {}
}a[N];

int pre[N],dp[N][3],fa[N];

void dfs1(int u,int fa)
{
    dp[u][2] = dp[u][1] = dp[u][0] = 0;
    pre[u] = fa;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(e[i].v == fa) continue;
        dfs1(e[i].v,u);
        if(dp[e[i].v][0] + 1 > dp[u][0]) {
            dp[u][2] = dp[u][1];
            dp[u][1] = dp[u][0];
            dp[u][0] = dp[e[i].v][0] + 1;
        }
        else if(dp[u][1] < dp[e[i].v][0] + 1) {
            dp[u][2] = dp[u][1];
            dp[u][1] = dp[e[i].v][0] + 1;
        }
        else dp[u][2] = max(dp[u][2],dp[e[i].v][0] + 1);
    }
}

void dfs2(int u,int pre)
{
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(e[i].v == pre) continue;
        fa[e[i].v] = fa[u] + 1;
        if(dp[e[i].v][0] + 1 == dp[u][0])
            fa[e[i].v] = max(fa[e[i].v],dp[u][1] + 1);
        else fa[e[i].v] = max(fa[e[i].v],dp[u][0] + 1);
        dfs2(e[i].v,u);
    }
}

int main()
{
    int t,n,x,y,z;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d",&n);
        cnt = 0;
        memset(head,-1,sizeof(head));
        for(int i = 1; i < n; i ++) {
            scanf("%d%d%d",&x,&y,&z);
            addedge(x,y);
            addedge(y,x);
            a[i] = point(x,y,z);
        }
        dfs1(1,0);
        fa[0] = fa[1] = 0;
        dfs2(1,0);
        int ans = 0x7fffffff,id = -1;
        for(int i = 1; i < n; i ++) {
            int x = a[i].x,y = a[i].y;
            if(pre[y] == x) {
                int ma2,ma1 = dp[y][0] + dp[y][1];
                if(dp[x][0] == dp[y][0] + 1) {
                    ma2 = max(fa[x],dp[x][2]) + dp[x][1];
                }
                else if(dp[x][1] == dp[y][0] + 1) {
                    ma2 = max(fa[x],dp[x][2]) + dp[x][0];
                }
                else ma2 = max(fa[x],dp[x][1]) + dp[x][0];
                if(a[i].z * max(ma1,ma2) < ans) {
                    ans = min(ans,a[i].z * max(ma1,ma2));
                    id = i;
                }
            }
            else {
                swap(x,y);
                 int ma2,ma1 = dp[y][0] + dp[y][1];
                if(dp[x][0] == dp[y][0] + 1) {
                    ma2 = max(fa[x],dp[x][2]) + dp[x][1];
                }
                else if(dp[x][1] == dp[y][0] + 1) {
                    ma2 = max(fa[x],dp[x][2]) + dp[x][0];
                }
                else ma2 = max(fa[x],dp[x][1]) + dp[x][0];
                if(a[i].z * max(ma1,ma2) < ans) {
                    ans = min(ans,a[i].z * max(ma1,ma2));
                    id = i;
                }
            }
        }
        printf("Case #%d: %d",cas,id);
        cout << endl;
    }
    return 0;
}

