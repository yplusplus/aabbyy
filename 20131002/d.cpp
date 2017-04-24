#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
 
const int E = 50010;
const int oo = 0x7fffffff;
const int N = 1010;
 
struct edge
{
    int next,v,flow,cost;
}e[E];
 
int head[N],cnt;
queue<int> q;
 
void addedge(int u,int v,int flow,int cost)
{
    e[cnt].v = v;
    e[cnt].flow = flow;
    e[cnt].cost = cost;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}
 
void addEdge(int u,int v,int flow,int cost)
{
    addedge(u,v,flow,cost);
    addedge(v,u,0, -cost);
}
 
int S,T;
struct point
{
    int x,y;
    point() {}
    point(int x,int y):x(x),y(y) {}
};
 
vector<point> v[N];
int gl[N];
int dist[2][N];
 
void spfa(int n,int st,int id)
{
    while(!q.empty()) q.pop();
    int visit[N];
    memset(visit,0,sizeof(visit));
    q.push(st);
    for(int i = 1; i <= n; i ++) dist[id][i] = oo;
    dist[id][st] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        visit[u] = 0;
        for(int i = 0; i < v[u].size(); i ++) {
            if(dist[id][v[u][i].x] > dist[id][u] + v[u][i].y) {
                dist[id][v[u][i].x] = dist[id][u] + v[u][i].y;
                if(!visit[v[u][i].x]) {
                    q.push(v[u][i].x);
                    visit[v[u][i].x] = 1;
                }
            }
        }
    }
}
 
bool flag;
void init(int n,int m)
{
    int x,y,z;
    memset(head,-1,sizeof(head));
    cnt = 0;
    for(int i = 0; i <= n; i ++) v[i].clear();
    for(int i = 1; i <= n; i ++) scanf("%d",&gl[i]);
    while(m --) {
        scanf("%d%d%d",&x,&y,&z);
        v[x].push_back(point(y,z));
        v[y].push_back(point(x,z));
    }
    flag = false;
    spfa(n,1,0);
    spfa(n,n,1);
    if(dist[1][1] ==  oo) {
        printf("-1\n");
        flag = true;
        return;
    }
    S = 0,T = n + 1;
    for(int i = 1; i <= n; i ++)
        for(int j = 0; j < v[i].size(); j ++)
            if(dist[0][i] + dist[1][v[i][j].x] + v[i][j].y == dist[0][n])
                addEdge(i,v[i][j].x,1,gl[v[i][j].x]);
    addEdge(S,1,1,gl[1]);
    addEdge(n,T,1,0);
}
 
int dis[N],cc[N],visit[N],pre[N],dd[N];
 
int spfa()
{
    fill(dis,dis + T + 1, -oo);
    dis[S] = 0;
    pre[S] = -1;
    q.push(S);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        visit[u] = 0;
        for(int i = head[u]; i != -1; i = e[i].next) {
            if(e[i].flow > 0 && dis[e[i].v] < dis[u] + e[i].cost) {
                dis[e[i].v] = dis[u] + e[i].cost;
                pre[e[i].v] = u;
                cc[e[i].v] = i;
                dd[e[i].v] = e[i].cost;
                if(!visit[e[i].v]) {
                    q.push(e[i].v);
                    visit[e[i].v] = 1;
                }
            }
        }
    }
    return dis[T] > 0;
}
 
int argument()
{
    int aug = oo;
    int u,v;
    int ans = 0;
    for(u = pre[v = T]; v != S; v = u, u = pre[v])
        if(e[cc[v]].flow < aug) aug = e[cc[v]].flow;
    for(u = pre[v = T]; v != S; v = u, u = pre[v]) {
        e[cc[v]].flow -= aug;
        e[cc[v] ^ 1].flow += aug;
        if(e[cc[v] ^ 1].flow < 0) printf("fuck\n");
        ans += dd[v] * aug;
    }
    return ans;
}
 
void mcmf() 
{
    int ans = 0;
    memset(visit,0,sizeof(visit));
    while(spfa()) ans += argument();
    printf("%d\n",ans);
}
 
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF) {
        init(n,m);
        if(!flag) mcmf();
    }
    return 0;
}

