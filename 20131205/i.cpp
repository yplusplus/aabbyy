#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
const int mod = 1000003;
int c[N][N];

int main()
{
    memset(c,0,sizeof(c));
    for(int i = 0; i < N;i ++) {
        c[i][i] = c[i][0] = 1;
        for(int j = 1; j < i; j ++) { 
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    int n;
    long long a[N];
    while(scanf("%d",&n) != EOF) {
        for(int i = 1; i <= n; i ++)
            scanf("%I64d",&a[i]);
        int bit[65];
        memset(bit,0,sizeof(bit));
        for(int i = 1; i <= n; i ++) {
            for(int j = 0; j < 63; j ++) {
                if(a[i] & (1LL << j)) bit[j] ++;
            }
        }
        for(int i = 1; i <= n; i ++) {
            long long ans = 0;
            for(int j = 0; j < 63; j ++) {
                long long tot = 0;
                for(int k = 1; k <= bit[j] && k <= i; k += 2) {
                    if(n - bit[j] >= i - k) tot += (long long)c[bit[j]][k] * c[n - bit[j]][i - k];
                }
                tot %= mod;
                ans = (ans + tot  * ((1LL << j) % mod)) % mod;
            }
            printf("%I64d",ans);
            if(i == n) cout << endl;
            else printf(" " );
        }
    }
    return 0;
}

