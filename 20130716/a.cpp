#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 40;

const int N = 111111;
const int M = N << 2;

int eh[N], tot;
struct Edge {
    int v, w, next;
} et[M];

void addedge(int u, int v, int w) {
    Edge e = {v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

bool visit[N];
ll dist[N];
int n, m, s, e, p1, p2, k;

ll findShortPath(int s, int e, int forbid = -1) {
    if (forbid == s) return linf;
    for (int i = 0; i < n; i++) dist[i] = linf, visit[i] = false;
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, w = et[i].w;
            if (v == forbid) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!visit[v]) {
                    que.push(v);
                    visit[v] = true;
                }
            }
        }
    }
    return dist[e];
}


int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        tot = 0;
        for (int i = 0; i < n; i++) eh[i] = -1;
        for (int i = 0, a, b, c; i < m; i++) {
            cin >> a >> b >> c;
            addedge(a, b, c);
            addedge(b, a, c);
        }
        cin >> s >> e >> p1 >> p2 >> k;
        ll ans = linf;
        ans = min(ans, findShortPath(s, e, p1));        
        ans = min(ans, findShortPath(s, p1) + findShortPath(p2, p1) * k + findShortPath(p1, e));
        ans = min(ans, findShortPath(s, p1) + findShortPath(p2, e, p1));
        if (ans == linf) ans = -1;
        printf("Case #%d: %lld\n", Case++, ans);
    }
    return 0;
}
