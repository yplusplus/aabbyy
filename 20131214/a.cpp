#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
int f[1000010];

int main()
{
    int period;
    f[0] = 1,f[1] = 2;
    for(int i = 2; i <= 40000 ; i ++) {
        f[i] = 2 * (f[i - 1] + f[i - 2]) % mod;
        if(f[i] == 2 && f[i - 1] == 1) {
            period = i - 1;
            //break;
        }
    }
    int n;
    while(scanf("%d",&n) != EOF) {
        if(n == -1) break;
        int ans = 0;
        for(int i = 0; i <= n && i < period; i ++)
            ans = (ans + f[i] * f[(n - i) % period] % mod * (1 + (n - i) / period) % mod) % mod;
        printf("%d\n",ans);
        /*
        ans = 0;
        for(int i = 0; i <= n; i ++)
            ans = (ans + f[i] * f[n - i]) % mod;
        cout << ans << endl;
        */
    }
    return 0;
}

