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

int n;
const int N = 1111;
int x[N], y[N], z[N];

bool check(int i, int j) {
    if (z[i] > z[j]) swap(i, j);
    if (y[j] <= z[i]) return true;
    int l = y[j] - z[i], r = z[j] - y[i];
    int d = __gcd(x[i], x[j]);
    l = (l + d - 1) / d;
    r = r / d;
    return l <= r;
}

int main() {
    while (~scanf("%d", &n)) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &x[i], &y[i], &z[i]);
        }
        for (int i = 0; i < n && !found; i++) {
            for (int j = i + 1; j < n; j++) {
                if (check(i, j)) {
                    found = true;
                    break;
                }
            }
        }
        puts(found ? "Cannot Take off" : "Can Take off");
    }
    return 0;
}
