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

const int N = 100100;

//int a[5] = {1,2,3};
vector<int> g[N];
vector<int> h[N];
LL sum[N], ans[N];
int sz[N];
int n, cas = 1;

void dfs(int u, int fa) {
    sz[u] = 1;
    sum[u] = 0;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        sum[u] += 1LL * h[u][i] * sz[v] + sum[v];
    }
    //    cout << u << ' '<< sz[u] << ' ' << sum[u] << endl;
}

void dfs2(int u, int fa, LL res) {
    ans[u] = res;
    //    cout << u << ' ' << res << endl;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs2(v, u, res + 1LL * h[u][i] * (-sz[v] * 2 + n));
    }
}

void out(__int128 x) {
    if (x<10) {putchar(x+'0'); return ;}
    out(x/10);
    putchar(x%10+'0');
}

int main () {
    //    freopen("in.txt", "r", stdin);
    int T;
    cin >> T;
    while (T--) {
        int u, v, c;
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear(), h[i].clear();
        for (int i = 1; i < n; i++) {
            scanf ("%d%d%d", &u, &v, &c);
            g[u].push_back(v);
            g[v].push_back(u);
            h[u].push_back(c);
            h[v].push_back(c);
        }
        dfs(1, 0);
        dfs2(1, 0, sum[1]);
        //        for (int i = 1; i <= n; i++)
        //            cout << ans[i] << endl;
        sort(ans + 1, ans + n + 1);
        __int128 rr = 0;
        for (int i = 1; i <= n; i++) {
            //            cout << ans[i] << endl;
            rr += ans[i] * (n - i);
        }
        printf("Case #%d: ", cas++);
        out(rr);
        cout << endl;
    }
}
