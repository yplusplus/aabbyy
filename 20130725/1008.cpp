#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(),(a).end()
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define FORD(i,a,b) for (int i=(a); i>=(b); i--)
#define REP(i,b) FOR(i,0,b)
#define ll long long
#define sf scanf
#define pf printf
#define Maxn 310
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int n, m;
int a[Maxn][Maxn];
int row[Maxn][Maxn][2], col[Maxn][Maxn][2];

void init() {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    int x, y;
    REP(i, n) {
        REP(j, m) {
            //row
            x = j, y = j;
            while (x >= 0 && y < m && a[i][x] == a[i][y]) {
                row[i][j][0]++;
                x--;
                y++;
            }
            if (j + 1 < m) {
                x = j, y = j + 1;
                while (x >= 0 && y < m && a[i][x] == a[i][y]) {
                    row[i][j][1]++;
                    x--;
                    y++;
                }
            }
            
            //col
            x = i, y = i;
            while (x >= 0 && y < n && a[x][j] == a[y][j]) {
                col[i][j][0]++;
                x--;
                y++;
            }
            if (i + 1 < n) {
                x = i, y = i + 1;
                while (x >= 0 && y < n && a[x][j] == a[y][j]) {
                    col[i][j][1]++;
                    x--;
                    y++;
                }
            }
        }
    }
    /*
    cout <<"****************" <<endl;
    REP(i, n) {
        REP(j, m) {
            cout <<row[i][j][0] <<" ";
        }
        cout <<endl;
    }
    cout <<"_________________________________" <<endl;
    REP(i, n) {
        REP(j, m) {
            cout <<col[i][j][0] <<" ";
        }
        cout <<endl;
    }
    
    cout <<"****************" <<endl;
    REP(i, n) {
        REP(j, m) {
            cout <<row[i][j][1] <<" ";
        }
        cout <<endl;
    }
    cout <<"_________________________________" <<endl;
    REP(i, n) {
        REP(j, m) {
            cout <<col[i][j][1] <<" ";
        }
        cout <<endl;
    }
    */
}

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

inline int calc(int tx, int ty, int ic, int flag) {
    if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
        if (ic) {
            return row[tx][ty][flag];
        }
        else return col[tx][ty][flag];
    }
    else return -1;
}
int solve() {
    int ret = 0;
    int tx, ty;
    REP(i, n) {
        REP(j, m) {
            //odd
            int p = min(col[i][j][0], row[i][j][0]);
            for (int k = 0; k < p; k++) {
                int mi = min(min(calc(i,j-k,0,0),calc(i,j+k,0,0)), min(calc(i-k,j,1,0),calc(i+k,j,1,0)));
                if (mi < (k + 1)) break;
                ret = max(ret, 2 * k + 1);
            }
            
            //even
            p = min(col[i][j][1], row[i][j][1]);
            for (int k = 0; k < p; k++) {
                int mi = min(min(calc(i-k,j,1,1), calc(i+k+1,j,1,1)), min(calc(i,j-k,0,1), calc(i,j+k+1,0,1)));
                if (mi < (k + 1)) break;
                ret = max(ret, 2 * (k + 1));
            }
        }
    }
    return ret;
}
int main() {
    int T;
    sf("%d", &T);
    while (T--) {
        sf("%d%d", &n, &m);
        REP(i, n) {
            REP(j, m) {
                sf("%d", &a[i][j]);
            }
        }
        init();
        int ans = solve();
        pf("%d\n", ans);
    }
    return 0;
}

