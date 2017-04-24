#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int sum = 0, ma = 0;
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            sum += x;
            ma = max(ma, x);
        }
        cout << max(ma, (sum + m - 1) / m) << endl;
    }
    return 0;
}
