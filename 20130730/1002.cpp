include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;
struct sannode
{
    int l,nl,ml,c;
    sannode *ch[26],*f;
    sannode() {
        for(int i = 0; i < 26; i ++)
            ch[i] = NULL;
        f = NULL;
        c = 0;
    }
}e[N],*tail,*head,*tmp, *a[N];

int cnt = 0;
void add(int c,int len)
{
    sannode *p = tail, *np = &e[cnt ++];
    np->l = np->nl = len;
    np->ml = 0;
    for(; p && !p->ch[c]; p = p->f) p->ch[c] = np;
    tail = np;
    if(!p) np->f = head;
    else {
        if(p->ch[c]->l == p->l + 1) np->f = p->ch[c];
        else {
            sannode *q = p->ch[c], *r = &e[cnt ++];
            *r = *q;
            r->ml = 0;
            r->l = r->nl = p->l + 1;
            q->f = np->f = r;
            for(; p && p->ch[c] == q; p = p->f) p->ch[c] = r;
        }
    }
}

char s[N];
int c[N];

struct point
{
    int x,id;
    point() {}
    point(int x,int id):x(x),id(id) {}
    friend bool operator < (const point &p,const point &q) {
        return p.x < q.x;
    }
};
void topo_sort()
{
    for(int i = 0; i < cnt; i ++) c[i] = 0;
    for(int i = 0; i < cnt; i ++)
        c[e[i].l] ++;
    for(int i = 1; i < cnt; i ++) c[i] += c[i - 1];
    for(int i = 0; i < cnt; i ++) a[-- c[e[i].l]] = &e[i];
}

int cal()
{
        
    for(int i = cnt - 1; i > 0; i --) {
        a[i]->f->c += a[i]->c;
    }
    int ans = 0;
    for(int i = cnt - 1; i > 0; i --) {
        ans += a[i]->c;
        a[i]->c = 0;
    }
    return ans;
}
    
    
vector<point> v[2010];
int ans[100010];
int tot = 0;

void dfs(sannode *root)
{
    tot = 0;
    for(int i = cnt - 1; i > 0; i --)
        tot += e[i].l - e[i].f->l;
}

int main()
{
    int t,m,x,y;
    scanf("%d",&t);
    while(t --) {
        scanf("%s",s + 1);
        int n = strlen(s + 1);
        for(int i = 1; i <= n; i ++)
            v[i].clear();
        scanf("%d",&m);
        for(int i = 1; i <= m; i ++) {
            scanf("%d%d",&x,&y);
            v[x].push_back(point(y,i));
        }
        for(int i = 1; i <= n; i ++)
            sort(v[i].begin(),v[i].end());
        for(int i = 1; i <= n; i ++) {
            for(int j = 0; j < cnt; j ++) {
                for(int k = 0; k < 26; k ++) {
                    e[j].ch[k] = NULL;
                }
                e[j].f = NULL;
                e[j].c = 0;
            }
            cnt = 0;
            if(v[i].size() == 0) continue;
            tmp = tail = head = &e[cnt ++];
            int pos = 0;
            int ct = 0;
            for(int j = i; j <= n && pos < v[i].size(); j ++) {
                add(s[j] - 'a', ++ ct);
                if(j != v[i][pos].x) continue;
                tot = 0;
                dfs(head);
                while(pos < v[i].size() && j == v[i][pos].x) {
                    ans[v[i][pos].id] = tot;
                    pos ++;
                }
            }
        }
        for(int i = 1; i <= m; i ++)
            printf("%d\n",ans[i]);
    }
    return 0;
}

