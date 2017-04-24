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
const int M = 333333;
bool maz[N][N], visit[N];
int matchx[N], n, m, matchy[N];
bool dfs(int u) {
    for (int v = 1; v <= m; v++) {
        if (maz[u][v] && !visit[v]) {
            visit[v] = true;
            if (matchx[v] == -1 || dfs(matchx[v])) {
                matchx[v] = u;
                matchy[u] = v;
                return true;
            }
        }
    }
    return false;
}
int Match() {
    int cnt = 0;
    memset(matchx, -1, sizeof (matchx));
    memset(matchy, -1, sizeof (matchy));
    for (int u = 1; u <= n; u++) {
        memset(visit, false, sizeof (visit));
        if (dfs(u)) cnt++;
    }
    return cnt;
}

struct Edge {
    int v, next;
} et[M];

int dfn[N], low[N], Dindex, instack[N], belong[N], scc;
int s[N], top;
int eh[N], tot;
void addedge(int u, int v) {
	Edge E = {v, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}
void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}
void tdfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		v = et[i].v;
		if(!dfn[v]) tdfs(v), low[u] = min(low[u], low[v]);
		else if(instack[v]) low[u] = min(low[u], dfn[v]);	
     }
	if(dfn[u] == low[u]) {
		scc++;
		do {
			v = s[top--];
			instack[v] = false;
			belong[v] = scc;
		}while(v != u);
	}
}
void tarjan() {
	top = scc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
    memset(belong, 0, sizeof(belong));
	for (int i = 1; i <= n + m; i++) {
		if(!dfn[i]) tdfs(i);
		if (top) {
            scc++;
            while (top) belong[s[top--]] = scc;
        }
	}
}

bool flag[N];
bool flag1[N];
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        memset(maz, false, sizeof(maz));
        for (int i = 1, k, x; i <= n; i++) {
            scanf("%d", &k);
            while (k--) {
                scanf("%d", &x);
                maz[i][x] = true;
                addedge(i, x + n);
            }
        }
        Match();
        for (int i = 1; i <= m; i++) {
            if (matchx[i] != -1) {
                addedge(i + n, matchx[i]);
            }
        }
        tarjan();
        queue<int> que;
        memset(flag, false, sizeof(flag));
        memset(visit, false, sizeof(visit));
        for (int i = 1; i <= m; i++) {
            if (matchx[i] == -1) {
                que.push(i);
                visit[i] = true;
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = 1; i <= n; i++) {
                if (maz[i][u]) {
                    flag[belong[i]] = true;
                    for (int j = 1; j <= m; j++) {
                        if (!visit[j] && belong[i] == belong[j + n]) {
                            que.push(j);
                            visit[j] = true;
                        }
                    }
                }
            }
        }
        memset(flag1, false, sizeof(flag1));
        memset(visit, false, sizeof(visit));
        for (int i = 1; i <= n; i++) {
            if (matchy[i] == -1) {
                que.push(i);
                visit[i] = true;
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            flag1[belong[u]] = true;
            for (int i = 1; i <= m; i++) {
                if (maz[u][i]) {
                    for (int j = 1; j <= n; j++) {
                        if (!visit[j] && belong[i + n] == belong[j]) {
                            que.push(j);
                            visit[j] = true;
                        }
                    }
                }
            }
        }
        printf("Case #%d:\n", Case++);
        vector<int> ans;
        for (int i = 1; i <= n; i++) {
            ans.clear();
            for (int j = 1; j <= m; j++) {
                if (!maz[i][j]) continue;
                if (belong[i] == belong[j + n]) ans.pb(j);
                else if (matchy[i] == -1 || matchx[j] == -1 || flag[belong[matchx[j]]] || flag1[belong[i]]) ans.pb(j);
            }
            printf("%d", ans.size());
            for (int j = 0; j < ans.size(); j++) {
                printf(" %d", ans[j]);
            }
            puts("");
        }
    }
    return 0;
}

