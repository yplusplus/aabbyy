#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
struct edge
{
    int v,dis,next;
}e[N * 20];

int head[N],cnt;

void addedge(int u,int v,int dis)
{
    e[cnt].v = v;
    e[cnt].dis = dis;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

struct node
{
    int u,v;
    long long dis;
    node() {}
    node(int u,int v,long long dis):u(u),v(v),dis(dis) {}
    friend bool operator < (const node &p,const node &q) {
        if(p.dis != q.dis) return p.dis < q.dis;
        return p.u < q.u;
    }
}a[N * 20],c[N];
    
int pre[N];
int find(int x)
{
    if(pre[x] == -1) return x;
    return pre[x] = find(pre[x]);
}

void unions(int x,int y)
{
    x = find(x);
    y = find(y);
    if(x != y) pre[x] = y;
}

int val[N];
void solve()
{
    int n,m,x,y,z;
    scanf("%d%d",&n,&m);
    memset(pre,-1,sizeof(pre));
    for(int i = 0; i < n; i ++) {
        scanf("%d",&x);
        val[i] = x;
        c[i + 1] = node(i,i,x);
    }
    cnt = 0;
    memset(head,-1,sizeof(head));
    sort(c + 1,c + n + 1);
    while(m --) {
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);
        addedge(y,x,z);
    }
    if(val[0]) {
        puts("Bad King");
        return;
    }
    long long ans = 0;
    int i = 1;
    while(i <= n) {
        int j = i;
        while(j <= n && c[j].dis == c[i].dis) j ++;
        int cnt = 0;
        for(int k = i; k < j; k ++) {
            int u = c[k].v;
            for(int r = head[u]; r != -1; r = e[r].next) {
                x = e[r].v;
                if(val[x] <= val[u]) {
                    if(val[x] + e[r].dis < val[u]) {
                        ans += (val[u] - val[x] - e[r].dis);
                        unions(0,u);
                    }
                    else a[++ cnt] = node(x,u,val[x] + e[r].dis - val[u]);
                }
            }
        }
        sort(a + 1,a + cnt + 1);
        for(int k = 1; k <= cnt; k ++) {
            x = find(a[k].u);
            y = find(a[k].v);
            if(x != y) {
                unions(x,y);
                ans += a[k].dis;
            }
        }
        for(int k = i; k < j; k ++)
            if(find(0) != find(c[k].v)) {
                puts("Bad King");
                return;
            }
        i = j;
    }
    cout << ans << endl;
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

