#include <iostream>
using namespace std;

const int N = 400;
int cnt[N];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int s, t;
        cin >> s >> t;
        for (int j = s; j <= t; j++) {
            cnt[j]++;
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += cnt[i] > 0 ? 1 : 0;
    }
    cout << ans << endl;
    return 0;
}
