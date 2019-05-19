#include <iostream>
#include <cassert>
#include <set>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 100000 + 10;
int a[N];
int n;

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int cur = 1;
    vector<int> stk;
    for (int i = 1; i <= n; i++) {
        stk.push_back(a[i]);
        while (!stk.empty() && stk.back() == cur) {
            stk.pop_back();
            cur++;
        }
    }

    int ans = 1;
    if (cur < n + 1) {
        ans = 2;
    }
    cout << ans << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
