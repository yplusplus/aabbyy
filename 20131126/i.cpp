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

const int N = 22222;
struct Human {
    int s, e;
    void read() { scanf("%d%d", &s, &e); }
    bool operator < (const Human &x) const {
        if (e != x.e) return e > x.e;
        else return s > x.s;
    }
} human[N];
int n;
int rec[N];

int bs(int pos, int x) {
    int l = 0, r = pos;
    int res = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (rec[mid] >= x) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) human[i].read();
        sort(human, human + n);
        int ans = 0;
        for (int i = 0; i < n; i++) rec[i] = inf;
        for (int i = 0; i < n; i++) {
            int res = bs(ans, human[i].s);
            if (res == ans) ans++;
            rec[res + 1] = human[i].s;
        }
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
