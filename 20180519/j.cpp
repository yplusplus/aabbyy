#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int N = 111111;
int pow2[N];

int add(long long a, long long b) {
    return (a + b) % MOD;
}

int mul(long long a, long long b) {
    return (a * b) % MOD;
}

int main() {
    pow2[0] = 1;
    for (int i = 1; i < N; i++) {
        pow2[i] = add(pow2[i - 1], pow2[i - 1]);
    }
    int n;
    while (cin >> n) {
        string str;
        cin >> str;
        reverse(str.begin(), str.end());
        str.resize(n, '0');
        reverse(str.begin(), str.end());
        int cnt = 0;
        int ans = 1;
        //cout << str << endl;
        for (int i = 0; i < n; i++) {
            if (str[i] == '1') {
                ans = mul(ans, add(pow2[i], MOD - pow2[cnt]));
                cnt++;
            } else {
                ans = mul(ans, pow2[cnt]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
