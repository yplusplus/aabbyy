#include <iostream>
using namespace std;

const int N = 100000 + 10;
int a[N], b[N];

bool check() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n - 2; i++) {
        if (a[i] > b[i]) return false;
        int delta = b[i] - a[i];
        a[i + 1] += delta * 2;
        a[i + 2] += delta * 3;
    }
    return a[n - 2] == b[n - 2] && a[n - 1] == b[n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        if (check()) cout << "TAK" << endl;
        else cout << "NIE" << endl;
    }
    return 0;
}
