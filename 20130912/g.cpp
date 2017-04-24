#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <set>
using namespace std;

const int N = 200010;
int Map[N];
vector<int> vv[N],v[N],mat[N / 2];
int size[N],cc,C[N / 2];
set<int> ST[N];
void dummy(int n,vector<int> a)
{
    ++ cc;
    for(int i = 0; i < n; i ++) {
        Map[a[i]] = cc;
        C[a[i]] ++;
        vv[cc].push_back(a[i]);
    }
    size[cc] = n;
}

void search(int n,vector<int> mat[],int *dfn,int *low,int now,int &cnt,int *st,int &sp)
{
    int i,m;
    vector<int> a;
    dfn[st[sp ++] = now] = low[now] = ++ cnt;
    for(int j = 0; j < mat[now].size(); j ++) {
        i = mat[now][j];
        if(!dfn[i]) {
            search(n,mat,dfn,low,i,cnt,st,sp);
            if(low[i] < low[now]) low[now] = low[i];
            if(low[i] >= dfn[now]) {
                a.clear();
                for(st[sp] = -1,a.push_back(now),m = 1; st[sp] != i;a.push_back(st[-- sp]),m ++);
                dummy(m,a);
            }
        }
        else if(dfn[i] < low[now]) low[now] = dfn[i];
    }
}

int dfn[N / 2],low[N / 2],st[N / 2],visit[N];

void block(int n,vector<int> mat[])
{
    int i,cnt,sp = 0;
    for(i = 0; i <= n; dfn[i ++] = 0);
    for(cnt = 0,i = 1; i <= n; i ++)
        if(!dfn[i]) search(n,mat,dfn,low,i,cnt,st,sp);
}

void search(int n,vector<int> mat[],int *dfn,int *low,int now,int &cnt)
{
    int i,j;
    for(low[now] = dfn[now], j = 0; j < mat[now].size(); j ++) {
        i = mat[now][j];
        if(!dfn[i]) {
            dfn[i] = dfn[now] + 1;
            search(n,mat,dfn,low,i,cnt);
            if(low[i] > dfn[now]) {
                //key[cnt][0] = i;
                //key[cnt ++][1] = now;
                ST[i].insert(now);
                ST[now].insert(i);
            }
            if(low[i] < low[now]) low[now] = low[i];
        }
        else if(dfn[i] < dfn[now] - 1 && dfn[i] < low[now]) low[now] = dfn[i];
    }
}

int key_edge(int n,vector<int> mat[]) 
{
    int ret = 0;
    for(int i = 0; i <= n; dfn[i ++] = 0);
    for(int i = 1; i <= n; i ++)
        if(!dfn[i]) {
            dfn[i] = 1;
            search(n,mat,dfn,low,i,ret);
        }
    return ret;
}

void dfs(int u,int pre)
{
    visit[u] = 1;
    for(int i = 0; i < v[u].size(); i ++)
        if(v[u][i] != pre) dfs(v[u][i],u);
}

int P[N][19],pat[N],L[N];

void dfs(int fa,int u,int dist,int dep)
{
    L[u] = dep;
    pat[u] = fa;
    for(int i = 0; i < v[u].size(); i ++)
        if(v[u][i] != fa) {
            dfs(u,v[u][i],dist + 1,dep + 1);
        }
}

void init_lca(int n)
{
    int i,j;
    for(i = 1; i <= n; i ++)
        for(j = 1; j < 19; j ++) P[i][j] = -1;
    for(i = 1; i <= n; i ++) P[i][0] = pat[i];
    for(j = 1; (1 << j) <= n; j ++)
        for(i = 1; i <= n; i ++)
            if(P[i][j - 1] != -1)
                P[i][j] = P[P[i][j - 1]][j - 1];
}

int query_lca(int p,int q)
{
    if(L[p] < L[q]) swap(p,q);
    int i,log;
    for(log = 1; (1 << log) <= L[p]; log ++);
    log --;
    for(i = log; i >= 0; i --)
        if(L[p] - (1 << i) >= L[q])
            p = P[p][i];
    if(p == q) return p;
    for(i = log; i >= 0; i --)
        if(P[p][i] != -1 && P[p][i] != P[q][i])
            p = P[p][i],q = P[q][i];
    return pat[p];
}

void read(int &x)
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
        else return;
    }
}
    
int gdis(int x,int y,int n)
{
    int z = query_lca(x,y);
    if(z == n) return -1;
    return L[x] + L[y] - 2 * L[z];
}

bool check(int x,int y)
{
    /*
    int lt = 0,rt = mat[x].size() - 1,mid;
    bool flag = false;
    while(lt <= rt) {
        mid = (lt + rt) / 2;
        if(mat[x][mid] == y) {
            flag = true;
            break;
        }
        if(mat[x][mid] < y) lt = mid + 1;
        else rt = mid - 1;
    }
    if(!flag) return false;*/
    return ST[x].count(y);
}

int a[500010];
int main()
{
//    int SIZE=1<<27;
//    char *p=(char*)malloc(SIZE)+SIZE;
//    __asm__("movl %0, %%esp\n" :: "r"(p));
    int n,m,x,y,z,pp;
    int r,cd;
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 0; i < N; i ++) {
            vv[i].clear();
            v[i].clear();
            Map[i] = -1;
            visit[i] = 0;
            ST[i].clear();
        }
        for(int i = 0; i < N / 2; i ++)
            mat[i].clear();
        memset(C,-1,sizeof(C));
        for(int i = 1; i <= m; i ++) {
            read(x);
            read(y);
            if(x > y) swap(x,y);
            //a[i] = point(x,y);
            mat[x].push_back(y);
            mat[y].push_back(x);
            /*
            mat[x].push_back(y);
            mat[y].push_back(x);
            while(ST[x].count(y)) cout << "omg" << endl;
            while(ST[y].count(x)) cout << "omg" << endl;*/
        }
        for(int i = 1; i <= n; i ++) {
            sort(mat[i].begin(),mat[i].end());
            int et = 0;
            for(int j = 0; j < mat[i].size(); j ++)
                if(!j || mat[i][j] != mat[i][j - 1]) a[et ++] = mat[i][j];
            mat[i].clear();
            for(int j = 0; j < et; j ++)
                mat[i].push_back(a[j]);
        }
        /*
        sort(a + 1,a + m + 1);
        for(int i = 1; i <= m; i ++)
            if(i == 1 || !(a[i].x == a[i - 1].x && a[i].y == a[i - 1].y)) {
                x = a[i].x;
                y = a[i].y;
                mat[x].push_back(y);
                mat[y].push_back(x);
            }*/
        //cout << "fuck" << endl; 
            
        //for(int i = 0; i < N;i ++) ST[i].clear();
        cc = 0;
        int bridges = key_edge(n,mat);
        block(n,mat);
        for(int i = 0; i < N / 2;i ++) mat[i].clear();
        int tmp = cc;
        for(int i = 1; i <= n; i ++)
            if(C[i] > 0 || C[i] == -1) {
                size[++ cc] = -1;
                Map[i] = cc;
            }
        for(int i = 1; i <= tmp; i ++) {
            for(int j = 0; j < vv[i].size(); j ++) {
                if(C[vv[i][j]] > 0) {
                    v[i].push_back(Map[vv[i][j]]);
                    v[Map[vv[i][j]]].push_back(i);
                }
            }
        }
        for(int i = 1; i <= cc; i ++)
            if(!visit[i]) {
                dfs(i,0);
                v[cc + 1].push_back(i);
                v[i].push_back(cc + 1);
            }
        cc  ++;
        dfs(cc,cc,0,0);
        init_lca(cc);
        scanf("%d",&pp);
        while(pp --) {
            read(cd);
            if(cd == 2) {
                read(x);
                read(y);
                read(z);
                if(z == x || z == y || query_lca(Map[x],Map[y]) == cc) printf("no\n");
                else if(size[Map[z]] != -1 || Map[x] == Map[y]) printf("yes\n");
                else {
                    int d1 = gdis(Map[x],Map[y],cc);
                    int d2 = gdis(Map[x],Map[z],cc);
                    int d3 = gdis(Map[z],Map[y],cc);
                    if(d1 < 0) printf("no\n");
                    else if(d1 >= 0 && d2 >= 0 && d3 >= 0 && d1 == d2 + d3) printf("no\n");
                    else printf("yes\n");
                }
            }
            else {
                read(x);
                read(y);
                read(z);
                read(r);
                if(query_lca(Map[x],Map[y]) == cc) printf("no\n");
                else if(!check(z,r) || Map[x] == Map[y]) printf("yes\n");
                else {
                    int flag = 0;
                    int d1 = gdis(Map[x],Map[y],cc);
                    int d2 = gdis(Map[x],Map[z],cc);
                    int d3 = gdis(Map[z],Map[y],cc);
                    if(d1 >= 0 && d2 >= 0 && d3 >= 0 && d1 == d2 + d3) flag += 1;

                    swap(z,r);
                    d1 = gdis(Map[x],Map[y],cc);
                    d2 = gdis(Map[x],Map[z],cc);
                    d3 = gdis(Map[z],Map[y],cc);   
                    if(d1 >= 0 && d2 >= 0 && d3 >= 0 && d1 == d2 + d3) flag += 1;
   
                    if(flag == 2) printf("no\n");
                    else printf("yes\n");
                }
            }       
        }
    }   
    return 0;
}