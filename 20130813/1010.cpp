#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const long long mod = 1000000007;
const int N = 300010;

long long pow(long long a,long long b)
{
    if(b < 0) return 0;
    long long ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans;
}

long long dp[300010];
long long c[300010];
int a[300010];
int pri[90010];
long long f[300010],rev[300010];

void init()
{
    f[0] = rev[0] = 1;
    for(int i = 1; i < N;i ++) {
        f[i] = f[i - 1] * i % mod;
        rev[i] = rev[i - 1] * pow(i,mod - 2) % mod;
    }
}

void prime()
{
    bool visit[90010];
    memset(visit,false,sizeof(visit));
    for(int i = 2; i <= 300; i ++)
        if(!visit[i])
            for(int j = i * i; j <= 90000; j += i)
                visit[j] = true;
    for(int i = 0, j = 2; j <= 90000; j ++)
        if(!visit[j]) pri[i ++] = j;
}

int fac[35],num[35],cnt;

void factor(int n)
{
    memset(num,0,sizeof(num));
    cnt = 0;
    for(int i = 0; pri[i] * pri[i] <= n; i ++)
        if(n % pri[i]) continue;
        else {
            fac[cnt] = pri[i];
            while(n % pri[i] == 0) n /= pri[i],num[cnt] ++;
            cnt ++;
        }
    if(n > 1) {
        fac[cnt] = n;
        num[cnt ++] = 1;
    }
}

void dfs(int x,int pos)
{
    if(pos == cnt) return;
    dfs(x,pos + 1);
    int mul = 1;
    for(int i = 1; i <= num[pos]; i ++) {
        mul *= fac[pos];
        dfs(x * mul,pos + 1);
        c[x * mul] ++;
    }
}

long long com(int n,int m)
{
    if(n < m) return 0;
    return f[n] * rev[m] % mod * rev[n - m] % mod;
}

int main()
{
    init();
    prime();
    int n,m,r;
    while(scanf("%d%d%d",&n,&m,&r) != EOF) {
        memset(c,0,sizeof(c));
        memset(dp,0,sizeof(dp));
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&a[i]);
            factor(a[i]);
            dfs(1,0);
            c[1] ++;
        }
        for(int i = m; i >= 1; i --) {
            if(n - c[i] > r) continue;
            long long tmp = pow(m / i,n - c[i]);
            tmp = tmp * com(c[i],r - (n - c[i])) % mod * pow(m / i - 1,r - (n - c[i])) % mod;
            dp[i] = tmp;
        }
        for(int i = m; i >= 1; i --) {
            for(int j = 2 * i; j <= m; j += i) {
                dp[i] -= dp[j];
                if(dp[i] < 0) dp[i] += mod;
            }
        }
        for(int i = 1; i <= m; i ++) {
            printf("%I64d",dp[i]);
            if(i == m) printf("\n");
            else printf(" ");
        }
        
    }
    return 0;
}

