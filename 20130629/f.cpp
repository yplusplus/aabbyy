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

const int N = 111;
int n, m, q;
bool maz[N][N];

int ans;

bool floyd() {
    bool found = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (maz[i][j]) continue;
            int cnt = 0;
            for (int k = 0; k < n; k++) {
                cnt += (i != k && j != k && maz[i][k] && maz[j][k]);
                if (cnt >= q) {
                    ans++;
                    maz[i][j] = maz[j][i] = true;
                    found = true;
                    break;
                }
            }
        }
    }
    return found;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> q;
        memset(maz, false, sizeof(maz));
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            maz[a][b] = maz[b][a] = true;
        }
        for (int i = 0; i < n; i++) {
            maz[i][i] = true;
        }
        ans = 0;
        while (floyd()) ;
        cout << ans << endl;
    }
    return 0;
}
