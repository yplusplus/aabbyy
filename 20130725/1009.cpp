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
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 1111;
const int M = 55555;
int n, m;
pii h[N], v[N];
int eh[N], tot;
struct Edge {
    int u, v, next;
} et[M];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int match[N];
bool vist[N];

bool dfs(int u) {
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!vist[v]) {
            vist[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match() {//二分图匹配
    int cnt = 0;
    memset(match, -1, sizeof (match));
    for (int u = 0; u < n; u++) {
        memset(vist, false, sizeof (vist));
        if (dfs(u)) cnt++; //每找到一条增广路，匹配数+1
    }
    return cnt; //返回最大匹配数
}

bool check(int a, int b) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (mp(h[a].fi + i, h[a].se) == mp(v[b].fi, v[b].se + j)) return true;
        }
    }
    return false;
}

int main() {
    while (~scanf("%d%d", &n, &m), n + m) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &h[i].fi, &h[i].se);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &v[i].fi, &v[i].se);
        }
        init();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (check(i, j)) {
                    addedge(i, j);
                }
            }
        }
        printf("%d\n", n + m - Match());
    }
    return 0;
}

