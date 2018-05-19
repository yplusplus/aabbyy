#include iostream
#include cstdio
#include cstring
#include algorithm
using namespace std;

const int N = 100010;
const int mod = 1000000007;

long long mpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans  a % mod;
        a = a  a % mod;
        b = 1;
    }
    return ans;
}

char s[N];
int sum[N];

int main()
{
    int n;
    while (scanf(%d%s, &n, s) != EOF) {
        for (int i = 0; i = n; i++) sum[i] = 0;
        int m = strlen(s);
        long long tot = 0;
        for (int i = 0; i  m; i++) {
            if (s[i] == '1') {
                tot += (m - i - 1), sum[m - i - 1] = 1;
            }
        } 
        for (int i = n - 2; i = 0; i--) sum[i] += sum[i + 1];
        long long ans = mpow(2, tot);
        for (int i = 0; i  m; i++) {
            if (sum[i] - sum[i + 1]) {
                ans = ans  (mpow(2, n - i - 1 - sum[i + 1]) - 1) % mod;
            }
        }
        printf(%lldn, ans);
    }
    return 0;
}