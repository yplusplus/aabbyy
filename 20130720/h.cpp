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
#define Maxn 1111111
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
const int N = 1000010;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int n;

struct BIT {
    int tree[Maxn];
    void clr() {
        memset(tree, 0, sizeof(tree));
    }
    void add(int idx, int val) {
        //cout <<"edit " <<idx <<" val : " <<val <<endl;
        for (; idx <= N; idx += idx & -idx) tree[idx] += val;
    }
    int query(int idx) {
        int ret = 0;
        for (; idx; idx -= idx&-idx) ret += tree[idx];
        return ret;
    }
    int getsum(int a, int b) {
        return query(b) - query(a-1);
    }
    int find(int k){
        int cnt = 0, ret = 0;
        for(int i=21; i>=0; i--){
            ret += (1<<i);
            if(ret >= N || cnt + tree[ret] >= k) ret -= (1<<i);
            else cnt += tree[ret];
        }
        return ret + 1;
    }

};
BIT seg;

int fa[Maxn], tot[Maxn], len[Maxn], num[Maxn];
bool vis[Maxn];

int getFa(int x) {
    if (fa[x] == x) return fa[x];
    else return fa[x] = getFa(fa[x]);
}

void Union(int x, int y) {
    if (x < y) {
        fa[y] = x;
        tot[x] += tot[y];
        len[x] += len[y];
    }
    else {
        fa[x] = y;
        tot[y] += tot[x];
        len[y] += len[x];
    }
}

void init() {
    seg.clr();
    REP(i, N+2) fa[i] = i, tot[i] = 0, len[i] = 1, num[i] = 0;
    memset(vis, false, sizeof(vis));
}

void GetTowers() {
    printf("%d towers\n", seg.getsum(1, N));
}

void GetTCubes() {
    int id, x;
    sf("%d%d", &id, &x);
    int loc = seg.find(id);
    printf("%d cubes in %dth column of %dth tower\n", num[loc+x-1], x, id);
}

void GetCubes() {
    int id;
    sf("%d", &id);
    printf("%d cubes in %dth tower\n", tot[getFa(seg.find(id))], id);
}

void GetLength() {
    int id;
    sf("%d", &id);
    int st = seg.find(id);
    //cout <<"The " <<id <<"th seg start at " <<st <<endl;
    printf("length of %dth tower is %d\n", id, len[st]);
}

void putCubes(int x, int c) {
    //cout <<"***** loc " <<x <<" add " <<c <<" cubes" <<endl; 
    int p = getFa(x);
    num[x] += c;
    tot[p] += c;
    if (vis[x]) return;
    vis[x] = true;
    seg.add(x, 1);
    if (vis[x+1]) {
        int y = getFa(x+1);
        seg.add(getFa(x), -1);
        seg.add(y, -1);
        Union(getFa(x), y);
        seg.add(getFa(x), 1);
    }
    if (vis[x-1]) {
        //if (!flag) seg.add(getFa(x), -1);
        int y = getFa(x - 1);
        seg.add(y, -1);
        seg.add(getFa(x), -1);
        Union(getFa(x), y);
        seg.add(getFa(x), 1);
    }
    //cout <<" ------ " <<len[1] <<" "<<len[2] <<" "<<len[3] <<endl;
}
void WorkPut() {
    int x, c;
    sf("%d%d", &x, &c);
    putCubes(x, c);
}

void WorkTPut() {
    int id, x, c;
    sf("%d%d%d", &id, &x, &c);
    int loc = seg.find(id);
    putCubes(loc + x - 1, c);
}

void solve() {
    char op[10];
    REP(i, n) {
        sf("%s", op);
        if (op[0] == 't' && op[1] == 'o') GetTowers();
        else if (op[0] == 't' && op[1] == 'c') GetTCubes();
        else if (op[0] == 'c') GetCubes();
        else if (op[0] == 'l') GetLength();
        else if (op[0] == 'p') WorkPut();
        else if (op[0] == 't' && op[1] == 'p') WorkTPut();
    }

}
int main() {
    while (~sf("%d", &n)) {
        init();
        solve();
    }
    return 0;
}


