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

const int kind = 26;
const int N = 1111111;
int root, tot;
struct Node {
    int child[kind];
    bool id;
    void init() {
        memset(child, 0, sizeof (child));
        id = 0;
    }
} T[N];
void init() {
    root = tot = 0;
    T[root].init();
}
void insert(char *s) {
    int p = root, index;
    while (*s) {
        index = *s - 'a';
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].id = 1;
}

double ans;
void dfs(int u, int dep) {
    if (T[u].id) ans += dep;
    int cnt = 0;
    int idx = -1;
    for (int i = 0; i < 26; i++) if (T[u].child[i] != 0) cnt++, idx = T[u].child[i];
    if (u != root && !T[u].id && cnt == 1) {
        dfs(idx, dep);
    } else {
        for (int i = 0; i < 26; i++) {
            if (T[u].child[i]) {
                dfs(T[u].child[i], dep + 1);
            }
        }
    }
}
int n;
int main() {
    char str[100];
    while (~scanf("%d", &n)) {
        init();
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            insert(str);
        }
        ans = 0;
        dfs(root, 0);
        printf("%.2f\n", ans / n);
    }
    return 0;
}
