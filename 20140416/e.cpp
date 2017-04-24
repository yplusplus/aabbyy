#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int pri[N];

void prime()
{
    memset(pri,-1,sizeof(pri));
    for(int i = 2; i < N; i ++)
        if(pri[i] == -1) {
            for(int j = i; j < N; j += i)
                pri[j] = i;
        }
    pri[1] = 1;
}

int fac[55],num[55],cnt;

void factor(int n)
{
    cnt = 0;
    while(n > 1) {
        int x = pri[n];
        num[cnt] = 0;
        while(n % x == 0) n /= x,num[cnt] ++;
        fac[cnt ++] = x;
    }
}

unsigned long long dp[N],f[N];
vector<int> v[N];

int check(int x,int y)
{
    factor(x);
    int flag = -1;
    for(int i = 0; i < cnt; i ++) {
        int tot = 0;
        while(y % fac[i] == 0) y /= fac[i],tot ++;
        if(!tot) return 0;
        if(num[i] % tot) return 0;
        if(i && flag != num[i] / tot) return 0;
        flag = num[i] / tot;
    }
    return flag;
}

void init()
{
    for(int i = 2; i < N; i ++) {
        for(int j = i; j < N; j += i) {
            int flag = check(j,i);
            if(flag) v[j].push_back(flag);
        }
        
    }
}
            
int main()
{
    prime();
    init();
    dp[1] = 1;
    for(int i = 2; i < N; i ++)
        for(int j = 0; j < v[i].size(); j ++)
            dp[i] += dp[v[i][j]];
    int a,b,c;
    while(scanf("%d^%d^%d",&a,&b,&c) != EOF) {
        factor(b);
        map<int,int> ma;
        for(int i = 0; i < cnt; i ++)
            ma[fac[i]] = num[i] * c;
        factor(a);
        int gcd = 0;
        for(int i = 0; i < cnt; i ++)
            gcd = __gcd(gcd,num[i]);
        factor(gcd);
        for(int i = 0; i < cnt; i ++)
            if(!ma.count(fac[i])) ma[fac[i]] = num[i];
            else ma[fac[i]] += num[i];
        memset(f,0,sizeof(f));
        int maxn = 0;
        for(map<int,int>::iterator it = ma.begin(); it != ma.end(); it ++) {
            int times = it->second;
            maxn = max(maxn,times);
            for(int j = 1; j <= times; j ++) {
                int x = times / j;
                f[j] = f[j] + x + x * f[j];
            }
        }
        //for(int i = 1; i <= maxn; i ++) cout << i << " : " << f[i] << endl;
        //for(int i = maxn; i > 1; i --)
            //for(int j = i * 2; j <= maxn; j += i)
                //f[i] -= f[j];
        unsigned long long ans = 0;
        for(int i = 2; i <= maxn; i ++) ans += f[i] * dp[i];
        cout << ans << endl;
    }
    return 0;
}

