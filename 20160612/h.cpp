#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000010;
int a[N], b[N];

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(a, 0, sizeof(a));
        for (int i = 1,x; i <= n; i++) {
            scanf("%d", &x);
            a[x]++;
        }
        memset(b, 0, sizeof(b));
        for (int i = 1, x; i <= m; i++) {
            scanf("%d", &x);
            b[x]++;
        }
        for (int i = 1; i < N; i++) b[i] += b[i - 1];
        long long ans = 0;
        for (int i = 0; i < N; i++) {
            if (!a[i]) continue;
            for (int j = 1, st, ed; i + j * j < N; j++) {
                st = i + j * j - 1;
                ed = min(N, i + (j + 1) * (j + 1)) - 1;
                ans += ((long long)a[i]) * j * (b[ed] - b[st]);
            }
            for (int j = 1, st, ed; i - j * j >= 0; j++) {
                ed = i - (j + 1) * (j + 1);
                st = i - j * j;
                ans += ((long long)a[i]) * j * b[st];
                if (ed >= 0) ans -= ((long long)a[i]) * j * b[ed];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
