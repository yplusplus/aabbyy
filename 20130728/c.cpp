#pragma comment(linker,"/STACK:102400000,102400000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

const int N = 100010;
const int E = 500010;

struct edge
{
    int v,next;
}e[E * 4];

int head[N],cnt;

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

int low[N],dfn[N],bel[N],size[N],c1,c;
stack<int> sta;
void init()
{
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(bel,0,sizeof(bel));
    memset(size,0,sizeof(size));
    memset(head,-1,sizeof(head));
    c = c1 = cnt = 0;
}

void tarjan(int u,int pre)
{
    low[u] = dfn[u] = ++ c1;
    sta.push(u);
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(!dfn[e[i].v]) {
            tarjan(e[i].v,u);
            if(low[e[i].v] < low[u]) low[u] = low[e[i].v];
        }
        else if(e[i].v != pre && dfn[e[i].v] < low[u]) low[u] = dfn[e[i].v];
    }
    if(low[u] == dfn[u]) {
        ++ c;
        int v;
        do {
            v = sta.top();
            sta.pop();
            size[c] ++;
            bel[v] = c;
        }while(u != v);
    }
}

vector<int> ve[N * 10],v[N * 2];
int map[N * 2];

int dfs(int u,int pre)
{
    int ans = 0;
    for(int i = 0; i < v[u].size(); i ++) {
        if(v[u][i] == pre) continue;
        int x = dfs(v[u][i],u);
        ans ^= (x + 1);
    }
    return ans;
}

int S[N];
int main()
{
    int n,m,r,x,y;
    scanf("%d%d%d",&n,&m,&r);
    memset(S,0,sizeof(S));
    init();
    for(int i = 1; i <= m; i ++) {
        scanf("%d",&x);
        for(int j = 1; j <= x; j ++) {
            scanf("%d",&y);
            ve[i].push_back(y);
        }
        for(int j = 1; j < ve[i].size(); j ++) {
            addedge(ve[i][j - 1],ve[i][j]);
            addedge(ve[i][j],ve[i][j - 1]);
        }
    }
    for(int i = 1; i <= n; i ++)
        if(!dfn[i]) tarjan(i,0);
    int tot = c;
    for(int i = 1; i <= n; i ++)
        for(int j = head[i];j != -1; j = e[j].next)
            if(bel[i] == bel[e[j].v]) {
                S[bel[i]] ++;
            }
    for(int i = 1; i <= c; i ++) S[i] /= 2;
    for(int i = 1; i <= c; i ++) {
        if(size[i] > 1 && (S[i] & 1)) {
            map[i] = ++ tot;
            v[i].push_back(tot);
            v[tot].push_back(i);
        }
        else map[i] = i;
    }
    for(int i = 1; i <= n; i ++)
        for(int j = head[i]; j != -1; j = e[j].next)
            if(bel[i] == bel[e[j].v]) continue;
            else {
                v[map[bel[i]]].push_back(map[bel[e[j].v]]);
            }
    int ans = dfs(map[bel[r]],-1);
    if(ans) printf("First\n");
    else printf("Second\n");
    return 0;
}



