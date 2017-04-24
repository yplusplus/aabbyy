#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef vector<DB> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;
const DB EPS = 1e-12;
const int N = 1 << 4;
const int T = 1 << 6;
const DB BOUND = 1 << 7;

struct LP {
    int m, n;
    VI N, B;
    VVD D;
    LP(const VVD &A, const VD &b, const VD &c) :
        m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2)) {
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) D[i][j] = A[i][j];
        for (int i = 0; i < m; ++i) B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
        for (int i = 0; i < n; ++i) N[i] = i, D[m][i] = -c[i];
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        for (int i = 0; i < m + 2; ++i) {
            if (i == r) continue;
            for (int j = 0; j < n + 2; ++j) {
                if (j == s) continue;
                D[i][j] -= D[r][j] * D[i][s] / D[r][s];
            }
        }
        for (int i = 0; i < n + 2; ++i) if (i != s) D[r][i] /= D[r][s];
        for (int i = 0; i < m + 2; ++i) if (i != r) D[i][s] /= -D[r][s];
        D[r][s] = 1 / D[r][s];
        swap(B[r], N[s]);
    }
    bool simplex(int phase) {
        int x = m + phase;
        while (1) {
            int s = -1;
            for (int i = 0; i <= n; ++i) {
                if (!phase && N[i] == -1) continue;
                if (s == -1 || D[x][i] < D[x][s] || (D[x][i] == D[x][s] && N[i] < N[s])) s = i;
            }
            if (D[x][s] >= -EPS) return 1;
            int r = -1;
            for (int i = 0; i < m; ++i) {
                if (D[i][s] <= 0) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] || (D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r])) r = i;
            }
            if (r == -1) return 0;
            pivot(r, s);
        }
    }
    DB solve(VD &x) {
        int r = 0;
        for (int i = 1; i < m; ++i) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] <= -EPS) {
            pivot(r, n);
            if (!simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<DB>::infinity();
            for (int i = 0; i < m; ++i) {
                if (~B[i]) continue;
                int s = -1;
                for (int j = 0; j < n; ++j) {
                    if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
                }
                pivot(i, s);
            }
        }
        if (!simplex(0)) return numeric_limits<DB>::infinity();
        x = VD(n);
        for (int i = 0; i < m; ++i) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
} ;

VVD A;
VD b, c, x;
DB matrix[N][N];
int n;

bool check(const DB &m) {
    int K = n + 2;
    A.resize(K);
    for (int i = 0; i < K; ++i) A[i] = VD(matrix[i], matrix[i] + n);
    for (int i = 0; i < K; ++i) for (int j = 0; j < n; ++j) A[i][j] = -A[i][j];
    //for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) cerr << A[i][j] << ' '; cerr << endl; }
    b.clear();
    b.resize(K, -m);
    b[n] = 1;
    b[n + 1] = -1;
    c.clear();
    c.resize(n, 1);
    x.resize(n);
    //cerr << "Build" << endl;
    LP(A, b, c).solve(x);
    //cerr << "Solve End " << m << endl;
    //for (int i = 0; i < n; ++i) cerr << x[i] << ' '; cerr << endl;
    for (int i = 0; i < K; ++i) {
        DB sum = 0;
        for (int j = 0; j < n; ++j) sum += A[i][j] * x[j];
        if (sum <= b[i] + EPS) continue;
        return 0;
    }
    return 1;
}

int run() {
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) cin >> matrix[j][i];
            matrix[n][i] = -1;
            matrix[n + 1][i] = 1;
        }
        //cerr << "Input End" << endl;
        DB l = -BOUND, r = BOUND, m;
        for (int i = 0; i < T; ++i) {
            m = (l + r) / 2;
            if (check(m)) l = m;
            else r = m;
        }
        check(l);
        cout << m << endl;
        //cerr << check(0.6) << ' ' << check(0.5) << ' ' << check(0.1) << endl;
        //cerr << check(-1.0) << ' ' << check(-0.5) << endl;
        for (int i = 0; i < n; ++i) cout << x[i] << ' '; cout << endl;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cout << setiosflags(ios::fixed) << setprecision(10);
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    return run();
}