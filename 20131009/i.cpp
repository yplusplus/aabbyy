#pragma comment(linker, "/STACK:102400000,102400000")
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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int kind = 26;
const int N = 111111;
char str[N];
int f[N], g[N], cnt[N];
int n;
struct Trie {
    int root, tot;
    struct Node {
        int child[kind], e;
        void init() {
            memset(child, 0, sizeof(child));
            e = 0;
        }
    } node[N];
    void clear() { node[root = tot = 0].init(); }
    void insert() {
        scanf("%s", str);
        int p = root, pos = 0;
        while (str[pos]) {
            int idx = str[pos] - 'a';
            if (!node[p].child[idx]) {
                node[p].child[idx] = ++tot;
                node[tot].init();
            }
            p = node[p].child[idx];
            pos++;
        }
        node[p].e = 1;
    }
    void dfs(int u) {
        if (node[u].e) {
            f[u] = g[u] = 0;
            cnt[u] = 1;
            return;
        }
        cnt[u] = 0;
        int sum = 0;
        for (int i = 0; i < kind; i++) {
            int v = node[u].child[i];
            if (v) {
                dfs(v);
                sum += f[v] + cnt[v];
                cnt[u] += cnt[v];
            }
        }
        f[u] = g[u] = inf;
        for (int i = 0; i < kind; i++) {
            int v = node[u].child[i];
            if (v) {
                f[u] = min(f[u], sum - f[v] + g[v]);
                g[u] = min(g[u], sum - f[v] - cnt[v] + g[v]);
            }
        }
    }
    int get_ans() {
        dfs(0);
        return f[0];
    }
} trie;

int main() {
    while (~scanf("%d", &n)) {
        trie.clear();
        for (int i = 0; i < n; i++) trie.insert();
        printf("%d\n", trie.get_ans());
        //for (int i = 0; i <= trie.tot; i++) {
            //cout << f[i] << " " << g[i] << endl;
        //}
    }
    return 0;
}
