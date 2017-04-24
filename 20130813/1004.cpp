#pragma comment(linker, "/STACK:10006777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100020;
unsigned int dp[N / 2 + 50][210];
int m;
int bit[N],sum[N],p10[4 * N],map[N];
int c[N];

struct point
{
    int lt,rt,val,len;
}a[N * 4];

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    if(lt == rt) {
        a[step].val = c[lt] % m;
        a[step].len = bit[c[lt]];
        return;
    }
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    a[step].val = (a[2 * step].val * p10[a[2 * step + 1].len] + a[2 * step + 1].val) % m;
    a[step].len = a[2 * step].len + a[2 * step + 1].len;
}

int query(int lt,int rt,int step,int &len)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        len = a[step].len;
        return a[step].val;
    }
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step,len);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1,len);
    else {
        int len1,len2;
        int x = query(lt,a[2 * step].rt,2 * step,len1);
        int y = query(a[2 * step + 1].lt,rt,2 * step + 1,len2);
        len = len1 + len2;
        return (x * p10[len2] + y) % m;
    }
}

void read(int &x)
{
    char c;
    while(1) {
        c = getchar();
        if(isdigit(c)) break;
    }
    x = c - '0';
    while(1) {
        c = getchar();
        if(isdigit(c)) {
            x = 10 * x + (c - '0');
        }
        else return;
    }
}

int main()
{
    for(int i = 1; i < 10; i ++) bit[i] = 1;
    for(int i = 10; i < 100; i ++) bit[i] = 2;
    for(int i = 100; i < 1000; i ++) bit[i] = 3;
    bit[1000] = 4;
    int n;
    while(scanf("%d%d",&n,&m) != EOF) {
        sum[0] = 0;
        for(int i = 1; i <= n; i ++) {
            read(c[i]);
            c[i + n] = c[i];
        }
        for(int i = 1; i <= 2 * n; i ++) {
            sum[i] = sum[i - 1] + bit[c[i]];
        }
        p10[0] = 1;
        for(int i = 1; i <= sum[2 * n]; i ++)
            p10[i] = 10 * p10[i - 1] %  m;
        init(1,2 * n,1);
        for(int i = 0; i < m; i ++)
            dp[0][i] = 0;
        int mod = (n + 10);
        for(int i = 0; i <= 2 * n; i ++)
            map[i] = i % mod;
        long long ans = 0;
        for(int i = 1; i <= 2 * n; i ++) {
            for(int j = 0; j <= m; j ++)
                dp[map[i]][j] = 0;
            int val,len;
            if(i > n) val = query(i - n + 1,i,1,len);
            for(int j = 0; j < m; j ++) {
                int x = (j * p10[bit[c[i]]] + c[i]) % m;
                long long tmp = dp[map[i - 1]][j];
                dp[map[i]][x] += tmp;
            }
            dp[map[i]][c[i] % m] += 1;
            /*
            printf("fuck : %d\n",i);
            for(int j = 0; j < m; j ++)
                if(dp[map[i]][j]) printf("%d : %u\n",j,dp[map[i]][j]);*/
            if(i > n) {
                int x = map[i - n];
                for(int j = (c[i - n] % m); j <= (c[i - n]) % m; j ++) {
                    int y = (j * p10[len] + val) % m;
                    dp[map[i]][y] --;
                }
            }
            /*
            printf("fuck2 : %d\n",i);
            for(int j = 0; j < m; j ++)
                if(dp[map[i]][j]) printf("%d : %u\n",j,dp[map[i]][j]);*/
            if(i > n) {
                ans += dp[map[i]][0];
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

