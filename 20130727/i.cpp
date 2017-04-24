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
int n, m;
int c[2][N];
int d[N];
void add(int x, int v, int c[]) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c[i] += v;
    }
}

int sum(int x, int c[]) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += c[i];
    }
    return res;
}

int sign(int x) {
    return x < 0 ? -1 : (x > 0 ? 1 : 0);
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &d[i]);
            if (d[i] == 0) add(i, 1, c[0]);
            else if (d[i] < 0) add(i, 1, c[1]);
        }
        char cmd[5];
        int a, b;
        while (m--) {
            scanf("%s%d%d", cmd, &a, &b);
            if (cmd[0] == 'C') {
                if (sign(b) == sign(d[a])) continue;
                else {
                    if (d[a] == 0) add(a, -1, c[0]);
                    if (d[a] < 0) add(a, -1, c[1]);
                    if (b == 0) {
                        add(a, 1, c[0]);
                    } else if (b < 0) {
                        add(a, 1, c[1]);
                    }
                    d[a] = b;
                }
            } else {
                int cnt = sum(b, c[0]) - sum(a - 1, c[0]);
                if (cnt) putchar('0');
                else {
                    cnt = sum(b, c[1]) - sum(a - 1, c[1]);
                    putchar((cnt & 1) ? '-' : '+');
                }
            }
        }
        puts("");
    }
    return 0;
}
