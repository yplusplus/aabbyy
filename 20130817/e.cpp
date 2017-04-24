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

const int N = 11111;
set<int> col;
int n, m;
int sum[N];
int d[N], f[N];
char digit[10][10] = {
    "|_||.|._.", "..|..|...", "|_.._|._.",
    "._|._|._.", "..||_|...", "._||_.._.",
    "|_||_.._.", "..|..|._.", "|_||_|._.",
    "._||_|._."
};

char calc(int k, int x, int y) {
    if (y > f[k] * 2) return '.';
    int i, j;
    if (x == 0) i = 0;
    else if (x == f[k] + 1) i = 2;
    else i = 1;
    j = -1;
    if (i == 1 && y % f[k] != 0) return '.';
    j = y / f[k];
    return digit[d[k]][j * 3 + i];
}

int main() {
    while (~scanf("%d", &n), n) {
        col.clear();
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &d[i], &f[i]);
            sum[i] = sum[i - 1] + 1 + f[i] + 2;
            col.insert(sum[i]);
        }
        int m, x, y;
        scanf("%d", &m);
        while (m--) {
            scanf("%d%d", &x, &y);
            x++;
            if (col.count(x)) {
                puts(".");
                continue;
            }
            int l = 1, r = n;
            int res = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (sum[mid] - 1 >= x) res = mid, r = mid - 1;
                else l = mid + 1; 
            }
            x -= sum[res - 1];
            x--;
            putchar(calc(res, x, y));
            puts("");
        }
    }
    return 0;
}
