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

int visit[N];
bool isLock[N];
int room[N];
vector<int> vec[N];
void dfs(int u) {
    if (isLock[u]) {
        visit[u] = 1;
        return;
    }
    visit[u] = 2;
    if (room[u] != -1) {
        isLock[room[u]] = false;
        if (visit[room[u]] == 1) dfs(room[u]);
    }
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (visit[v] == 2) continue;
        dfs(v);
    }
}

int n, m, p;
int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            vec[i].clear();
            isLock[i] = false;
            room[i] = -1;
        }
        for (int i = 0, a, b; i < m; i++) {
            cin >> a >> b;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        cin >> p;
        for (int i = 0, a, b; i < p; i++) {
            cin >> a >> b;
            isLock[a] = true;
            room[b] = a;
        }
        memset(visit, 0, sizeof(visit));
        dfs(0);
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (visit[i] != 2) {
                found = true;
                break;
            }
        }
        printf("Case #%d: %s\n", Case++, found ? "No" : "Yes");
    }
    return 0;
}
