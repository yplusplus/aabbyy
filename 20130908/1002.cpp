#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 111111;
vector<int> vec[N];
int fa[N];
int dist[N];
int n, d;
void bfs() {
    queue<int> que;
    que.push(0);
    memset(dist, -1, sizeof(dist));
    memset(fa, -1, sizeof(fa));
    dist[0] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            if (v == fa[u] || dist[v] != -1) continue;
            fa[v] = u;
            dist[v] = dist[u] + 1;
            que.push(v);
        }
    }
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d", &n, &d);
        for (int i = 0; i < n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        bfs();
        int ans = 0;
        for (int i = 0; i < n; i++) ans += dist[i] > d;
        printf("%d\n", ans);
    }
    return 0;
}