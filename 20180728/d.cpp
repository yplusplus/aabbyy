#include <iostream>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int N = 222;
int n;
int mat[N][N];
bool visit[N][N];

void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", mat[i][j], j == n - 1 ? '\n' : ' ');
        }
    }
}

bool check() {
    vector<int> r(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[i] += mat[i][j];
            c[j] += mat[i][j];
        }
    }
    set<int> s;
    s.insert(r.begin(), r.end());
    s.insert(c.begin(), c.end());
    return s.size() == 2 * n;
}

/*
bool dfs(int x, int y, int cnt) {
    if (y == n) {
        x++, y = 0;
        set<int> s;
        for (int i = 0; i < x; i++) {
            s.insert(accumulate(&mat[i][0], &mat[i][n], 0));
        }
        if (s.size() != x) return false;
    }
    if (x == n) {
        if (check()) {
            print();
            return true;
        }
        return false;
    }
    if (visit[x][y]) {
        if (dfs(x, y + 1, cnt)) return true;
    }else {
        if (cnt > 0) {
            mat[x][y] = 0;
            if (dfs(x, y + 1, cnt - 1)) return true;
            mat[x][y] = 1;
        }
        if (dfs(x, y + 1, cnt)) return true;
    }
    return false;
}

int main() {
    while (cin >> n) {
        if (n & 1) { 
            cout << "done" << endl;
        } else {
            memset(visit, 0, sizeof(visit));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    mat[i][j] = -1;
                    visit[i][j] = 1;
                }
                for (int j = n - i - 1; j < n; j++) mat[i][j] = 1;
                mat[i][n - i - 1] = i < n / 2 ? -1 : 1;
                visit[i][n - i - 1] = 1;
            }
            dfs(0, 0, n / 2);
            cout << "done" << endl;
        }
    }
    return 0;
}
*/

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        if (n & 1) {
            puts("impossible");
            continue;
        }
        puts("possible");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) { mat[i][j] = -1; }
            for (int j = n - i - 1; j < n; j++) mat[i][j] = 1;
            mat[i][n - i - 1] = i < n / 2 ? -1 : 1;
        }
        for (int i = 1; i < n / 2; i++) { mat[i][n - i] = 0; }
        mat[n - 1][n / 2 - 1] = 0;
        assert(check());
        //cout << "success" << endl;
        print();
    }
    return 0;
}

