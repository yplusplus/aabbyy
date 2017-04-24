#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 11;
const int INF = 0x77777777;
int mat[N][N], n;
typedef vector<int> VI;

VI num[N];
int getnum(int k, int &cnt) {
    int a = (n >> 1) - k, b = (n >> 1) + k;
    num[k].clear();
    for (int i = a; i < b; i++) num[k].push_back(mat[a][i]);
    for (int i = a; i < b; i++) num[k].push_back(mat[i][b]);
    for (int i = b; i > a; i--) num[k].push_back(mat[b][i]);
    for (int i = b; i > a; i--) num[k].push_back(mat[i][a]);
    //for (int i = 0; i < num[k].size(); i++) cout << num[k][i] << ' '; cout << endl;
    int d = k << 1, mx = -INF, mk = 0;
    for (int i = 0; i < d; i++) {
        int s = 0;
        for (int j = 0; j < 4; j++) s += num[k][j * d + i];
        if (s > mx) {
            mx = s;
            mk = k - abs(k - i);
        } else if (s == mx) {
            mk = min(mk, k - abs(k - i));
        }
    }
    cnt += mk;
    //cout << mk << endl;
    return mx;
}

int main() {
    //freopen("in", "r", stdin);
    ios::sync_with_stdio(0);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> mat[i][j];
        int m = n >> 1;
        int sum = mat[m][m], cnt = 0;
        for (int i = 1; i <= (n >> 1); i++) sum += getnum(i, cnt);
        cout << sum << ' ' << cnt << endl;
    }
    return 0;
}