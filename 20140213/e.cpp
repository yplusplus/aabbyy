#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000003;
long long fac[mod + 10],rev[mod + 10];

long long pow(long long a,long long b)
{
    long long ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long com(long long a,long long b)
{
    if(a < b) return 0;
    return fac[a] * rev[b] * rev[a - b] % mod;
}

void init()
{
    fac[0] = rev[0] = 1;
    for(int i = 1; i < mod; i ++) {
        fac[i] = fac[i - 1] * i % mod;
        rev[i] = rev[i - 1] * pow((long long)i,mod - 2) % mod;
    }
}

long long px[mod + 10],py[mod + 10],pz[mod + 10];

void solve()
{
    long long A,B,X,Y,Z;
    int a[3],b[3];
    cin >> A >> B >> X >> Y >> Z;
    for(long long tmp = A,i = 0; i < 3; i ++) {
        a[i] = tmp % mod;
        tmp /= mod;
    }
    for(long long tmp = B, i = 0; i < 3; i ++) {
        b[i] = tmp % mod;
        tmp /= mod;
    }
    px[0] = py[0] = pz[0] = 1;
    X %= mod;
    Y %= mod;
    Z %= mod;
    for(int i = 1; i < mod; i ++) {
        px[i] = px[i - 1] * X % mod;
        py[i] = py[i - 1] * Y % mod;
        pz[i] = pz[i - 1] * Z % mod;
    }
    int tx,ty;
    long long ans = 1;
    for(int i = 0; i < 3 && ans; i ++) {
        long long sum = 0;
        for(int k = max(0LL,a[i] + b[i] - mod + 1); k <= min(a[i],b[i]); k ++) {
            tx = a[i] - k,ty = b[i] - k;
            sum += com(tx + ty + k,tx) * com(ty + k,ty) * px[tx] % mod * py[ty] * pz[k] % mod;
        }
        ans *= sum % mod;
    }
    cout << ans % mod << endl;
}
    
int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t --) {
        solve();
    }
    return 0;
}


