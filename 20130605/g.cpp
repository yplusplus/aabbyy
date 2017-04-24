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

const int N = 8;
unsigned char row[N];
unsigned char result[N + 2][1 << N][1 << N];
int n;
int cnt[1 << N];
vector<ull> vec[N + 2][1 << N];
unsigned char get(int n, int a, int b) {
    unsigned char mask = 0;
    for (int i = 0; i < n; i++) {
        int flag = a >> i & 1;
        flag ^= (b >> i & 1);
        if (i + 1 < n) flag ^= (b >> i >> 1 & 1);
        if (i - 1 >= 0) flag ^= (b >> (i - 1) & 1);
        mask |= flag << i;
    }
    return mask;
}

void init() {
    cnt[0] = 0;
    for (int i = 1; i < (1 << N); i++) cnt[i] = cnt[i >> 1] + (i & 1);
    for (int i = 1; i <= N; i++) {
        int all = 1 << i;
        for (int mask = 0; mask < all; mask++) {
            for (int sub = 0; sub < all; sub++) {
                result[i][mask][sub] = get(i, mask, sub);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        int all = 1 << i;
        for (int mask = 0; mask < all; mask++) {
            memset(row, 0, sizeof(row));
            ull move = mask;
            row[0] = result[i][row[0]][mask];
            if (1 < i) row[1] ^= mask;
            for (int j = 1; j < i; j++) {
                row[j] = result[i][row[j]][row[j - 1]];
                if (j + 1 < i) row[j + 1] ^= row[j - 1];
                move <<= i;
                move |= row[j - 1];
            }
            vec[i][row[i - 1]].pb(move);
        }
    }
}

int count(ull mask, int n) {
    int res = 0;
    int all = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
        res += cnt[mask & all];
        mask >>= n;
    }
    return res;
}

int getint(){
    char c = getchar();
    int t = 0;
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        t = t * 10 + c - '0';
        c = getchar();
    }
    return (unsigned char)t;
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            row[i] = getint();
        }
        //for (int i = 0; i < n; i++) scanf("%d", &row[i]);
        int ans = inf;
        ull move = 0;
        for (int i = 1; i < n; i++) {
            row[i] = result[n][row[i]][row[i - 1]];
            if (i + 1 < n) row[i + 1] ^= row[i - 1];
            move <<= n;
            move |= row[i - 1];
        }
        for (int i = 0; i < vec[n][row[n - 1]].size(); i++) {
            ans = min(ans, count(move ^ vec[n][row[n - 1]][i], n));
        }
        if (ans == inf) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
