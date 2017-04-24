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

const int N = 1111;
int a[N * 5];
int n;
int ti[6][N * 5];
int period[6];
int to[5 * N];

int find_position(int a[], int x) {
    for (int i = 1; i <= 5 * n; i++)
        if (a[i] == x) return i;
}

void calc_period() {
    int pos = 1;
    for (int i = 0; i < n; i++) {
        to[i * 2 + 1] = pos++;
        to[i * 2 + 2] = pos++;
        to[n * 2 + i * 2 + 1] = pos++;
        to[n * 2 + i * 2 + 2] = pos++;
        to[n * 4 + i + 1] = pos++;
    }
    memset(ti, -1, sizeof(ti));
    for (int i = 1; i <= 5; i++) {
        int cnt = 0;
        pos = find_position(a, i);
        while (ti[i][pos] == -1) {
            ti[i][pos] = cnt++;
            pos = to[pos];
        }
        period[i] = cnt;
    }
}


void Exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (!b) {
        d = a, x = 1, y = 0;
    } else {
        Exgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

ll inv(ll a, ll b) {
    a %= b;
    ll d, x, y;
    Exgcd(a, b, d, x, y);
    x = (x % b + b) % b;
    return x;
}

ll calc(int n, ll a[], ll b[]) {
    ll a1 = a[0], b1 = b[0];
    for (int i = 1; i < n; i++) {
        ll a2 = a[i], b2 = b[i];
        ll d = __gcd(b1, b2);
        ll c = a2 - a1;
        if (c % d != 0) return -1;
        c /= d;
        ll x = inv(b1 / d, b2 / d);
        b2 /= d;
        x = (x * c % b2 + b2) % b2;
        a1 = (x * b1) + a1;
        b1 = b1 * b2;
        a1 = (a1 % b1 + b1) % b1;
    }
    if (a1) return a1;
    else return b1;
}

ll ans[N];
void solve() {
    calc_period();
    int c[5];
    ll a[10], b[10];
    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) c[j] = j + 1;
        do {
            bool found = false;
            for (int j = 0; j < 5; j++) {
                int tmp = ti[c[j]][5 * i + j + 1];
                if (tmp == -1) { found = true; break; }
                a[j] = tmp, b[j] = period[c[j]];
            }
            if (found) continue;
            ll ret = calc(5, a, b);
            if (ret == -1) continue;
            if (ans[i] == -1 || ans[i] > ret) ans[i] = ret;
        } while (next_permutation(c, c + 5));
    }
    int id = -1;
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) continue;
        if (id == -1 || ans[i] < ans[id]) id = i;
    }
    if (id != -1) printf("Player %d wins game number %I64d.\n", id + 1, ans[id]);
    else puts("Neverending game.");
}

void get_int(int &t) {
    char ch;
    ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    t = 0;
    while (isdigit(ch)) { t = t * 10 + ch - '0'; ch = getchar(); }
}

int main() {
    while (~scanf("%d", &n), n) {
        for (int i = 1; i <= 5 * n; i++) get_int(a[i]);
        solve();
    }
    return 0;
}
