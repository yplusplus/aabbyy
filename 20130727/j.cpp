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
const ll linf = 1LL << 55;


const int N = 111111;
const int M = 2 * N;
int n, m;
int F[N*2], B[N*2], pos[N];
int rmq[N*2][20], rn;
struct Edge {
	int u, v, next;
}et[M];
int eh[N], tot;
int dis[N];
inline void add(int u, int v) {
	Edge e = {u, v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}
inline void addedge(int u, int v) {
	add(u, v), add(v, u);
}
void dfs(int u, int pre, int deep) {
	F[++rn] = u, B[rn] = deep, pos[u] = rn;
	for(int son = eh[u]; son != -1; son = et[son].next) {
		int v = et[son].v;
		if(v == pre) continue;
        dis[v] = dis[u] + 1;
		dfs(v, u, deep + 1);
		F[++rn] = u, B[rn] = deep;
	}
}
void Init_RMQ() {
	for(int i = 1; i <= rn; i++) rmq[i][0] = i;
	for(int j = 1; (1<<j) <= rn; j++) {
		for(int i = 1; i + (1<<j) - 1 <= rn; i++) {
			int a = rmq[i][j-1], b = rmq[i+(1<<(j-1))][j-1];
			if(B[a] < B[b]) rmq[i][j] = a;
			else rmq[i][j] = b;
		}
	}
}
int RMQ(int a, int b) {
	int k = int(log(1.0 + b - a) / log(2.0));
	int u = rmq[a][k], v = rmq[b-(1<<k)+1][k];
	if(B[u] < B[v]) return F[u];
	else return F[v];
}
int LCA(int a, int b) {
	a = pos[a], b = pos[b];
	if(a > b) return RMQ(b, a);
	else return RMQ(a, b);
}
int fa[N];
void init() {
	tot = rn = 0;
	memset(eh, -1, sizeof(eh));
    for (int i = 0; i < N; i++) fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

int son[N];
pii edge[N];
int main() {
    while (~scanf("%d", &n)) {
        init();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &son[i]);
            if (!Union(i, son[i])) {
                edge[find(i)] = mp(i, son[i]);
            } else addedge(i, son[i]);
        }
        for (int i = 1; i <= n; i++) {
            if (fa[i] == i) {
                addedge(i, 0);
            }
        }
        dfs(0, 0, 0);
        Init_RMQ();
        scanf("%d", &m);
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            int ablca = LCA(a, b);
            int ans = inf;
            if (ablca == 0) {
                puts("-1");
                continue;
            }
            ans = min(ans, dis[a] - dis[ablca] + dis[b] - dis[ablca]);
            pii e = edge[find(a)];
            int u = e.fi, v = e.se;
            int aulca = LCA(a, u), avlca = LCA(a, v), bulca = LCA(b, u), bvlca = LCA(b, v);
            int tmp = dis[a] + dis[u] - 2 * dis[aulca] + dis[b] + dis[v] - 2 * dis[bvlca] + 1;
            ans = min(ans, tmp);
            tmp = dis[a] + dis[u] - 2 * dis[avlca] + dis[b] + dis[v] - 2 * dis[bulca] + 1;
            ans = min(ans, tmp);
            printf("%d\n", ans);
        }
    }
    return 0;
}
