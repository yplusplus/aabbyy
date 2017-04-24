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
const int M = 111111;
int n, m, root;
int visit[N];
int cnt[N], cc[N];;
struct edge {
    int v, next;
}et[M];
int dfn[N], low[N], Dindex, instack[N], belong[N], scc;
int s[N], top;
int eh[N], tot;
void addedge(int u, int v) {
    edge E = {v, eh[u]};
    et[tot] = E;
    eh[u] = tot++;
}
void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}
void dfs(int u) {
    int v;
    dfn[u] = low[u] = ++Dindex;
    s[++top] = u, instack[u] = true;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        v = et[i].v;
        if(!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
        else if(instack[v]) low[u] = min(low[u], dfn[v]);    
    }
    if(dfn[u] == low[u]) {
        scc++;
        do {
            v = s[top--];
            instack[v] = false;
            belong[v] = scc;
            cnt[scc]++;
        }while(v != u);
    }
}
void tarjan() {
    top = scc = Dindex = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    for (int i = 1; i <= n; i++) {
        if(!dfn[i]) dfs(i);
        if (top) {
            scc++;
            while (top) belong[s[top--]] = scc, cnt[scc]++;
        }
    }
}

int in[N], out[N];

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        memset(cnt, 0, sizeof(cnt));
        memset(cc, 0, sizeof(cc));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        tarjan();
        if (scc == 1) {
            printf("Case %d: ", Case++);
            puts("-1");
            continue;
        }
        //calculate
        for (int u = 1; u <= n; u++) {
            for (int j = eh[u]; j != -1; j = et[j].next) {
                int v = et[j].v;
                if (belong[u] == belong[v]) {
                    cc[belong[u]]++;
                } else {
                    in[belong[v]]++, out[belong[u]]++;
                }
            }
        }
        ll ans = 0;
        for (int i = 1; i <= scc; i++) {
            if (out[i] == 0 || in[i] == 0) {
                ll t = n - cnt[i];
                ll tmp = t * (t - 1) - m + (cnt[i] * 1LL * (cnt[i] - 1)) + t * cnt[i] ;
                ans = max(ans, tmp);
            }
        }
        printf("Case %d: ", Case++);
        cout << ans << endl;
    }
    return 0;
}

