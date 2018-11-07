#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int N = 55;
int a[N], b[N];
int g[N][N];
bool visit[N];
int n;

void dfs(int u) {
    visit[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (g[a[u]][a[v]] && !visit[v]) {
            dfs(v);
        }
    }
}

bool is_connected() {
    memset(visit, 0, sizeof(visit));
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!visit[i]) {
            cnt++;
            dfs(i);
        }
    }
    return cnt == 1;
}

void solve() {
    int ans = 0;
    if (!is_connected()) {
        ans = 1;
        bool has47 = false;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 47) has47 = true;
        }

        if (has47) {
            a[1] = 2;
        } else {
            a[1] = 47;
        }
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) {
        cout << a[i] << (" \n"[i == n]);
    }
}

int main() {
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            g[i][j] = g[j][i] = __gcd(i, j) == 1;
        }
    }
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        solve();
    }
    return 0;
}
