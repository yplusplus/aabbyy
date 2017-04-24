#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
#include "sstream"
#include "assert.h"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 12;
vector<int> vec[N];
int mat[N][N];
int x[N];
int n;
set<int> ss[N][N];
vector<int> num[N];
int r, c;

void gauss(int row, int col) {
    int i , j;
    for(r = c = 0; r < row && c < col; r++, c++) {
        for(i = r ; i < row ; i ++) if(mat[i][c] != 0) break;
        if(i == row) {r--; continue;}
        if(i != r) {
            for(j = c ; j <= col ; j ++)
                swap(mat[i][j],mat[r][j]);
        }
        for(i = r + 1; i < row; i++) {
            if(mat[i][c] != 0) {
                int tmp = mat[i][c];
                for(j = c; j <= col; j++) {
                    mat[i][j] *= mat[r][c];
                    mat[i][j] -= tmp * mat[r][j];
                }
            }
        }
    }
    
    if (r < row) return;
    for(i = row - 1 ; i >= 0 ; i --) {
        if(mat[i][i] != 0) x[i] = mat[i][col] / mat[i][i];
        for(j = 0; j < i; j++) mat[j][col] -= mat[j][i] * x[i];
    }
   
}

int sum[N];
bool check(int a, int v) {
    for (int i = 0; i < a && i < r; i++) {
        if (ss[i][a + 1].find(sum[i] - v * mat[i][a]) == ss[i][a + 1].end()) return false;
    }
    return true;
}

bool dfs(int i) {
    if (i == n) return true;
    for (int j = 0; j < num[i].size(); j++) {
        if (!check(i, x[i] = num[i][j])) continue;
        for (int k = 0; k <= i; k++) sum[k] -= mat[k][i] * x[i];
        if (dfs(i + 1)) return true;
        for (int k = 0; k <= i; k++) sum[k] += mat[k][i] * x[i];
    }
    return false;
}

int main() {
    char str[500];
    while (scanf("%d", &n), n) {
        getchar();
        for (int i = 0; i < n; i++) {
            num[i].clear();
            gets(str);
            int d;
            stringstream scout;
            scout << str;
            while (scout >> d) {
                num[i].pb(d);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                if (j == n) scanf("%s", str);
                scanf("%d", &mat[i][j]);
            }
        }
        gauss(n, n);
        assert(n == r);
        if (n == r) {
            for (int i = 0; i < n; i++) {
                cout << x[i] << " ";
            }
            cout << endl;
            continue;
        }
        //n = r;
        for (int i = 0; i < n; i++) sum[i] = mat[i][n];
        for (int i = 0; i < r; i++) {
            ss[i][n].clear();
            ss[i][n].insert(0);
            for (int j = n - 1; j > i; j--) {
                ss[i][j].clear();
                for (int k = 0; k < num[i].size(); k++) {
                    for (set<int>::iterator it = ss[i][j + 1].begin(); it != ss[i][j + 1].end(); it++) {
                        ss[i][j].insert(*it + mat[i][j] * num[i][k]);
                    }
                }
            }
        }
        dfs(0);
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
