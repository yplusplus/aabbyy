#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int mod = 1000000007;

int mpow(int a, int b, int md) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1LL * ans * a % md;
        a = 1LL * a * a % md;
        b >>= 1;
    }
    return ans % md;
}

const int N = 100010;
int a[N], b[N], p[N];
int X[N];

struct tree {
    int lt, rt;
    long long sum, flag;
}t[N << 2];

void init(int lt, int rt, int step) {
    t[step].lt = lt;
    t[step].rt = rt;
    t[step].sum = X[rt] - X[lt - 1];
    t[step].flag = 1;
    if (lt == rt) return;

    int mid = (lt + rt) >> 1;
    init(lt, mid, step << 1);
    init(mid + 1, rt, step << 1 | 1);

    t[step].sum = t[step << 1].sum + t[step << 1 | 1].sum;
    if (t[step].sum >= mod) t[step].sum -= mod;
}

void down(int step) {
    t[step << 1].flag = t[step << 1].flag * t[step].flag % mod;
    t[step << 1 | 1].flag = t[step << 1 | 1].flag * t[step].flag % mod;

    t[step << 1].sum = t[step << 1].sum * t[step].flag % mod;
    t[step << 1 | 1].sum = t[step << 1 | 1].sum * t[step].flag % mod;

    t[step].flag = 1;
}

void mul(int lt, int rt, int step, int v) {
    if (t[step].lt == lt && t[step].rt == rt) {
        t[step].flag = t[step].flag * v % mod;
        t[step].sum = t[step].sum * v % mod;
        return;
    }
    down(step);
    if (rt <= t[step << 1].rt) mul(lt, rt, step << 1, v);
    else if (lt > t[step << 1 | 1].rt) mul(lt, rt, step << 1 | 1, v);
    else {
        mul(lt, t[step << 1].rt, step << 1, v);
        mul(t[step << 1 | 1].lt, rt, step << 1 | 1, v);
    }

    t[step].sum = t[step << 1].sum + t[step << 1 | 1].sum;
    if (t[step].sum >= mod) t[step].sum -= mod;

}

bool cmp(int x, int y) {
    return b[x] > b[y];
}

int find(int x, int n) {
    return lower_bound(X + 1, X + n + 1, x) - X;
}

int rak[N];
void solve() {
    int n;
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d%d%d", &a[i], &b[i], &x, &y);
        p[i] = 1LL * (y - x) * mpow(y, mod - 2, mod) % mod;
        X[i] = a[i];
        rak[i] = i;
    }
    ans = 1LL * (*max_element(a + 1, a + n + 1)) * (*max_element(b + 1, b + n + 1)) % mod;
    sort(rak + 1, rak + n + 1, cmp);
    sort(X + 1, X + n + 1);

    init(1, n, 1);
    rak[n + 1] = 0;
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j <= n && b[rak[i]] == b[rak[j]]) j++;
        for (int k = i; k < j; k++)
            mul(1, find(a[rak[k]], n), 1, p[rak[k]]);
        ans = (ans - 1LL * (b[rak[i]] - b[rak[j]]) * t[1].sum) % mod;
        i = j;
    }
    if (ans < 0) ans += mod;
    printf("%lld\n", ans);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
