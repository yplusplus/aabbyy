#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

const int N = 5010;
struct edge
{
    int v,next;
}e[N * 20];

int cnt,head[N];

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

stack<int> sta;
int low[N],dfn[N],instack[N],bel[N];
int cc,ct;

void tarjan(int u)
{
    low[u] = dfn[u] = ++ ct;
    sta.push(u);
    instack[u] = 1;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(!dfn[e[i].v]) {
            tarjan(e[i].v);
            if(low[e[i].v] < low[u]) low[u] = low[e[i].v];
        }
        else if(instack[e[i].v] && dfn[e[i].v] < low[u]) low[u] = dfn[e[i].v];
    }
    if(low[u] == dfn[u]) {
        cc ++;
        int v;
        do {
            v = sta.top();
            sta.pop();
            instack[v] = 0;
            bel[v] = cc;
        }while(u != v);
    }
}

vector<int> v[N];
int vis[N],pre[N];

int find(int x)
{
    for(int i = 0; i < v[x].size(); i ++) {
        if(!vis[v[x][i]]) {
            vis[v[x][i]] = 1;
            int tmp = pre[v[x][i]];
            pre[v[x][i]] = x;
            if(tmp == -1 || find(tmp)) return 1;
            pre[v[x][i]] = tmp;
        }
    }
    return 0;
}

int main()
{
    int t,n,m,x,y;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        cnt = 0;
        while(m --) {
            scanf("%d%d",&x,&y);
            addedge(x,y);
        }
        memset(low,0,sizeof(low));
        memset(instack,0,sizeof(instack));
        memset(dfn,0,sizeof(dfn));
        cc = ct = 0;
        while(!sta.empty()) sta.pop();
        for(int i = 1; i <= n; i ++)
            if(!dfn[i]) tarjan(i);
        for(int i = 0; i < N; i ++) v[i].clear();
        for(int i = 1; i <= n; i ++)
            for(int j = head[i]; j != -1; j = e[j].next)
                if(bel[i] != bel[e[j].v]) {
                    v[bel[i]].push_back(bel[e[j].v]);
                }
        int ans = cc;
        memset(pre,-1,sizeof(pre));
        for(int i = 1; i <= cc; i ++) {
            memset(vis,0,sizeof(vis));
            ans -= find(i);
        }
        printf("%d\n",ans);
    }
    return 0;
}
