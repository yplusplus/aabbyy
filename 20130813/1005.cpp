#pragma comment(linker, "/STACK:10006777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

const int N = 50010;

struct edge
{
    int v,next;
}e[2 * N];

int head[N],cnt,m;
long long pri[35];
int val[N][35];
long long vv[N];
map<long long,int> st;

long long hashval(int a[])
{
    long long hashval = 0;
    for(int i = 0; i < m; i ++)
        hashval = hashval * 3LL + a[i];
    return hashval;
}
    
void init(int n)
{
    scanf("%d",&m);
    for(int i = 0; i < m; i ++) {
        scanf("%I64d",&pri[i]);
    }
    for(int i = 1; i <= n; i ++) {
        scanf("%I64d",&vv[i]);
        while(!vv[i]) printf("omg\n");
        if(!vv[i]) {
            for(int j = 0; j < m; j ++)
                val[i][j] = 0;
        }
        else {
            long long x = vv[i];
            for(int j = 0; j < m; j ++) {
                val[i][j] = 0;
                while(x % pri[j] == 0) x /= pri[j],val[i][j] ++;
                val[i][j] %= 3;
            }
        }
    }
}

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

int ct,size[N],msize[N],visit[N];
struct point
{
    int x,y;
    point() {}
    point(int x,int y):x(x),y(y) {}
}a[N];

void dfs(int u,int fa)
{
    size[u] = 1;
    msize[u] = 0;
    for(int i = head[u]; i != -1; i = e[i].next)
        if(e[i].v != fa && !visit[e[i].v]) {
            dfs(e[i].v,u);
            size[u] += size[e[i].v];
            msize[u] = max(msize[u],size[e[i].v]);
        }
    a[ct ++] = point(u,msize[u]);
}

int get_center(int u)
{
    ct = 0;
    dfs(u,0);
    int ans = 0;
    int mi = 0x7fffffff;
    int sum = size[u];
    for(int i = 0; i < ct; i ++) {
        a[i].y = max(a[i].y,sum - a[i].y);
        if(a[i].y < mi) {
            mi = a[i].y;
            ans = a[i].x;
        }
    }
    return ans;
}

long long ans = 0;
long long re[N];
void dfs(int u,int fa,int a[])
{
    int c[31];
    for(int i = 0; i < m; i ++) {
        c[i] = a[i] + val[u][i];
        if(c[i] >= 3) c[i] -= 3;
    }
    re[ct] = hashval(c);
    if(re[ct] == 0) ans ++;
    ct ++;
    for(int i = head[u]; i != -1; i = e[i].next)
        if(e[i].v != fa && !visit[e[i].v]) {
            dfs(e[i].v,u,c);
        }
}

void Count(int u)
{
    int b[35];
    for(int i = 0; i < ct; i ++) {
        long long x = re[i];
        for(int j = m - 1; j >= 0; j --) {
            b[j] = x % 3;
            x /= 3;
            b[j] -= val[u][j];
            if(b[j] < 0) b[j] += 3;
            if(b[j]) b[j] = 3 - b[j];
        }
        long long hash = hashval(b);
        if(st.count(hash)) ans += st[hash];
    }
    for(int i = 0; i < ct; i ++) {
        st[re[i]] ++;
    }   
}

void cal2(int u)
{
    if(hashval(val[u]) == 0) ans ++;
    visit[u] = 1;
    for(int i = head[u]; i != -1; i = e[i].next) {
        if(visit[e[i].v]) continue;
        ct = 0;
        dfs(e[i].v,u,val[u]);
        Count(u);
    }
    st.clear();
}

void cal(int u,int fa)
{
    u = get_center(u);
    st.clear();
    cal2(u);
    for(int i = head[u]; i != -1; i = e[i].next)
        if(e[i].v != fa && !visit[e[i].v]) {
            cal(e[i].v,u);
        }
}

int main()
{
    int n;
    int x,y,z;
    while(scanf("%d",&n) != EOF) {
        init(n);
        cnt = 0;
        memset(head,-1,sizeof(head));
        for(int i = 1; i < n; i ++) {
            scanf("%d%d",&x,&y);
            addedge(x,y);
            addedge(y,x);
        }
        ans = 0;
        memset(visit,0,sizeof(visit));
        cal(1,0);
        printf("%I64d\n",ans);
    }
    return 0;
}

