#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 300 + 10;
const int OFFSET = N;

const int M = 1000 + 10;
int sum[M][M];
char houses[N][N];
int ans[M];
int n, m;

int query(int x1, int y1, int x2, int y2) {
    if (x1 <= 0) x1 = 1;
    if (y1 <= 0) y1 = 1;
    if (x2 >= M) x2 = M - 1;
    if (y2 >= M) y2 = M - 1;
    return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", &houses[i][1]);
    }

    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (houses[i][j] == '1') {
                int x = i + j + OFFSET;
                int y = i - j + OFFSET;
                sum[x][y]++;
            }
        }
    }

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < M; j++) {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    
    memset(ans, 0, sizeof(ans));
    for (int k = 1; k <= n + m - 2; k++) {
        //cout << "k = " << k << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (houses[i][j] == '0') continue;
                int x = i + j + OFFSET;
                int y = i - j + OFFSET;
                //cout << i << " " << j << " " << x << " " << y << endl; 
                int cnt = query(x - k, y - k, x + k, y + k);
                //cout << cnt << endl;
                ans[k] += cnt - 1;
            }
        }
    }

    for (int i = 1; i <= n + m - 2; i++) {
        printf("%d%c", (ans[i] - ans[i - 1]) / 2, " \n"[i == n + m - 2]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}


