#include <bits/stdc++.h>
using namespace std;

const int N = 8 * 8 * 8 * 8 * 8 + 10;
bool visit[N];
double dp[N];
double a[15][35];
int n,m,flag[35];
int base,ut;
int ep[15];
int cnt;
int ST[N];
int c[N];
bool rt_st[N];

void update(double &x,double y)
{
    if(x < y) x = y;
}

void dfs(int b[],int state,int step,int pos)
{
    if(!step) {
        if(rt_st[state]) ST[cnt ++] = state;
        return;
    }
    if(pos == n - 1) { 
        if(b[pos] + step <= ut) {
            b[pos] += step;
            dfs(b,state + step * ep[pos],0,pos + 1);
            b[pos] -= step;
        }
        return;
    }
    for(int i = 0; b[pos] + i <= ut && i <= step; i ++) {
        b[pos] += i;
        dfs(b,state + ep[pos] * i,step - i,pos + 1);
        b[pos] -= i;
    }
}

void get_state(int b[],int state,int step)
{
    dfs(b,state,step,0);
}
    
bool check(int state) { return rt_st[state]; } 

double dfs(int state)
{
    if(!check(state)) return 0;
    if(visit[state]) return dp[state];
    visit[state] = 1;
    int b[10];
    int x = state,tot = 0;
    for(int i = n - 1; i >= 0; i --) {
        b[i] = x % base;
        x /= base;
        tot += b[i];
    }
    if(tot == m) return dp[state] = 0;
    /*
    if(tot + 1 == m) {
        for(int i = 0; i < n; i ++)
            if(b[i] + 1 <= ut && check(state + ep[i])) return dp[state + ep[i]] = a[i][m];
    }
    */
    if(!flag[tot + 2]) {
        for(int i = 0; i < n; i ++) {
            if(b[i] + 1 <= ut && check(state + ep[i])) update(dp[state],dfs(state + ep[i]) + a[i][tot + 1]);
        }
        return dp[state];
    }
    int tmp = tot + 2;
    while(flag[tmp]) tmp ++;
    for(int i = 0; i < n; i ++) {
        if(b[i] + 1 <= ut && check(state + ep[i])) {
            double sum1 = dfs(state + ep[i]);
            b[i] ++;
            cnt = 0;
            get_state(b,state + ep[i],tmp - (tot + 2));
            b[i] --;
            double sum2 = 0;
            for(int j = 0; j < cnt; j ++) {
                if(check(ST[j])) sum2 = max(sum2,dfs(ST[j]));
            }
            update(dp[state],sum1 * a[i][tot + 1] + a[i][tot + 1] + sum2 * (1 - a[i][tot + 1]));
        }
    }
    return dp[state];
}
    
int get(int x,int &sum)
{
    int tot = 0;
    while(x) {
        if(x % base == ut) tot ++;
        x /= base;
        sum += x % base;
        if(x % base > ut) return 1000000000;
    }
    return tot;
}

void solve()
{
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    ut = m % n == 0 ? m / n : m / n + 1;
    base = ut + 1;
    memset(flag,0,sizeof(flag));
    memset(visit,0,sizeof(visit));
    memset(rt_st,false,sizeof(rt_st));
    int mul = 1;
    for(int i = 0; i < n; i ++) mul *= base;
    int left = m % n;
    if(!left) left = n;
    for(int i = 0; i < mul; i ++) {
        int sum = 0;
        rt_st[i] = get(i,sum) <= left;
        rt_st[i] &= sum <= m;
    }
    int tmp,x;
    scanf("%d",&tmp);
    while(tmp --) {
        scanf("%d",&x);
        flag[x] = 1;
    }
    ep[n - 1] = 1;
    for(int i = n - 2; i >= 0; i --)
        ep[i] = ep[i + 1] * base;
    for(int i = 0; i < n; i ++)
        for(int j = 1; j <= m; j ++)
            scanf("%lf",&a[i][j]);
    printf("%.4lf\n",dfs(0));
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case %d: ",cas);
        solve();
    }
    return 0;
}

