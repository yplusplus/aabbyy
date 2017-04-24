#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
struct edge
{
    int v,next;
}e[N];

int head[N / 2],cnt;

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

queue<int> q;
int dis[N / 2];
bool f[2][N / 2];
int bfs(int n)
{
    while(!q.empty()) q.pop();
    for(int i = 1; i <= n; i ++) dis[i] = -1;
    q.push(1);
    dis[1] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i != -1; i = e[i].next) {
            if(dis[e[i].v] == -1) {
                dis[e[i].v] = dis[u] + 1;
                q.push(e[i].v);
            }
        }
    }
    return dis[n];
}

int bfs2(int n)
{
    while(!q.empty()) q.pop();
    for(int i = 1; i <= n; i ++) dis[i] = -1;
    q.push(1);
    dis[1] = 0;
    int visit[1510];
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 1; i <= n; i ++) visit[i] = 0;
        for(int i = head[u]; i != -1; i = e[i].next) visit[e[i].v] = 1;
        for(int i = 1; i <= n; i ++) {
            if(!visit[i] && dis[i] == -1) {
                dis[i] = dis[u] + 1;
                q.push(i);
            }
        }
    }
    return dis[n];
}

int visit[N / 2];
void bfs3(int n,int a,int b)
{
    memset(visit,0,sizeof(visit));
    while(!q.empty()) {
        q.pop();
    }
    for(int i = 1; i <= n; i ++) dis[i] = -1;
    dis[1] = 0;
    q.push(1);
    int ans = a;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(dis[u] * b >= a) break;
        for(int i = 1; i <= n; i ++) visit[i] = 0;
        for(int i = head[u]; i != -1; i = e[i].next) {
            visit[e[i].v] = 1;
        }
        for(int i = 1; i <= n; i ++)
            if(!visit[i] && dis[i] == -1) {
                dis[i] = dis[u] + 1;
                q.push(i);
            }
        if(dis[n] != -1) {
            ans = min(ans,dis[n] * b);
            break;
        }
    }
    cout << ans << endl;
}
        
            
    
int ansx[N / 2],ansy[N / 2];
int main()
{
    int n,m,a,b,x,y;
    while(scanf("%d%d%d%d",&n,&m,&a,&b) != EOF) {
        cnt = 0;
        memset(head,-1,sizeof(head));
        memset(f,false,sizeof(f));
        bool flag = true;
        for(int i = 1; i <= m; i ++) {
            scanf("%d%d",&x,&y);
            addedge(x,y);
            addedge(y,x);
            if(x > y) swap(x,y);
            if(x == 1 && y == n) flag = false;
            else if(x == 1) f[0][y] = true;
            else if(y == n) f[1][x] = true;
        }
        if(flag) {
            int ans = bfs(n);
            if(ans == -1) cout << b << endl;
            else cout << min(1LL * b,1LL * ans * a) << endl;
            continue;
        }
        if(n <= 2500) {
            int ans = bfs2(n);
            if(ans == -1) cout << a << endl;
            else cout << min(1LL * a,1LL * ans * b) << endl;
            continue;
        }
        int ans = a;
        flag = true;
        int cc = 0,cx = 0,cy = 0;
        for(int i = 2; i < n; i ++)
            if(!f[0][i] && !f[1][i]) ans = min(ans,b * 2), flag = false;
            else if(!f[0][i]) cc |= 1,ansx[cx ++] = i;
            else if(!f[1][i]) cc |= 2,ansy[cy ++] = i;
        if(!flag || cc != 3) {
            cout << ans << endl;
            continue;
        }
        bfs3(n,a,b);
        /*
        if(1LL * cx * cy > m) {
            cout << min(a,3 * b) << endl;
            continue;
        }
        int tot = 0;
        for(int i = 0; i < cx; i ++) {
            int u = ansx[i];
            for(int j = head[u]; j != -1; j = e[j].next)
                if(e[j].v != 1 && e[j].v != n && !f[1][e[j].v]) tot ++;
        }
        if(tot > m) {
            cout << min(a,3 * b) << endl;
            continue;
        }
        */
    }
    return 0;
}



