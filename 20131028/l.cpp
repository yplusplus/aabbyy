#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 111111;
int n;
ll d, a, b;
ll p[N];
int main() {
    while (cin >> n >> d >> a >> b) {
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        ll up = 0, down = 0;
        ll cnt = 0;
        for (int i = 1; i < n; i++) {
            if (p[i] == p[i - 1]) {
                up = 0, down = 0;
            } else if (p[i] > p[i - 1]) {
                up++;
                down = 0;
                ll t = min(d / p[i], up * a);
                cnt += t;
                d -= t * p[i];
            } else {
                down++;
                up = 0;
                ll t = min(cnt, down * b);
                cnt -= t;
                d += t * p[i];
            }
        }
        cout << d << " " << cnt << endl;
    }
    return 0;
}

