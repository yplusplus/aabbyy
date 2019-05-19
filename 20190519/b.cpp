#include <iostream>
#include <queue>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int K = 26;
const int N = 300000 + 30;
struct Node {
    int son[K];
    int fail, id;
    void init() {
        memset(son, 0, sizeof(son));
        fail = id = 0;
    }
} node[N];

char str[N];
int n, m;

int char2int(char ch) {
    return ch - 'a';
}

struct Trie {
    void init() {
        root = 0;
        tot = 0;
    }

    void build() {
        queue<int> que;
        que.push(root);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
                int p = node[u].fail;
                //cout << "fail " << u << " " << p << endl;
            for (int i = 0; i < K; i++) {
                if (node[u].son[i]) {
                    int child = node[u].son[i];
                    if (u) {
                        node[child].fail = node[p].son[i];
                        node[child].id |= node[node[p].son[i]].id;
                    }
                    que.push(child);
                } else {
                    // virtual node
                    node[u].son[i] = node[p].son[i];
                }
            }
        }
    }

    void insert(char *s) {
        int p = root;
        while (*s) {
            int idx = char2int(*s);
            if (!node[p].son[idx]) {
                node[++tot].init();
                node[p].son[idx] = tot;
            }
            p = node[p].son[idx];
            s++;
        }
        node[p].id = 1;
    }

    int root, tot;
} trie;

bool visit[N];
vector<pair<int, int> > vec[N];

void dfs(int u) {
    if (visit[u]) return;
    visit[u] = true;
    for (int i = 0; i < K; i++) {
        int v = node[u].son[i];
        if (node[v].id) continue;
        vec[u].push_back({v, i});
        //cout << "add " << u << " -> " << v << " " << i << endl;
        
        if (!visit[v]) {
            dfs(v);
        }
        /*
        if (v == u) {
            // self-edge
            vec[u].push_back({v, i});
            cout << "add " << u << " -> " << v << " " << i << endl;
        } else {
            if (node[v].id || visit[v]) continue;
            vec[u].push_back({v, i});
            cout << "add " << u << " -> " << v << " " << i << endl;
            dfs(v);
        }
        */
    }
}

int dfn[N], low[N];
int tot, scc;
bool instk[N];
vector<int> stk;
pair<int, int> circle;
int belong[N];
void tarjan(int u) {
    dfn[u] = ++tot;
    low[u] = dfn[u];
    instk[u] = true;
    stk.push_back(u);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instk[v]) {
            low[u] = min(low[u], dfn[u]);
        } else {
        }
    }

    if (dfn[u] == low[u]) {
        scc++;
        int x;
        int cnt = 0;
        do {
            x = stk.back();
            stk.pop_back();
            belong[x] = scc;
            cnt++;
        } while (x != u);
        if (cnt > 1) {
            circle = min(circle, {u, belong[u]});
        } else {
            // self-loop
            for (int i = 0; i < vec[u].size(); i++) {
                //cout << u << " ##" << vec[u][i].first << endl;
                if (vec[u][i].first == u) {
                    circle = min(circle, {u, belong[u]});
                    break;
                }
            }
        }
    }
}

char ans_str[N];
void find_circle(int u, int pos) {
    if (pos == n) return;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (belong[v] != belong[u]) continue;
        ans_str[pos] = vec[u][i].second + 'a';
        find_circle(v, pos + 1);
        return;
    }
    assert(false);
}

int dist[N];
pair<int,int> pre[N];
void find_link(int u) {
    if (visit[u]) return;
    visit[u] = true;
    dist[u] = 0;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        find_link(v);
        if (dist[v] + 1 > dist[u]) {
            //cout << u << " " << v << " " << dist[v] + 1 << endl;
            dist[u] = dist[v] + 1;
            pre[u] = vec[u][i];
        }
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    trie.init();
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        trie.insert(str);
    }

    trie.build();
    dfs(0);

    circle = {N, N};
    for (int i = 0; i <= trie.tot; i++) {
        if (dfn[i] == 0)
            tarjan(i);
    }
    //cout << circle.first << " " << circle.second << endl;
    if (circle.first < N) {
        //cout << "find circle" << endl;
        find_circle(circle.first, 0);
    } else {
        memset(visit, 0, sizeof(visit));
        memset(pre, -1, sizeof(pre));
        find_link(0);
        //cout << dist[0] << endl;
        int u = 0;
        for (int i = 0; i < n; i++) {
            ans_str[i] = pre[u].second + 'a';
            u = pre[u].first;
        }
    }

    ans_str[n] = 0;
    puts(ans_str);
}

int main() {
    solve();
    return 0;
}
