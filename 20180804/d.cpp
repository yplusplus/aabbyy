#include <bits/stdc++.h>
#define pii pair <int, int>
#define pic pair <int, char>
#define psi pair <string, int>
#define piii pair <pii, int>
#define UINT unsigned int
#define LL long long
#define xx first
#define yy second
using namespace std;

const int N = 210000;
const int mod = 1e9 + 7;
int mx[N];

int main () {
    //    freopen("in.txt", "r", stdin);
    int T, cas = 1;
    cin >>T;
    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;
        memset (mx, 0, sizeof(mx[0]) * (m + 5));
        while (q--) {
            int x, y, z;
            scanf ("%d%d%d", &x, &y, &z);
            mx[y] = max(mx[y], z);
        }
        LL res = 0;
        for (int i = 1; i <= m; i++) {
            res += mx[i];
        }
        printf("Case #%d: %lld\n", cas++, res);
    }
}
