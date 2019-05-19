#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 100 + 10;
const long long MOD = 998244353;
int a[N];
int b[N];
int n, k;

long long mul(long long a, long long b) { return a * b % MOD; }

void solve() {
    for (int j = 0; j < k; j++) {
        for (int i = 0; i <= n; i++) {
            int p = n - i;
            b[i] = mul(a[i], p);
        }
        a[0] = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = b[i - 1];
        }
    }
    for (int i = 0; i <= n; i++) {
        printf("%d%c", (int)a[i], i == n ? '\n' : ' ');
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; i++) { scanf("%d", &a[i]); }
    solve();
    return 0;
}
