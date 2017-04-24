#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int N = 55;
string str[N][N];
bool visit[N][N];
char maz[N][N];
int n;

void solve() {
    queue<int> que;
    for (int i = 0; i < n; i++) {
        que.push(i); que.push(i);
        visit[i][i] = true;
        str[i][i] = "";
        for (int j = i + 1; j < n; j++) {
            str[i][j] = maz[i][j];
            que.push(i); que.push(j);
            visit[i][j] = true;
        }
    }
    while (!que.empty()) {
        int a = que.front(); que.pop();
        int b = que.front(); que.pop();
        visit[a][b] = false;
        if (a == 0 || b == n - 1) continue;
        for (int i = 0; i < a; i++) {
            for (int j = b + 1; j < n; j++) {
                if (maz[i][a] != maz[b][j]) continue;
                if (maz[i][a] == '*') continue;
                string tmp = maz[i][a] + str[a][b] + maz[b][j];
                if (str[i][j].length() < tmp.length() || (str[i][j].length() == tmp.length() && str[i][j] > tmp)) {
                    str[i][j] = tmp;
                    if (!visit[i][j]) {
                        visit[i][j] = true;
                        que.push(i); que.push(j);
                    }
                }
            }
        }
    }
    puts(str[0][n - 1].c_str());
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%s", maz[i]);
        solve();
    }
    return 0;
}
