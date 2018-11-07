#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool judge(const vector<int> &a, const vector<int> &b) {
    //cout << a.size() << " " << b.size() << endl;
    if (a.size() != b.size()) return true;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a, b;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        if (x > 0) a.push_back(x);
    }
    for (int i = 0, x; i < m; i++) {
        cin >> x;
        if (x > 0) b.push_back(x);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    bool win = judge(a, b);
    if (win) cout << "Alice" << endl;
    else cout << "Bob" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
