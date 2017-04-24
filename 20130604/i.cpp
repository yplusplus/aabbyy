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

const int N = 333;
char maz[N][N];

int visit[N];
bool oddCircle;

int n;
void dfs(int u, int dep) {
    if (oddCircle) return;
    visit[u] = dep;
    for (int i = 0; i < n; i++) {
        if (maz[u][i] == '0' || u == i) continue;
        if (!visit[i]) dfs(i, dep + 1);
        else {
            if ((dep - visit[i]) % 2 == 0) {
                oddCircle = true;
                break;
            }
        }
    }
}

int d[N];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            d[i] = 0;
            scanf("%s", &maz[i]);
            for (int j = 0; j < n; j++) {
                if (i != j && maz[i][j] == '1') d[i]++;
            }
        }
        memset(visit, 0, sizeof(visit));
        oddCircle = false;
        dfs(0, 1);
        for (int i = 0; i < n && !oddCircle; i++) {
            if (!visit[i] && d[i] > 0) oddCircle = true;
        }
        puts(oddCircle ? "No" : "Yes");
    }
    return 0;
}
