#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int mod = 1000000007;
const int N = 200010;

int get_phi(int n) {
    if (n == 1) return 1;
    int ans = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i) continue;
        ans = ans / i * (i - 1);
        while (n % i == 0) n /= i;
    }

    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

int phi[55];
int cnt = 0;
vector<int> pows[N];

void add(int &x, int y, int mod) {
    x += y;
    while (x >= mod) x -= mod;
}
void init() {
    phi[cnt++] = mod;
    while (phi[cnt - 1] != 1) {
        int n = phi[cnt - 1];
        phi[cnt++] = get_phi(n);
    }

    for (int i = 0; i < cnt; i++)
        if (phi[i] <= 10000000) {
            pows[i].push_back(1);
            for (int j = 1; j < phi[i]; j++) {
                pows[i].push_back(pows[i][j - 1]);
                add(pows[i][j], pows[i][j], phi[i]);
            }
        }
}

char s[N];

int mpow(int a, int b, int mod) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1LL * ans * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

void solve() {
    scanf("%s", s);
    int ans[cnt + 1];
    for (int i = 0; i <= cnt; i++) ans[i] = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '0') {
            for (int j = 0; j < cnt; j++)
                add(ans[j], 1, phi[j]);
        } else if (s[i] == '1') {
            for (int j = 0; j < cnt; j++) {
                add(ans[j], ans[j], phi[j]);
                add(ans[j], 2, phi[j]);
            }
        } else {
            for (int j = 0; j < cnt; j++) {
                if (phi[j] > 10000000) ans[j] = (6LL  * mpow(2, ans[j + 1], phi[j]) - 3) % phi[j];
                else {
                    while (ans[j + 1] >= phi[j]) printf("1\n");
                    ans[j] = (6LL * pows[j][ans[j + 1]] - 3) % phi[j];
                }
                if (ans[j] < 0) ans[j] += phi[j];
            }
        }
    }
    printf("%d\n", ans[0]);
}

int main()
{
    init();
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
