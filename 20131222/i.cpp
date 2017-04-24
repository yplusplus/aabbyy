#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 33;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    void read() { scanf("%d%d", &x, &y); }
    Point operator - (const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
} point[N], vec[N][N];

inline int det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) { point[i].read(); }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                vec[i][j] = point[i] - point[j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                for (int k = 0; k < n; k++) {
                    if (i == k || j == k) continue;
                    for (int l = 0; l < n; l++) {
                        if (i == l || j == l || k == l) continue;
                        int cnt = 0;
                        cnt += det(vec[k][j], vec[j][i]) > 0;
                        cnt += det(vec[l][k], vec[k][j]) > 0;
                        cnt += det(vec[i][l], vec[l][k]) > 0;
                        cnt += det(vec[j][i], vec[i][l]) > 0;
                        if (cnt == 0 || cnt == 4) ans++;// cout << i << " " << j << " " << k << " " << l << endl;
                    }
                }
            }
        }
        ans >>= 3;
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
