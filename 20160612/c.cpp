#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 111111;
int n, m;
int v[N];

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(v, -1, sizeof(v));
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if (a + 1 != b) continue;
            if (v[b] == -1 || v[b] > c) v[b] = c;
        }
        long long ans = 0;
        for (int i = 2; i <= n; i++) {
            if (v[i] == -1) {
                ans = -1;
                break;
            }
            ans += v[i];
        }
        cout << ans << endl;
    }
    return 0;
}
