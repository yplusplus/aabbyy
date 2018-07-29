#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> PII;
const int N = 2005;
const int INF = 1e9 + 7;

struct Segment
{
    int l, r, w;
    bool operator<(const Segment &other) const {
        return r < other.r;
    }
}seg[N];
int n, m;
int dp[N][N];
int min_dp[N][N];

int main()
{
    int T;
    cin >> T;
    while (T --) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &seg[i].l, &seg[i].r, &seg[i].w);
        }
        sort(seg + 1, seg + n + 1);
        seg[0].l = seg[0].r = seg[0].w = 0;
        min_dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= seg[i].r; j++) min_dp[i][j] = INF;
            for (int j = 0; j < i; j++) {
                if (seg[j].r < seg[i].l - 1) continue;
                int min_w = min_dp[j][seg[i].l - 1];
                int dp = INF;
                if (seg[j].r < seg[i].l) dp = max(min_w, seg[i].w);
                else dp = max(min_w, seg[i].w + seg[j].w);
                min_dp[i][seg[j].r] = min(min_dp[i][seg[j].r], dp);
            }
            for (int j = 1; j <= seg[i].r; j++) {
                min_dp[i][j] = min(min_dp[i][j], min_dp[i][j - 1]);
            }
        }
        int ret = INF;
        for (int i = 1; i <= n; i++) {
            if (seg[i].r == m) {
                ret = min(ret, min_dp[i][m]);
            }
        }
        if (ret == INF) cout << -1 << endl;
        else cout << ret << endl;
    }
    return 0;
}
