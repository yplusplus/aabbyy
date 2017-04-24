#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 111;
int dp[N][5][5][222];
int price[5][N];
int n, m, B, K, R, T;

struct Edge {
    int u, v, time, cost;
    void read() {
        scanf("%d%d%d%d", &u, &v, &time, &cost);
    }
};

vector<Edge> vec[N];

void check_max(int &a, int b) {
    if (a < b) a = b;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    dp[1][0][0][0] = R;
    for (int time = 0; time < T; time++) {
        for (int pos = 1; pos < n; pos++) {
            for (int bags = 0; bags <= B; bags++) {
                for (int id = 0; id < K; id++) {
                    if ((pos == 1 || pos == n) && (id != 0)) continue;
                    if (dp[pos][bags][id][time] == -1) continue;
                    int money = dp[pos][bags][id][time];
                    if (pos > 1 && pos < n && time < T) {
                        int nid = (id + 1) % K;
                        int ntime = time + 1;
                        check_max(dp[pos][bags][nid][ntime], money);
                        //sell
                        if (bags > 0) {
                            check_max(dp[pos][bags - 1][nid][ntime], money + price[nid][pos]);
                        }
                        //buy
                        if (bags < B) {
                            check_max(dp[pos][bags + 1][nid][ntime], money - price[nid][pos]);
                        }
                    }
                    for (int i = 0; i < vec[pos].size(); i++) {
                        int npos = vec[pos][i].v;
                        int nmoney = money - vec[pos][i].cost;
                        int ntime = time + vec[pos][i].time;
                        if (nmoney < 0 || ntime > T) continue;
                        check_max(dp[npos][bags][id][ntime], nmoney);
                        if (npos == 1 || npos == n) continue;
                        //sell
                        if (bags > 0) {
                            check_max(dp[npos][bags - 1][id][ntime], nmoney + price[id][npos]);
                        }
                        //buy
                        if (bags < B && nmoney >= price[id][npos]) {
                            check_max(dp[npos][bags + 1][id][ntime], nmoney - price[id][npos]);
                        }
                    }
                }
            }
        }
    }
    int ans = -1;
    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= T; j++) {
            ans = max(ans, dp[n][i][0][j]);
        }
    }
    if (ans == -1) puts("Forever Alone");
    else printf("%d\n", ans);
}

int main() {
    int _, Case = 1;
    scanf("%d", &_);
    while (_--) {
        scanf("%d%d%d%d%d%d", &n, &m, &B, &K, &R, &T);
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 0; i < K; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &price[i][j]);
            }
        }
        for (int i = 0; i < m; i++) {
            Edge edge;
            edge.read();
            vec[edge.u].push_back(edge);
        }
        printf("Case #%d: ", Case++);
        solve();
    }
    return 0;
}
