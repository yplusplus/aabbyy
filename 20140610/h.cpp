#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 222;
vector<int> vec[N];
int belong[N], dfn[N], low[N];
int stack[N], top;
bool ins[N];
int Dindex, scc;
int n, m;

pair<int, int> getVote() {
    static char buffer[10];
    int id;
    scanf("%d%s", &id, buffer);
    id--;
    int res = buffer[0] == 'y' ? 1 : 0;
    return make_pair(id, res);
}

void addedge(int u, int v) {
    vec[u].push_back(v);
}

void dfs(int u) {
    dfn[u] = low[u] = ++Dindex;
    stack[++top] = u;
    ins[u] = true;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
        else if (ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;
        ++scc;
        do {
            v = stack[top--];
            ins[v] = false;
            belong[v] = scc;
        } while (v != u);
    }
}

void tarjan() {
    Dindex = top = scc = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(ins, 0, sizeof(ins));
    for (int i = 0; i < (n << 1); i++) {
        if (!dfn[i]) {
            dfs(i);
        }
    }
}

bool check() {
    tarjan();
    for (int i = 0; i < n; i++) {
        if (belong[i << 1] == belong[i << 1 | 1]) return false;
    }
    return true;
}

int ans[N];
void solve(int Case) {
    for (int i = 0; i < (n << 1); i++) vec[i].clear();
    for (int i = 1; i <= m; i++) {
        int k;
        pair<int, int> ret;
        scanf("%d", &k);
        if (k <= 2) {
            for (int j = 0; j < k; j++) {
                ret = getVote();
                int id = ret.first << 1;
                int res = ret.second;
                addedge(id + (res ^ 1), id + res);
            }
        } else {
            vector<pair<int, int> > vec;
            for (int j = 0; j < k; j++) {
                vec.push_back(getVote());
            }
            for (int j = 0; j < k; j++) {
                int uid = vec[j].first << 1, ures = vec[j].second;
                for (int jj = 0; jj < k; jj++) {
                    if (j == jj) continue;
                    int vid = vec[jj].first << 1, vres = vec[jj].second;
                    addedge(uid + (ures ^ 1), vid + vres);
                }
            }
        }
    }
    printf("Case %d: ", Case++);
    if (!check()) puts("impossible");
    else {
        for (int i = 0; i < n; i++) {
            ans[i] = 0;
            for (int j = 0; j < 2; j++) {
                int u = i << 1;
                vec[u + (j ^ 1)].push_back(u + j);
                if (check()) ans[i] |= j + 1;
                vec[u + (j ^ 1)].pop_back();
            }
        }
        for (int i = 0; i < n; i++) {
            if (ans[i] == 1) putchar('n');
            else if (ans[i] == 2) putchar('y');
            else putchar('?');
        }
        puts("");
    }
}

int main() {
    int Case = 1;
    while (~scanf("%d%d", &n, &m), n && m) {
        solve(Case++);
    }
    return 0;
}
