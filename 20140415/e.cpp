#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1111;
char board[N][N];
int ind[N];
vector<int> vec[N];
vector<int> bag;
bool used[N];
int n;

bool topo(int t) {
    bag.clear();
    priority_queue<int> que;
    for (int i = 0; i < n * 2; i++) {
        if (ind[i] == 0) { que.push(i); }
    }
    while (!que.empty()) {
        int u = que.top(); que.pop();
        bag.push_back(u);
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            if (--ind[v] == 0) { que.push(v); } }
    }
    return bag.size() == t;
}

void solve() {
    memset(ind, 0, sizeof(ind));
    memset(used, false, sizeof(used));
    for (int i = 0; i < 2 * n; i++) vec[i].clear();
    int t = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'X') used[n + i] = true;
            else used[j] = true;
        }
    }
    for (int i = 0; i < 2 * n; i++) {
        if (!used[i]) ind[i] = 1;
        else t++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!used[j] || !used[n + i]) continue;
            if (board[i][j] == 'X') {
                vec[n + i].push_back(j);
                ind[j]++;
            } else if (board[i][j] == 'O') {
                vec[j].push_back(n + i);
                ind[n + i]++;
            }
        }
    }
    if (!topo(t)) {
        cout << "No solution" << endl;
    } else {
        for (int i = bag.size() - 1; i >= 0; i--) {
            int u = bag[i];
            if (u < n) {
                cout << "C" << u + 1;
            } else {
                cout << "R" << u - n + 1;
            }
            if (i == 0) cout << endl;
            else cout << " ";
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> board[i];
        solve();
    }
    return 0;
}
