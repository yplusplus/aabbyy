#include <iostream>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 55555;
vector<pair<pair<int, int>, int> > vec[N];
vector<pair<pair<int, int>, int> > rev[N];
bool visit[N];
int fromT[N][2], fromS[N][2];
int n, m;
bool uniqueFromS[N], uniqueFromT[N];

void dfsFromT(int u) {
    if (visit[u]) return;
    visit[u] = 1;
    if (u == n) {
        fromT[u][0] = fromT[u][1] = 0;
        return;
    }
    fromT[u][0] = INT_MAX;
    fromT[u][1] = INT_MIN;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first.first, w = vec[u][i].first.second;
        dfsFromT(v);
        fromT[u][0] = min(fromT[u][0], fromT[v][0] + w);
        fromT[u][1] = max(fromT[u][1], fromT[v][1] + w);
    }
}

void dfsFromS(int u) {
    if (visit[u]) return;
    visit[u] = 1;
    if (u == 1) {
        fromS[u][0] = fromS[u][1] = 0;
        return;
    }
    fromS[u][0] = INT_MAX;
    fromS[u][1] = INT_MIN;
    for (int i = 0; i < rev[u].size(); i++) {
        int v = rev[u][i].first.first, w = rev[u][i].first.second;
        dfsFromS(v);
        fromS[u][0] = min(fromS[u][0], fromS[v][0] + w);
        fromS[u][1] = max(fromS[u][1], fromS[v][1] + w);
    }
}

void solve() {
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= n; i++) dfsFromS(i);
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= n; i++) dfsFromT(i);
    bool found = false;
    for (int i = 1; i <= n; i++) {
        uniqueFromS[i] = fromS[i][0] == fromS[i][1];
        uniqueFromT[i] = fromT[i][0] == fromT[i][1];
        if (!uniqueFromS[i] && !uniqueFromT[i]) {
            found = true;
            break;
        }
    }
    if (found) {
        puts("No solution");
        return;
    }
    int maxLength = fromS[n][1];
    int ans[N] = {0};
    int modifyCnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            int v = vec[i][j].first.first;
            int w = vec[i][j].first.second;
            int edgeId = vec[i][j].second;
            if (uniqueFromS[i] && !uniqueFromS[v]) {
                ans[edgeId] = maxLength - fromS[i][0] - fromT[v][0] - w;
                modifyCnt += ans[edgeId] > 0;
            }
        }
    }
    printf("%d %d\n", modifyCnt, maxLength);
    for (int i = 0; i < m; i++) {
        if (ans[i]) {
            printf("%d %d\n", i + 1, ans[i]);
        }
    }
}

int main() {
    int Case = 1;
    ios::sync_with_stdio(false);
    while (cin >> n >> m, n && m) {
        for (int i = 1; i <= n; i++) { vec[i].clear(); rev[i].clear(); }
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            vec[a].push_back(make_pair(make_pair(b, c), i));
            rev[b].push_back(make_pair(make_pair(a, c), i));
        }
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
