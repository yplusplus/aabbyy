#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

#define lc ch[0]
#define rc ch[1]
const int N = 8010;
struct tree
{
    int rev;
    tree *pre,*ch[2];
    
    void init() ;
    
    void reverse() {
        rev ^= 1;
        swap(lc,rc);
    }
    
    void down() {
        if(rev) {
            lc->reverse();
            rc->reverse();
            rev = 0;
        }
    }
    
}*stk[N];

struct LCT
{
    tree e[N];
    
    void init(int n) {
        e[0].lc = e[0].rc = e[0].pre = NULL;
        e[0].rev = 0;
        for(int i = 1; i < N; i ++) {
            e[i].pre = e[i].lc = e[i].rc = e;
            e[i].rev = 0;
        }
    }
    
    bool isroot(tree *x) {
        return x->pre->lc != x && x->pre->rc != x;
    }
    
    void rotate(tree *y,int w) {
        tree *x = y->pre;
        if(x == e) return;
        y->pre = x->pre;
        if(!isroot(x)) {
            x->pre->ch[x == x->pre->rc] = y;
        }
        x->ch[w] = y->ch[!w];
        x->ch[w]->pre = x;
        y->ch[!w] = x;
        x->pre = y;
    }
    
    void splay(tree *x) {
        int top = 0;
        stk[++ top] = x;
        for(tree *v = x; !isroot(v); v = v->pre) {
            stk[++ top] = v->pre;
        }
        while(top) stk[top --]->down(); 
        while(!isroot(x)) {
            tree *y = x->pre;
            int w = (x == y->rc);
            if(!isroot(y) && w == (y == y->pre->rc)) rotate(y,w);
            rotate(x,w);
        }
    }
    
    tree *gotoroot(tree *x) {
        tree *p = x,*q;
        for(q = e; p != e; p = p->pre) {
            splay(p);
            p->rc = q;
            (q = p)->down();
        }
        splay(x);
        return q;
    }
    
    void makeroot(tree *x) {
        gotoroot(x);
        x->reverse();
    }
    
    int getroot(tree *x) {
        gotoroot(x);
        for(; x->lc != e; x = x->lc) x->down();
        return x - e;
    }
    
    void link(tree *x,tree *y) {
        makeroot(x);
        x->pre = y;
    }
    
    void cut(tree *x,tree *y) {
        getroot(x);
        getroot(y);
        makeroot(x);
        splay(y);
        y->lc->pre = y->pre;
        y->pre = y->lc = e;
    }
    
    bool connect(tree *x,tree *y) {
        if(getroot(x) != getroot(y)) return false;
        return true;
    }
}spt[110];
int c[110][N];

struct point
{
    int x,y;
    point() {}
    point(int x,int y):x(x),y(y) {};
    friend bool operator < (const point &p,const point &q) {
        return p.x < q.x;
    }
};
set<point> st[N];
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

int main()
{
    int n,m,r,t,x,y,z;
    while(scanf("%d%d%d%d",&n,&m,&r,&t) != EOF) {
        if(!n && !m && !r && !t) break;
        for(int i = 0; i <= r; i ++)
            for(int j = 0; j <= n; j ++)
                c[i][j] = 0;
        for(int i = 1; i <= r; i ++) spt[i].init(n);
        for(int i = 0; i <= n; i ++) st[i].clear();
        while(m --) {
            read(x);
            read(y);
            read(z);
            spt[z].link(spt[z].e + x,spt[z].e + y);
            c[z][x] ++,c[z][y] ++;
            st[x].insert(point(y,z));
        }
        while(t --) {
            read(x);
            read(y);
            read(z);
            if(!st[x].count(point(y,z))) {
                printf("No such cable.\n");
                continue;
            }
            set<point>::iterator it = st[x].find(point(y,z));
            if(it->y == z) {
                printf("Already owned.\n");
                continue;
            }
            if(c[z][x] > 1 || c[z][y] > 1) {
                printf("Forbidden: monopoly.\n");
                continue;
            }
            if(c[z][x] && c[z][y]) {
                if(spt[z].connect(spt[z].e + x,spt[z].e + y)) {
                    printf("Forbidden: redundant.\n");
                    continue;
                }
            }
            c[z][x] ++,c[z][y] ++;
            c[it->y][x] --,c[it->y][y] --;
            spt[it->y].cut(spt[it->y].e + x,spt[it->y].e + y);
            st[x].erase(it);
            st[x].insert(point(y,z));
            spt[z].link(spt[z].e + x,spt[z].e + y);
            printf("Sold.\n");
        }
        cout << endl;
    }
    return 0;
}



