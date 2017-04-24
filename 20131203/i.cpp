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
#include <sstream>
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

const int N = 5010;
const int MOD = 30;
int cnt[N][170];
bool visit[N];
int n, k;
int bits[1 << 15];
vector<int> vec[N];

void Union(int a, int b, int t) {
    if (t) {
        int d = n / MOD;
        for (int i = 0; i <= d; i++) cnt[a][i] |= cnt[b][i];
    } else {
        cnt[a][b / MOD] |= 1 << (b % MOD);
    }
}

int get_ones(int a) {
    int res = 0;
    int d = n / MOD;
    int mask = (1 << 15) - 1;
    for (int i = 0; i <= d; i++) {
        res += bits[cnt[a][i] & mask] + bits[cnt[a][i] >> 15];
    }
    return res;
}

void dfs(int u) {
    visit[u] = true;
    Union(u, u, 0);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) dfs(v);
        Union(u, v, 1);
    }
}

int main() {
    bits[0] = 0;
    for (int i = 1; i < 1 << 15; i++) bits[i] = bits[i >> 1] + (i & 1);
    while (~scanf("%d%d", &n, &k)) {
        vector<int> _set;
        _set.resize(k);
        int ans = 0, id = -1;
        for (int i = 0; i < k; i++) {
            scanf("%d", &_set[i]);
            _set[i]--;
        }
        for (int i = 0; i < n; i++) {
            vec[i].clear();
            visit[i] = false;
            for (int j = 0; j <= n / MOD; j++) cnt[i][j] = 0;
        }
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d", &x);
            string line;
            getline(cin, line);
            istringstream input(line);
            while (input >> y) { vec[x - 1].push_back(y - 1); }
        }
        for (int i = 0; i < k; i++) {
            if (!visit[_set[i]]) dfs(_set[i]);
            int ret = get_ones(_set[i]);
            if (ret > ans || (ret == ans && id > _set[i])) ans = ret, id = _set[i];
        }
        printf("%d\n", id + 1);
    }
    return 0;
}

