#include <iostream>
using namespace std;

const int N = 100000 + 10;
int a[N];

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > a[(i + 1) % n]) cnt++;
        }
        if (cnt <= 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
