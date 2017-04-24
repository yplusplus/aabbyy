#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 55;
const int inf = 1 << 25;
int n, m;
int maz[N][N];
int color[N];
int main() {
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                maz[i][j] = inf;
            }
            maz[i][i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            char str[10];
            cin >> str;
            color[i] = str[0] == 'E';
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            if (color[a] != color[b]) {
                maz[a][b] = maz[b][a] = 1;
            } else {
                maz[a][b] = maz[b][a] = 0;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    maz[i][j] = min(maz[i][k] + maz[k][j], maz[i][j]);
                }
            }
        }
        int ans = n;
        int pos = -1;
        for (int i = 1; i <= n; i++) {
            int t = 0;
            for (int j = 1; j <= n; j++) {
                //if (i == n) cout << maz[i][j] << " ";
                t = max(t, maz[i][j]);
            }
            //cout << i << " " << t << endl;
            if (t < ans) {
                ans = t, pos = i;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < ans; i++) {
            cout << pos << " " << (color[pos] ? 'J' : 'E') << endl;
            color[pos] ^= 1;
        }
    }
    return 0;
}

