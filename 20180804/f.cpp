#include <bits/stdc++.h>
#define pii pair <int, int>
#define pic pair <int, char>
#define psi pair <string, int>
#define piii pair <pii, int>
#define UINT unsigned int
#define LL long long
#define xx first
#define yy second
using namespace std;

const int N = 4100;
const int mod = 998244353;
char s[N][18];

vector<int> dp[N][2], tmp, tmp2, tmp3;
vector<int> f[N];
vector<int> g[N];
int sz[N];

void print(const vector<int>& A) {
    if (A.size() == 0) printf("0\n");
    else {
        printf("%d", A.back());
        for (int i = A.size() - 2; i >= 0; i--) {
            printf("%04d", A[i]);
        }
        printf("\n");
    }
}

void mul(const vector<int>& A, const vector<int>& B, vector<int>* C) {
    C->clear();
    C->resize(A.size() + B.size() + 1);
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            (*C)[i + j] += A[i] * B[j];
        }
    }
    for (int i = 0; i < (int)C->size() - 1; ++i) {
        (*C)[i + 1] += (*C)[i] / 10000;
        (*C)[i] %= 10000;
    }
    int l = C->size();
    while (l > 0 && (*C)[l - 1] == 0) l--;
    C->resize(l);
}

void add(const vector<int>& A, const vector<int>& B, vector<int>* C) {
    C->clear();
    C->resize(max(A.size(), B.size()) + 1);
    for (int i = 0; i < C->size(); ++i) {
        int a = (i < A.size() ? A[i] : 0);
        int b = (i < B.size() ? B[i] : 0);
        (*C)[i] = a + b;
    }
    for (int i = 0; i < (int)C->size() - 1; ++i) {
        (*C)[i + 1] += (*C)[i] / 10000;
        (*C)[i] %= 10000;
    }
    int l = C->size();
    while (l > 0 && (*C)[l - 1] == 0) l--;
    C->resize(l);
}

void sub(const vector<int>& A, const vector<int>& B, vector<int>* C) {
    C->clear();
    C->resize(A.size());
    int e = 0;
    for (int i = 0; i < C->size(); ++i) {
        int a = (i < A.size() ? A[i] : 0) + e;
        int b = (i < B.size() ? B[i] : 0);
        if (a < b) {
            e = -1;
            a += 10000;
        } else {
            e = 0;
        }
        (*C)[i] = a - b;
    }
    int l = C->size();
    while (l > 0 && (*C)[l - 1] == 0) l--;
    C->resize(l);
}

bool bigger(const vector<int>& A, const vector<int>& B){
    if (A.size() != B.size()) {
        return A.size() > B.size();
    }
    for (int i = A.size() - 1; i >= 0; --i) {
        if (A[i] != B[i]) {
            return A[i] > B[i];
        }
    }
    return true;
}


void dfs(int u) {
    if (g[u].size() == 0) {
        dp[u][0].resize(1);
        dp[u][0][0] = 1;
        dp[u][1].resize(1);
        dp[u][1][0] = 1;
        sz[u] = 1;
        return;
    }
    int x = g[u][0], y = g[u][1];
    dfs(x);
    dfs(y);
    sz[u] = sz[x] + sz[y];
    dp[u][0].clear();
    dp[u][1].clear();
    vector<int> right0, right1;
    vector<int> left0, left1;

    for (int j = 0; j < 2; j++) {
        if (j == 0) {
            left0 = dp[x][0];
            sub(f[sz[x]], dp[x][0], &left1);
        } else {
            left1 = dp[x][1];
            sub(f[sz[x]], dp[x][1], &left0);
        }
        for (int k = 0; k < 2; k++) {
            if (k == 0) {
                right0 = dp[y][0];
                sub(f[sz[y]], dp[y][0], &right1);
            } else {
                right1 = dp[y][1];
                sub(f[sz[y]], dp[y][1], &right0);
            }
            for (int i = 0; i < 16; i++) if (s[u][i] == '1') {
                vector<int> tmp, tmp2, tmp3;
                if ((1 << 0) & i) {
                    mul(left0, right0, &tmp2);
                    add(tmp, tmp2, &tmp3);
                    tmp.swap(tmp3);
                }
                if ((1 << 1) & i) {
                    mul(left0, right1, &tmp2);
                    add(tmp, tmp2, &tmp3);
                    tmp.swap(tmp3);
                }
                if ((1 << 2) & i) {
                    mul(left1, right0, &tmp2);
                    add(tmp, tmp2, &tmp3);
                    tmp.swap(tmp3);
                }
                if ((1 << 3) & i) {
                    mul(left1, right1, &tmp2);
                    add(tmp, tmp2, &tmp3);
                    tmp.swap(tmp3);
                }
                if (bigger(tmp, dp[u][1])) dp[u][1] = tmp;
                sub(f[sz[u]], tmp, &tmp2);
                tmp.swap(tmp2);
                if (bigger(tmp, dp[u][0])) dp[u][0] = tmp;
            }
        }
    }
}

void w() {
    freopen("in.txt", "w", stdout);
    int T = 1;
    cout << T << endl;
    while (T--) {
        int n = 2000;
        cout << n << endl;
        for (int i = 1; i < n; i++) {
            cout << "1111111111111111\n";
        }
        for (int i = 1; i < n; i++) {
            cout << i << endl << i << endl;
        }
    }
    exit(0);
}

int main () {
    //    freopen("in.txt", "r", stdin);
    f[0].resize(1);
    f[0][0] = 1;
    for (int i = 1; i < N; i++) {
        add(f[i - 1], f[i - 1], &f[i]);
    }
    //    for (int i = 0; i < 64; i++) {
    //        print (f[i]);
    //    }
    int T, cas = 1;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i < n; i++) {
            scanf ("%s", &s[i]);
        }
        for (int i = 1; i <= 2 * n; i++) {
            g[i].clear();
        }
        int x;
        for (int i = 1; i <= 2 * n - 2; i++) {
            scanf ("%d", &x);
            g[x].push_back(i + 1);
        }
        for (int i = 1; i <= 2 * n; i++) {
            sort(g[i].begin(), g[i].end());
        }
        dfs(1);
        printf("Case #%d: ", cas++);
        print(dp[1][1]);
    }
}
