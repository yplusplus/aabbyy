#pragma comment(linker,"/STACK:102400000,102400000")
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
const int N = 222222;
const int M = 2222222;
int n, m, root;
int eh[N], tot, belong[N], bcc, dfn[N], low[N], Dindex;
int s[N], top;
int visit[N];
struct Edge {
    int v, id, next;
}et[M];
void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}
void addedge(int u, int v, int id) {
    Edge e = {v, id, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void dfs(int u, int pre) {
    dfn[u] = low[u] = ++Dindex, visit[u] = 1;
    s[++top] = u;
    int cnt = 0;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == pre) cnt++;
        if(visit[v] == 1 && (v != pre || cnt != 1)) low[u] = min(low[u], dfn[v]);
        if(visit[v] == 0) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) {//桥
                bcc++;    //[1, bcc]
                while(1) {//缩点,也可以直接利用low[]来缩点,low属于[1, n]
                    belong[s[top]] = bcc;
                    if(s[top--] == v) break;
                }
            }
        }
    }
    visit[u] = 2;
}
void tarjan() {
    top = bcc = Dindex = 0;
    memset(visit, 0, sizeof(visit));
    for(root = 1; root <= n; root++) {
        if(!visit[root]) dfs(root, -1);
        if (top) {
            bcc++;
            while (top) belong[s[top--]] = bcc;
        }
    }
}

vector<int> vec[N];

void dfs2(int u, int fa, int dep) {
    visit[u] = dep;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (visit[v] != -1) continue;
        dfs2(v, u, dep + 1);
    }
}

int getD() {
    memset(visit, -1, sizeof(visit));
    dfs2(1, 0, 1);
    int u = 1;
    for (int i = 2; i <= bcc; i++) {
        if (visit[i] > visit[u]) u = i;
    }
    memset(visit, -1, sizeof(visit));
    dfs2(u, 0, 1);
    u = 1;
    for (int i = 2; i <= bcc; i++) {
        if (visit[i] > visit[u]) u = i;
    }
    return visit[u];
}

int main() {
    while (~scanf("%d%d", &n, &m), n + m) {
        init();
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addedge(a, b, i), addedge(b, a, i);
        }
        tarjan();
        for (int i = 0; i <= bcc; i++) vec[i].clear();
        for (int i = 1; i <= n; i++) {
            for (int j = eh[i]; j != -1; j = et[j].next) {
                int v = et[j].v;
                if (belong[i] != belong[v]) {
                    vec[belong[i]].pb(belong[v]);
                    vec[belong[v]].pb(belong[i]);
                }
            }
        }
        int d = getD();
        printf("%d\n", bcc - d);
    }
    return 0;
}

