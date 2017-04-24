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

const int N = 222;
int mat[N][N], x[N];
int a[N];
vector<int> vec[N];
int n;
bool gauss(int row, int col) {
    int r , c , i , j;
    for(r = c = 0; r < row && c < col; r++, c++) {
        for(i = r; i < row ; i++) if (mat[i][c]) break;
        if(i == row) {r--; continue;}
        if(i != r) {
            for(j = c; j <= col; j++)
                swap(mat[i][j], mat[r][j]);
        }
        for(i = r + 1; i < row; i++) {
            if (mat[i][c]) {
                for (j = c; j <= col; j++) mat[i][j] ^= mat[r][j];
            }
        }
    }
    for(i = row - 1 ; i >= 0 ; i --) {
        if (mat[i][i]) x[i] = mat[i][col];
        else {
            if(mat[i][col] == 0) x[i] = 0;
            else return false;//нч╫Б
        }
        for(j = 0; j < i; j++) mat[j][col] ^= (x[i] * mat[j][i]);
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k, c;
        cin >> k;
        for (int j = 0; j < k; j++) cin >> c, vec[i].pb(c);
    }
    for (int i = 0; i < n; i++) cin >> a[i];
    bool found = false;
    vector<int> click;
    for (int i = 0; i < 2; i++) {
        click.clear();
        memset(mat, 0, sizeof(mat));
        memset(x, 0, sizeof(x));
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < vec[j].size(); k++) {
                mat[vec[j][k] - 1][j] = 1;
            }
            //mat[j][j] = 1;
            mat[j][n] = a[j] ^ i;
        }
        if (gauss(n, n)) {
            found = true;
            for (int i = 0; i < n; i++) {
                if (x[i]) click.pb(i + 1);
            }
            break;
        }
    }
    if (!found) cout << -1 << endl;
    else {
        cout << click.size() << endl;
        for (int i = 0; i < click.size(); i++) {
            cout << click[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
