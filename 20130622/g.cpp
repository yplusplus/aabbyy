#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(),(a).end()
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define FORD(i,a,b) for (int i=(a); i>=(b); i--)
#define REP(i,b) FOR(i,0,b)
#define ll long long
#define sf scanf
#define pf printf

#define Maxn 111111
#define Maxm 111111
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int n, m;
struct node {
    pii key;
    int fix, mxy, miy, miid;
    node *lf, *rg;
} nodes[Maxn*30];
int memNodes;
struct Treap {
    node *rt;
    void cls() {
        rt = NULL;
    }
    void update(node *&r) {
        if (!r) return;
        //r->sum = r->rep;
        r->miid = r->key.se;
        if (r->lf) r->miid = min(r->miid, r->lf->miid);
        if (r->rg) r->miid = min(r->miid, r->rg->miid);
        r->miy = r->mxy = r->key.fi;
        if (r->lf) r->miy = min(r->miy, r->lf->miy);
        if (r->rg) r->mxy = max(r->mxy, r->rg->mxy);
    }
    void rotrg(node *&r) {
        node *tmp = r->lf;
        r->lf = tmp->rg;
        tmp->rg = r;
        update(r);
        r = tmp;
        update(r);
    }
    void rotlf(node *&r) {
        node *tmp = r->rg;
        r->rg = tmp->lf;
        tmp->lf = r;
        update(r);
        r = tmp;
        update(r);
    }
    void insert(pii num, node *&r) {
        if (!r) {
            //++memNodes;
            r = &nodes[++memNodes];
            r->lf = r->rg = NULL;
            r->key = num;
            r->miy = r->mxy = num.fi;
            r->miid = num.se;
            r->fix = rand();
        } 
        else {
            if (num < r->key) {
                insert(num, r->lf);
                if (r->lf->fix > r->fix)rotrg(r);
            } else {
                insert(num, r->rg);
                if (r->rg->fix < r->fix)rotlf(r);
            }
        }
        update(r);
    }
    void del(pii num, node *&r)   
    {
        if (!r) return;
        if (num < r->key) del(num, r->lf);
        else if (num > r->key) del(num, r->rg);
        else {
            if (r->lf == NULL && r->rg == NULL) {
                r = NULL;
            } else if (r->lf == NULL) {
                node *tmp = r;
                r = r->rg;
            } else if (r->rg == NULL) {
                node * tmp = r;
                r = r->lf;
            } else {
                if (r->lf->fix < r->rg->fix) {
                    rotlf(r);
                    del(num, r->lf);
                } else {
                    rotrg(r);
                    del(num, r->rg);
                }
            }
        }
        update(r);
    }

    int query(int ly, int ry, node *&r) {
        if (r == NULL) return m;
        //cout <<ly <<" "<<ry <<" : " <<r->key.fi <<" "<<r->key.se <<endl;
        if (ly <= r->miy && r->mxy <= ry) return r->miid;
        int ret = m;
        if (r->key.fi < ly ) return query(ly, ry, r->rg);
        else if (r->key.fi > ry )  return query(ly, ry, r->lf);
        //if (r->key.fi < ly && (r->rg && r->rg->miid < m)) return query(ly, ry, r->rg);
        //else if (r->key.fi > ry && (r->lf && r->lf->miid < m))  return query(ly, ry, r->lf);
        else {
            ret = min(ret, r->key.se);
            //if (r->rg && r->rg->miid < ret) ret = min(ret, query(ly, ry, r->rg)), cout <<r->rg->miid <<" *** "<<ret <<endl;
            //if (r->lf && r->lf->miid < ret) ret = min(ret, query(ly, ry, r->lf)), cout <<r->lf->miid <<" --- "<<ret <<endl;
            if (r->rg ) ret = min(ret, query(ly, ry, r->rg));
            if (r->lf ) ret = min(ret, query(ly, ry, r->lf));
        }
        return ret;
    }
};


struct rect{
    int xl, xr, yl, yr, z;
    int id;
    bool operator<(const rect &b ) const {
        return z < b.z;
    }
}d[Maxn];

struct SegmentTree {
    Treap root[Maxn*10];
    void build(int p, int l, int r) {
        root[p].cls();
        if (l == r) return ;
        int mid = (l + r) >>1;
        build(p<<1, l, mid);
        build(p<<1|1, mid+1, r);
    }

    void insert(int p, int l, int r, int idx, pii key) {
        //cout <<l <<" "<<r <<" "<<idx <<" (" <<key.fi <<"-" <<key.se <<")" <<endl;
        root[p].insert(key, root[p].rt);
        if (l == r) return;
        int mid = (l + r) >>1;
        if (idx <= mid) insert(p<<1, l, mid, idx, key);
        else insert(p<<1|1, mid+1, r, idx, key);
    }
    
    void Delete(int p, int l, int r, int idx, pii key) {
        root[p].del(key, root[p].rt);
        if (l == r) return;
        int mid = (l + r) >>1;
        if (idx <= mid) Delete(p<<1, l, mid, idx, key);
        else Delete(p<<1|1, mid+1, r, idx, key);
    }
    
    int querymin(int p, int l, int r, int lx, int rx, int ly, int ry) {
        if (lx <= l && r <= rx) {
            //cout <<l <<" "<<r <<endl;
            //cout <<p <<" "<<lx <<" "<<rx <<" "<<ly <<" "<<ry <<" " <<root[p].query(ly, ry, root[p].rt) <<endl;
            return root[p].query(ly, ry, root[p].rt);
        }
        int mid = (l + r) >>1;
        int ret = m;
        if (lx <= mid) ret = min(ret, querymin(p<<1, l, mid, lx, rx, ly, ry));
        if (rx > mid) ret = min(ret, querymin(p<<1|1, mid+1, r, lx, rx, ly, ry));
        return ret;
    }
}seg;

inline int getint() {
    char c = getchar();
    int t = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        t = t * 10 + c - '0';
        c = getchar();
    }
    return t;
}

pii Query[Maxm];
int bX[Maxn*4], totX;
int ans[Maxm];
int main() {
    srand(time(NULL));
    //sf("%d", &n);
    n = getint();
    totX = memNodes = 0;
    REP(i, n) {
        //sf("%d%d%d%d%d", &d[i].xl, &d[i].xr, &d[i].yl, &d[i].yr, &d[i].z);
        d[i].xl = getint();
        d[i].xr = getint();
        d[i].yl = getint();
        d[i].yr = getint();
        d[i].z = getint();
        d[i].id = i + 1;
        bX[totX++] = d[i].xl;
        bX[totX++] = d[i].xr;
    }
    sort(d, d+n);
    
    //sf("%d", &m);
    m = getint();
    REP(i, m) {
        //sf("%d%d", &Query[i].fi, &Query[i].se);
        Query[i].fi = getint();
        Query[i].se = getint();
        bX[totX++] = Query[i].fi;
    }
    
    sort(bX, bX+totX);
    totX = unique(bX, bX+totX) - bX;
    
    seg.build(1, 0, totX-1);
    REP(i, m) {
        Query[i].fi = lower_bound(bX, bX+totX, Query[i].fi) - bX;
        seg.insert(1, 0, totX-1, Query[i].fi, mp(Query[i].se, i));
    }
    
    memset(ans, 0, sizeof(ans));
    REP(i, n) {
         d[i].xl = lower_bound(bX, bX+totX, d[i].xl) - bX;
         d[i].xr = lower_bound(bX, bX+totX, d[i].xr) - bX;
         int idx = seg.querymin(1, 0, totX-1, d[i].xl, d[i].xr, d[i].yl, d[i].yr);
         if (idx >= m) continue;
         else {
             ans[idx] = d[i].id;
             seg.Delete(1, 0, totX-1, Query[idx].fi, mp(Query[idx].se, idx));
         }
    }
    
    REP(i, m) pf("%d\n", ans[i]);
    return 0;
}

