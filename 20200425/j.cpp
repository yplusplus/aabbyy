#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 3;
int a[N][N];
int b[N][N];

const vector<vector<pair<int, int>>> rot = {{{0, 1}, {1, 2}, {2, 1}, {1, 0}}, {{0, 0}, {0, 2}, {2, 2}, {2, 0}}};

void rotate() {
    memcpy(b, a, sizeof(a));
    for (int j = 0; j < 2; j++) {
        const vector<pair<int, int> > r = rot[j];
        for (int i = 0; i < 4; i++) {
            int nx = r[(i + 3) % 4].first;
            int ny = r[(i + 3) % 4].second;
            int x = r[i].first;
            int y = r[i].second;
            a[x][y] = b[nx][ny];
        }
    }
}

const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

int main() {
    int T;
    cin >> T;
    while (T--) {
        string str;
        cin >> str;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = str[i * N + j] - '0';
            }
        }
        int ans = 1 << 30;
        for (int i = 0; i < 4; i++) {
            int res = 0;
            for (int i = 0; i < 8; i++) {
                int t = a[1][1] ^ a[1 + dx[i]][1 + dy[i]];
                if (t > 0) {
                    res += (t << (7 - i));
                }
            }
            ans = min(ans, res);
            rotate();
        }
        cout << ans << endl;
    }
    return 0;
}
