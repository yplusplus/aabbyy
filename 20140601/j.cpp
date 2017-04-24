#include <iostream>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

const int N = 1111;
char board[N][N];
int black[N][N];
int white[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m;

bool inmat(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; }

void fix(pair<long long, long long> &x) {
    long long d = __gcd(x.first, x.second);
    x.first /= d;
    x.second /= d;
}

void check_min(pair<long long, long long> &x, const pair<long long, long long> &y) {
    if (x.first * y.second > x.second * y.first) {
        x = y;
        fix(x);
    }
}

void solve() {
    int distance = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'W') {
                distance = min(distance, i + j);
                white[i][j] = 2;
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (inmat(x, y) && board[x][y] == 'W') {
                        white[i][j] = 1;
                        break;
                    }
                }
            }
        }
    }
    queue<int> que;
    que.push(n - 1); que.push(m - 1);
    memset(black, -1, sizeof(black));
    black[n - 1][m - 1] = 0;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int y = que.front(); que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (inmat(nx, ny) && black[nx][ny] == -1) {
                black[nx][ny] = black[x][y] + 1;
                if (board[nx][ny] == 'B') {
                    que.push(nx);
                    que.push(ny);
                }
            }
        }
    }
    int c = 0;
    vector<pair<int, int> > vec;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'W') {
                c += white[i][j];
                if (black[i][j] != -1) {
                    vec.push_back(pair<int, int>(black[i][j] - white[i][j], white[i][j]));
                }
            }
        }
    }
    sort(vec.begin(), vec.end());
    pair<long long, long long> trans(1 << 20, 1);
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i].first + vec[i].second;
        c -= vec[i].second;
        pair<long long, long long> tmp(sum + c, i + 1);
        fix(tmp);
        check_min(trans, tmp);
    }
    //cout << trans.first << "/" << trans.second << endl;
    pair<long long, long long> ans(1 << 20, 1);
    //cout << black[0][0] << endl;
    //cout << distance << endl;
    if (vec.size()) {
        pair<long long, long long> tmp = pair<long long, long long>(trans.first + trans.second * distance, trans.second);
        fix(tmp);
        check_min(ans, tmp);
    }
    if (black[0][0] != -1) check_min(ans, pair<long long, long long>(black[0][0], 1));
    cout << ans.first << "/" << ans.second << endl;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++) scanf("%s", board[i]);
        solve();
    }
    return 0;
}
