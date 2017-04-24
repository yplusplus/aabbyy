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

const int N = 111;
char maz[N][N];
int my[N * N];
bool visit[N * N];
vector<int> vec[N * N];
int n, m;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maz[x][y] != 'X';
}

int get_id(int x, int y) {
    return x * m + y;
}

bool dfs(int u) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            visit[v] = true;
            if (my[v] == -1 || dfs(my[v])) {
                my[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match(int t) {
    int cnt = 0;
    memset(my, -1, sizeof(my));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maz[i][j] == 'X') continue;
            if ((i + j) % 2 == t) {
                memset(visit, false, sizeof(visit));
                cnt += dfs(get_id(i, j));
            }
        }
    }
    return cnt;
}

void solve(int t) {
    Match(t);
    t ^= 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maz[i][j] == 'X') continue;
            if ((i + j) % 2 == t) {
                int v = get_id(i, j);
                memset(visit, false, sizeof(visit));
                visit[v] = true;
                if (my[v] == -1 || dfs(my[v])) maz[i][j] = 'B', my[v] = -1;
                else maz[i][j] = 'A';
            }
        }
    }
}

int main() {
    while (~scanf("%d%d", &n, &m), n + m) {
        for (int i = 0; i < n; i++) scanf("%s", &maz[i]);
        for (int i = 0; i < n * m; i++) vec[i].clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maz[i][j] == 'X') continue;
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (check(x, y)) { vec[get_id(i, j)].push_back(get_id(x, y)); }
                }
            }
        }
        solve(0);
        solve(1);
        for (int i = 0; i < n; i++) puts(maz[i]);
        puts("");
    }
    return 0;
}
