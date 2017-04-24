#pragma comment(linker, "/STACK:10006777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int N = 100010;

struct tree
{
    int lt,rt,mx[2],lmx[2],rmx[2],lval,rval,len;
}a[N * 4];

int c[N];
//0连续递增子序列
//1连续下降子序列
void update(tree &p,tree q,tree r)
{
    p.lval = q.lval;
    p.rval = r.rval;
    p.lt = q.lt;
    p.rt = r.rt;
    p.len = q.len + r.len;
    p.mx[0] = max(q.mx[0],r.mx[0]);
    if(q.rval < r.lval) p.mx[0] = max(p.mx[0],q.rmx[0] + r.lmx[0]);
    p.mx[1] = max(q.mx[1],r.mx[1]);
    if(q.rval > r.lval) p.mx[1] = max(p.mx[1],q.rmx[1] + r.lmx[1]);
    p.lmx[0] = q.lmx[0];
    if(q.lmx[0] == q.len && q.rval < r.lval) p.lmx[0] += r.lmx[0];
    p.rmx[0] = r.rmx[0];
    if(r.rmx[0] == r.len && r.lval > q.rval) p.rmx[0] += q.rmx[0];
    
    p.lmx[1] = q.lmx[1];
    if(q.lmx[1] == q.len && q.rval > r.lval) p.lmx[1] += r.lmx[1];
    p.rmx[1] = r.rmx[1];
    if(r.rmx[1] == r.len && r.lval < q.rval) p.rmx[1] += q.rmx[1];
    
    //while(p.mx[0] == 0 || p.mx[1] == 0) cout << "fuck" << endl;
}

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    a[step].len = rt - lt + 1;
    if(lt == rt) {
        a[step].lval = a[step].rval = c[lt];
        for(int i = 0; i < 2; i ++) {
            a[step].mx[i] = a[step].lmx[i] = a[step].rmx[i] = 1;
        }
        return;
    }
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    update(a[step],a[2 * step],a[2 * step + 1]);
    //if(step == 2) cout << a[step].lt << " " << a[step].rt << " " << a[step].lval << " " << a[step].rval << endl;
}

tree query(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) return a[step];
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else {
        tree lnode = query(lt,a[2 * step].rt,2 * step);
        tree rnode = query(a[2 * step + 1].lt,rt,2 * step + 1);
        tree node;
        update(node,lnode,rnode);
        return node;
    }
}

struct edge
{
    int v,next;
}e[N];
int cnt,head[N];
void addedge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}

int fa[N],top[N],size[N],son[N],w[N],dep[N],e_num,map[N];

void init()
{
    cnt = e_num = 0;
    memset(head,-1,sizeof(head));
    memset(fa,0,sizeof(fa));
    memset(size,0,sizeof(size));
    memset(top,0,sizeof(top));
    memset(son,0,sizeof(son));
    memset(dep,0,sizeof(dep));
}

void dfs(int u)
{
    size[u] = 1;
    for(int i = head[u]; i != -1; i = e[i].next)
        if(e[i].v != fa[u]) {
            dep[e[i].v] = dep[u] + 1;
            fa[e[i].v] = u;
            dfs(e[i].v);
            size[u] += size[e[i].v];
            if(size[son[u]] < size[e[i].v]) son[u] = e[i].v;
        }
}

void dfs(int u,int tp)
{
    w[u] = ++ e_num;
    map[e_num] = u;
    top[u] = tp;
    if(son[u]) dfs(son[u],tp);
    for(int i = head[u]; i != -1; i = e[i].next)
        if(e[i].v != fa[u] && e[i].v != son[u])
            dfs(e[i].v,e[i].v);
}

tree f1[N],f2[N];
void find(int x,int y)
{
    if(x == y) {
        printf("1\n");
        return;
    }
    int fx = top[x],fy = top[y];
    int c1 = 0,c2 = 0;
    while(fx != fy) {
        if(dep[fx] < dep[fy]) {
            f2[c2 ++] = query(w[fy],w[y],1);
            y = fa[fy];
            fy = top[y];
        }
        else {
            f1[c1 ++] = query(w[fx],w[x],1);
            x = fa[fx];
            fx = top[x];
            swap(f1[c1 - 1].lmx[0],f1[c1 - 1].rmx[0]);
            swap(f1[c1 - 1].lmx[1],f1[c1 - 1].rmx[1]);
            swap(f1[c1 - 1].lval,f1[c1 - 1].rval);
            swap(f1[c1 - 1].mx[0],f1[c1 - 1].mx[1]);
            swap(f1[c1 - 1].lmx[0],f1[c1 - 1].lmx[1]);
            swap(f1[c1 - 1].rmx[0],f1[c1 - 1].rmx[1]);
        }
    }
    if(dep[x] >= dep[y]) {
        f1[c1 ++] = query(w[y],w[x],1);
        swap(f1[c1 - 1].lval,f1[c1 - 1].rval);
        swap(f1[c1 - 1].lmx[0],f1[c1 - 1].rmx[0]);
        swap(f1[c1 - 1].lmx[1],f1[c1 - 1].rmx[1]);
        swap(f1[c1 - 1].mx[0],f1[c1 - 1].mx[1]);
        swap(f1[c1 - 1].lmx[0],f1[c1 - 1].lmx[1]);
        swap(f1[c1 - 1].rmx[0],f1[c1 - 1].rmx[1]);
    }
    else f2[c2 ++] = query(w[x],w[y],1);
    for(int i = c2 - 1; i >= 0; i --)
        f1[c1 ++] = f2[i];
    tree t = f1[0],tmp;
    for(int i = 1; i < c1; i ++) {
        tmp = t;
        update(t,tmp,f1[i]);
    }
    printf("%d\n",t.mx[0]);
    /*
    for(int i = 0; i < c1; i ++)
        cout << f1[i].mx[0] << " " << f1[i].mx[1] << " " << f1[i].lt << " " << f1[i].rt << " " << endl;*/
}

int val[N];

int main()
{
    int t,n,m,x,y;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++)
            scanf("%d",&val[i]);
        init();
        for(int i = 2; i <= n; i ++) {
            scanf("%d",&x);
            addedge(x,i);
        }
        dfs(1);
        dfs(1,1);
        /*
        for(int i = 1; i <= n; i ++) cout << w[i] << " ";
        cout << endl;*/
        for(int i = 1; i <= n; i ++)
            c[i] = val[map[i]];
        init(1,e_num,1);
        //for(int i = 1; i <= n; i ++) cout << c[i] << " ";
        //cout << endl;
        printf("Case #%d:\n",cas);
        scanf("%d",&m);
        while(m --) {
            scanf("%d%d",&x,&y);
            find(x,y);
        }
        if(cas < t) cout << endl;
    }
    return 0;
}


/*
1
8
3 4 5 6 2 3 4 1
1 2 2 1 5 5 5
*/

/*
7
3 4 5 2 1 2 8
1 2 3 4 5 6
*/

/*
8
3 3 4 5 5 6 7 8
1 2 3 4 5 6 7
*/

