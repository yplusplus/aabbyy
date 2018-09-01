#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int M = 111;
vector<int> row[N];
int n, m;

void solve() {
    vector<int> c(m + 1, 0);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int x: row[i]) { c[x] = max(c[x], i); }
        vector<pair<int, int> > vec;
        vec.push_back({0, n + 1});
        long long sum = 0;
        for (int j = 1; j <= m; j++) {
            pair<int, int> x{j, c[j]};
            while (x.second > vec.back().second) {
                auto y = vec.back();
                vec.pop_back();
                sum -= 1LL * (i - y.second) * (y.first - vec.back().first);
            }
            sum += 1LL * (i - x.second) * (x.first - vec.back().first);
            vec.push_back(x);
            ans += sum;
        }
    }
    cout << ans << endl;
}

int main() {
    int T;
    int Case = 1;
    scanf("%d", &T);
    while (T--) {
        int k;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) row[i].clear();
        for (int i = 0; i < k; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            row[a].push_back(b);
        }
        printf("Case #%d: ", Case++);
        solve();
    }
    return 0;    
}
