#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        int p = 0;
        long long sum = a[0];
        while (p < n - 1) {
            long long t = sum;
            while (t > 0 && p < n - 1) {
                p++;
                sum += a[p];
                t--;
            }
            ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
