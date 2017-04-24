#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 50010;
const int oo = -1000000000;
struct tree
{
    int lt,rt;
    int val;
}a[N * 4];

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    a[step].val = oo;
    if(lt == rt) return;
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
}

void insert(int pos,int step,int val)
{
    if(a[step].lt == a[step].rt) {
        a[step].val = max(a[step].val,val);
        return;
    }
    if(pos <= a[2 * step].rt) insert(pos,2 * step,val);
    else insert(pos,2 * step + 1,val);
    a[step].val = max(a[2 * step].val,a[2 * step + 1].val);
}

int query(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        return a[step].val;
    }
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else {
        int x = query(lt,a[2 * step].rt,2 * step);
        int y = query(a[2 * step + 1].lt,rt,2 * step + 1);
        return max(x,y);
    }
}


struct point
{
    int id,x,y;
    point() {}
    point(int id,int x,int y):id(id),x(x),y(y) {}
}p1[N],p2[N];

bool cmp(const point &p,const point &q)
{
    return p.x > q.x;
};

struct node
{
    int x,y;
    int val;
    node() {}
    node(int x,int y,int val):x(x),y(y),val(val) {}
}e1[1000010];

bool cmpx(const node &p,const node &q) 
{
    return p.x > q.x;
}

int sum[N],ans[N];

void solve_positive(int n,int c,int d)
{
    sort(e1,e1 + c,cmpx);
    sort(p1,p1 + d,cmp);
    init(1,n,1);
    for(int i = 0,j = 0; i < d; i ++) {
        while(j < c && e1[j].x >= p1[i].x) {
            insert(e1[j].y,1,e1[j].val);
            j ++;
        }
        int val = query(p1[i].x,p1[i].y,1);
        if(val < 0) val = 0;
        ans[p1[i].id] = val;
    }

}

int cc[N],c[N];

struct edge
{
    int v,next;
}e[1000010];
int head[N],cnt;

void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

void read(int &x)
{
    char c ;
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

int main()
{
    int t;
    int n,m,r,x,y,z;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) {
            read(cc[i]);
        }
        memset(head,-1,sizeof(head));
        cnt = 0;
        int c1 = 0;;
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j * j <= cc[i]; j ++) {
                if(cc[i] % j) continue;
                addedge(j,i);
                if(j * j == cc[i]) continue;
                addedge(cc[i] / j,i);
            }
        }
        for(int i = 1; i <= n / 2; i ++) {
            int ct = 0;
            for(int j = head[i]; j != -1; j = e[j].next)
                c[++ ct] = e[j].v;
            reverse(c + 1,c + ct + 1);
            if(ct < 2) continue;
            for(int j = 2; j <= ct; j ++)
                e1[c1 ++] = node(c[j - 1],c[j],i);
        }
        int d1 = 0;
        scanf("%d",&r);
        for(int i = 1; i <= r; i ++) {
            read(x);
            read(y);
            p1[d1 ++] = point(i,x,y);
        }
        solve_positive(n,c1,d1);
        for(int i = 1; i <= r; i ++)
            printf("%d\n",ans[i]);
    }
    return 0;
}

