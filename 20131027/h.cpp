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

const int N = 333;
int f[N][N], g[N][N], h[N][N];
int n;
void build() {
    for (int i = 0; i < n; i++) {
        g[i][i] = h[i][i] = 0;
        for (int j = 0; j < i; j++) {
            if (f[i][j] > 1 || f[j][i] > 1 || (f[i][j] == 1 && f[j][i] == 1)) {
                g[i][j] = g[j][i] = n;
                h[i][j] = h[j][i] = 0;
            } else if (f[i][j] == 0 && f[j][i] == 0) {
                g[i][j] = g[j][i] = 0;
                h[i][j] = h[j][i] = 1;
            } else {
                g[i][j] = f[i][j];
                h[i][j] = f[i][j] ? 2 : 1;
                g[j][i] = f[j][i];
                h[j][i] = f[j][i] ? 2 : 1;
            }
        }
    }
}

bool check() {
    build();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (f[i][j] != g[i][j]) return false;
        }
    }
    return true;
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++)
                cin >> f[i][j];
        if (check()) {
            puts("YES");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << h[i][j];
                }
                cout << endl;
            }
        } else {
            puts("NO");
        }
    }
    return 0;
}
