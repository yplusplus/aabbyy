#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 30;
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int n, m;
char maz[N][N];

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool solve() {
    int num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maz[i][j] == 'F') { num++; continue; }
            int cnt = maz[i][j] - '0';
            for (int k = 0; k < 8; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (check(x, y) && maz[x][y] == 'F') cnt--;
            }
            if (cnt != 0) return false;
        }
    }
    return num < n * m;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", &maz[i]);
        //if (n == 1 && m == 1) {
            //puts(maz[0][0] == '0' ? "Well done Clark!" : "Please sweep the mine again!");
        //} else {
            puts(solve() ? "Well done Clark!" : "Please sweep the mine again!");
        //}
    }
    return 0;
}
