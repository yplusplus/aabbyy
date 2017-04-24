#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

const int N = 333333;
const int M = 666666;
const int inf = 0x7fffffff;
int dist[N], layer[N];
bool visit[N];
int n, m, c;
int eh[N], tot;
struct Edge {
    int v, w, next;
} et[M];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v, int w) {
    Edge e = {v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int read() {
    char ch;
    ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    int t = 0;
    while (isdigit(ch)) {
        t = t * 10 + ch - '0';
        ch = getchar();
    }
    return t;
}

void spfa() {
    for (int i = 1; i <= 3 * n + 5; i++) dist[i] = inf, visit[i] = false;
    queue<int> que;
    que.push(1);
    dist[1] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, w = et[i].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!visit[v]) {
                    que.push(v);
                    visit[v] = true;
                }
            }
        }
    }
} 
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &c);
        init();
        for (int i = 1; i <= n; i++) {
            layer[i] = read();
            //scanf("%d", &layer[i]);
        }
        for (int i = 0; i < m; i++) {
            int a, b, w;
            a = read(), b = read(), w = read();
            //scanf("%d%d%d", &a, &b, &w);
            addedge(a, b, w << 1);
            addedge(b, a, w << 1);
        }
        for (int i = 1; i <= n; i++) {
            int l = layer[i];
            if (l > 1) addedge(n + l, i, c);
            if (l < n) addedge(i, n + l + 1, c);
            if (l > 1) addedge(i, n + n + l, c);
            if (l < n) addedge(n + n + l + 1, i, c);
        }
        spfa();
        int ans = dist[n];
        if (ans == inf) ans = -1;
        else ans >>= 1;
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}

