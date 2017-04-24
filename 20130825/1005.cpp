#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int N = 15;
int mod[N], fi[N];
vector<int> ans[N];

void PRE() {
    mod[0] = 100007;
    for (int i = 1; i < N; i++) {
        int cur = 0, cnt = 0;
        map<int, int> id;
        id.clear();
        id[0] = 0;
        ans[i - 1].clear();
        ans[i - 1].push_back(0);
        while (true) {
            cur = (cur * 10 + 2) % mod[i - 1], cnt++;
            ans[i - 1].push_back(cur);
            if (id.find(cur) != id.end()) break;
            id[cur] = cnt;
        }
        mod[i] = cnt - id[cur], fi[i] = id[cur];
        //for (int j = 0, sz = ans[i - 1].size(); j < min(sz, 25); j++) cout << ans[i - 1][j] << ' '; cout << endl;
        //cout << mod[i] << ' ' << fi[i] << endl;
    }
}

int cal(int n, int r) {
    if (r < 0) return 0;
    if (r == 0) return 1;
    if (n >= 10) return (r & 1) + 1;
    int tmp = cal(n + 1, r - 1) % mod[n + 1];
    //cout << n << ' ' << r << ' ' << tmp << ' ' << ans[n].size() << ' ' << ans[n][tmp] << endl;
    if (r <= 2) return ans[n][tmp]; // 当r>2时，必定有x>4
    else if (tmp <= fi[n + 1]) return ans[n][(tmp + mod[n + 1] - fi[n + 1]) % mod[n + 1] + fi[n + 1]];
    else return ans[n][tmp % mod[n + 1]];
}

int main() {
    PRE();
    int n;
    while (cin >> n) {
        //cout << ans[0][n] << endl;
        cout << (cal(0, n - 2) * 9 + 1) % mod[0] << endl;
    }
    return 0;
}
