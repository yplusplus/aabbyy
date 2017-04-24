#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

const int N = 20010;
const int oo = 1000000000;

void myscanf(int &x)
{
    char c;
    while(1) {
        c = getchar();
        if(isdigit(c)) break;
    }
    x = c - '0';
    while(1) {
        c = getchar();
        if(isdigit(c)) x = 10 * x + (c - '0');
        else break;
    }
}

struct point
{
    int x,y,id;
    void read() {
        myscanf(x);
        myscanf(y);
    }
    point() {}
    point(int x,int y,int id):x(x),y(y),id(id) {}
    friend bool operator < (const point &p,const point &q) {
        if(p.x != q.x) return p.x < q.x;
        return p.y < q.y;
    }
}a[N],b[N];

struct edge
{
    int u,v,dis;
    edge() {}
    edge(int u,int v,int dis):u(u),v(v),dis(dis) {}
    friend bool operator < (const edge &p,const edge &q) {
        return p.dis < q.dis;
    }
}e[N * 8];

int pre[N];
int find(int x)
{
    if(pre[x] == -1) return x;
    return pre[x] = find(pre[x]);
}

int find(int x,int a[],int n)
{
    int lt = 1,rt = n,mid;
    while(lt <= rt) {
        mid = (lt + rt) / 2;
        if(a[mid] == x) return mid;
        if(a[mid] > x) rt = mid - 1;
        else lt = mid + 1;
    }
}

struct seg
{
    int a[N * 4],b[N * 4];
    void init(int lt,int rt,int step) {
        a[step] = oo;
        b[step] = -1;
        if(lt == rt) return;
        int mid = (lt + rt) / 2;
        init(lt,mid,2 * step);
        init(mid + 1,rt,2 * step + 1);
    }
    
    void insert(int pos,int step,int L,int R,int val,int id) {
        if(L == R) {
            if(val < a[step]) {
                a[step] = val;
                b[step] = id;
            }
            return;
        }
        int mid = (L + R) / 2;
        if(pos <= mid) insert(pos,2 * step,L,mid,val,id);
        else insert(pos,2 * step + 1,mid + 1,R,val,id);
        if(a[2 * step] <= a[2 * step + 1]) {
            b[step] = b[2 * step];
        }
        else b[step] = b[2 * step + 1];
        a[step] = min(a[2 * step],a[2 * step + 1]);
    }
    
    int query(int lt,int rt,int step,int L,int R,int &id) {
        if(L == lt && rt == R) {
            id = b[step];
            return a[step];
        }
        int mid = (L + R) / 2;
        if(rt <= mid) return query(lt,rt,2 * step,L,mid,id);
        else if(lt > mid) return query(lt,rt,2 * step + 1,mid + 1,R,id);
        else {
            int id1,id2;
            int x = query(lt,mid,2 * step,L,mid,id1);
            int y = query(mid + 1,rt,2 * step + 1,mid + 1,R,id2);
            if(x <= y) id = id1;
            else id = id2;
            return min(x,y);
        }
    }
}T;
    
int dis(point p,point q)
{
    return abs(p.x - q.x) + abs(p.y - q.y);
}

void solve(int n,int &m)
{
    sort(a + 1,a + n + 1);
    int b[N];
    for(int i = 1; i <= n; i ++)
        b[i] = a[i].y - a[i].x;
    sort(b + 1,b + n + 1);
    int cnt = 1;
    for(int i = 2; i <= n; i ++)
        if(b[i] != b[cnt]) b[++ cnt] = b[i];
    T.init(1,cnt,1);
    for(int i = n; i >= 1; i --) {
        int id,val,x = find(a[i].y - a[i].x,b,cnt);
        val = T.query(x,cnt,1,1,cnt,id);
        if(val != oo) {
            e[m ++] = edge(a[i].id,a[id].id,dis(a[i],a[id]));
        }
        T.insert(x,1,1,cnt,a[i].x + a[i].y,i);
    }
}       
        
vector<int> ve[N];
int build_graph(int n)
{
    int m = 0;
    for(int times = 0; times < 4; times ++) {
        if(times == 1 || times == 3) {
            for(int i = 1; i <= n; i ++)
                swap(a[i].x,a[i].y);
        }
        else if(times == 2) {
            for(int i = 1; i <= n; i ++)
                a[i].x *= (-1);
        }
        solve(n,m);
    }
    return m;
}

void kruskal(int m)
{
    for(int i = 0; i < N; i ++) ve[i].clear();
    sort(e,e + m);
    memset(pre,-1,sizeof(pre));
    int ans = 0;
    for(int i = 0; i < m; i ++) {
        int x = find(e[i].u);
        int y = find(e[i].v);
        if(x == y) continue;
        pre[x] = y;
        ve[e[i].u].push_back(e[i].v);
        ve[e[i].v].push_back(e[i].u);
    }
}

int phi[N],com[N];
vector<int> v[N];

int get_phi(int n)
{
    int ans = n;
    for(int i = 2; i * i <= n; i ++) {
        if(n % i) continue;
        while(n % i == 0) n /= i;
        ans = ans / i * (i - 1);
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}
    
void init()
{
    phi[0] = 0;
    com[0] = 0;
    for(int i = 1; i < N;i ++) {
        for(int j = 1; j * j <= i; j ++) {
            if(i % j) continue;
            v[i].push_back(j);
            if(j * j != i) v[i].push_back(i / j);
        }
        phi[i] = get_phi(i);
        com[i] = i * (i - 1) / 2;
    }
}

int ans[N];
int visit[N],c[N];

int cal(int x)
{
    return com[visit[x]] * phi[x];
}

int sqs[N];
int cnt;

void dfs(int u,int fa)
{
    sqs[++ cnt] = u;
    for(int i = 0; i < ve[u].size(); i ++)
        if(ve[u][i] == fa) continue;
        else dfs(ve[u][i],u);
}
    
void solve(int m)
{
    int sum = 0;
    memset(visit,0,sizeof(visit));
    for(int i = 2; i <= m; i ++) {
        point pre = b[sqs[i - 1]],now = b[sqs[i]];
        if(i == 2) {
            for(int j = now.x; j <= now.y; j ++) {
                int x = c[j];
                for(int k = 0; k < v[x].size(); k ++) {
                    sum -= cal(v[x][k]);
                    visit[v[x][k]] ++;
                    sum += cal(v[x][k]);
                }
            }
            ans[sqs[i]] = sum;
        }
        else {
            if(pre.x < now.x) {
                for(int j = pre.x; j < now.x; j ++) {
                    int x = c[j];
                    for(int k = 0; k < v[x].size(); k ++) {
                        sum -= cal(v[x][k]);
                        visit[v[x][k]] --;
                        sum += cal(v[x][k]);
                    }
                }
            }
            else {
                for(int j = now.x; j < pre.x; j ++) {
                    int x = c[j];
                    for(int k = 0; k < v[x].size(); k ++) {
                        sum -= cal(v[x][k]);
                        visit[v[x][k]] ++;
                        sum += cal(v[x][k]);
                    }
                }
            }                    
            if(pre.y < now.y) {
                for(int j = pre.y + 1; j <= now.y; j ++) {
                    int x = c[j];
                    for(int k = 0; k < v[x].size(); k ++) {
                        sum -= cal(v[x][k]);
                        visit[v[x][k]] ++;
                        sum += cal(v[x][k]);
                    }
                }
            }          
            else {
               for(int j = now.y + 1; j <= pre.y; j ++) {
                    int x = c[j];
                    for(int k = 0; k < v[x].size(); k ++) {
                        sum -= cal(v[x][k]);
                        visit[v[x][k]] --;
                        sum += cal(v[x][k]);
                    }
                }
            }      
            ans[sqs[i]] = sum;
        }
    }               
}
int main()
{
    int cas = 0;
    init();
    int t,n,m;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) myscanf(c[i]);
        scanf("%d",&m);
        for(int i = 1; i <= m; i ++) {
            a[i].read();
            a[i].id = i;
        }
        ++ m;
        a[m].id = m;
        a[m].x = 0,a[m].y = -1;
        for(int i = 1; i <= m; i ++)
            b[i] = a[i];
        int tot = build_graph(m);
        kruskal(tot);
        cnt = 0;
        dfs(m,0);
        solve(m);
        printf("Case #%d:\n",++ cas);
        for(int i = 1; i < m; i ++)
            printf("%d\n",ans[i]);
    }
    return 0;
}




