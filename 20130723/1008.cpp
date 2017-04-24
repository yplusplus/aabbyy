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

const int N = 111111;
int eh[N], tot;
struct Edge {
    int v, next;
} et[N * 2];

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int visit[N];
int n, m;
void dfs(int u, int fa, int dep) {
    visit[u] = dep;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == fa) continue;
        dfs(v, u, dep + 1);
    }
}

int getD() {
    dfs(1, 0, 1);    
    int u = 1;
    for (int i = 2; i <= n; i++) {
        if (visit[i] > visit[u]) u = i;
    }
    dfs(u, 0, 1);
    u = 1;
    for (int i = 2; i <= n; i++) {
        if (visit[i] > visit[u]) u = i;
    }
    return visit[u];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d", &n, &m);
        tot = 0;
        memset(eh, -1, sizeof(int) * (n + 5));
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        int d = getD();
        int k;
        while (m--) {
            scanf("%d", &k);
            if (k <= d) printf("%d\n", k - 1);
            else printf("%d\n", d - 1 + (k - d) * 2);
        }
    }
    return 0;
}

