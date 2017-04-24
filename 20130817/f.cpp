#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct edge
{
    int v,dis,next;
}e[1000010];

int head[110],cnt;

void addedge(int u,int v,int dis)
{
    e[cnt].v = v;
    e[cnt].dis = dis;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

int dis[110],visit[110],c[110];

bool spfa(int n)
{
    memset(visit,0,sizeof(visit));
    fill(dis + 1,dis + n + 1,1000000000);
    dis[1] = 0;
    memset(c,0,sizeof(c));
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        visit[u] = 0;
        for(int i = head[u]; i != -1; i = e[i].next)
            if(dis[e[i].v] > dis[u] + e[i].dis) {
                dis[e[i].v] = dis[u] + e[i].dis;
                if(!visit[e[i].v]) {
                    visit[e[i].v] = 1;
                    c[e[i].v] ++;
                    q.push(e[i].v);
                    if(c[e[i].v] > n + 5) return true;
                }
            }
    }
    return false;
}

int main()
{
    int n,m,x,y,z;
    ios::sync_with_stdio(0);
    while(cin >> n >> m) {
        if(!n && !m) break;
        cnt = 0;
        memset(head,-1,sizeof(head));
        while(m --) {
            cin >> x >> y >> z;
            addedge(x,y,z);
            addedge(y,x,-z);
        }
        if(spfa(n)) cout << "Y" << endl;
        else cout << "N" << endl;
    }
    return 0;
}


