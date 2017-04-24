#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;

int pri[40010];
int a[40010];
double dp[125][10010];
int pre[125][10010],num[125][10010];

void prime()
{
    memset(a,0,sizeof(a));
    for(int i = 2; i <= 200; i ++)
        if(!a[i])
            for(int j = i * i; j <= 40000; j += i)
                a[j] = 1;
    for(int i = 0,j = 2; j <= 40000; j ++)
        if(!a[j]) pri[++ i] = j;
}

stack<int> sta;
void get_ans(int dep,int n)
{
    if(dep == 0) {
        for(int j = 1; j <= n; j ++) {
            sta.push(1);
        }
        return;
    }
    if(n == 0) return;
    if(num[dep][n]) {
        int tmp = 1;
        for(int i = 1; i <= num[dep][n]; i ++) tmp *= pri[dep];
        sta.push(tmp);
    }
    get_ans(dep - 1,pre[dep][n]);
}
    
int aa[10010];
void output(int n)
{
    int ct = 0;
    while(!sta.empty()) {
        aa[++ ct] = sta.top();
        sta.pop();
    }
    sort(aa + 1,aa + ct + 1);
    for(int i = ct; i >= 1; i --) sta.push(aa[i]);
    /*
    while(!sta.empty()) {
        cout << sta.top() << " ";
        sta.pop();
    }
    cout << endl;*/
    int number = 0;
    while(!sta.empty()) {
        int u = sta.top();
        sta.pop();
        if(u == 1) {
            printf("%d",++ number);
            if(number == n) printf("\n");
            else printf(" ");
            continue;
        }
        for(int i = number + 2; i <= number + u; i ++) {
            printf("%d ",i);
        }
        printf("%d",number + 1);
        number += u;
        if(number == n) printf("\n");
        else printf(" ");
    }
}

void solve(int n)
{
    if(n == 1) {
        printf("1\n");
        return;
    }
    if(n == 2) {
        printf("2 1\n");
        return;
    }
    for(int i = 0; i < 125; i ++) {
        for(int j = 0; j <= n; j ++) {
            dp[i][j] = -100000000;
            pre[i][j] = -1;
        }
    }
    while(!sta.empty()) sta.pop();
    for(int i = 0; i <= n; i ++) dp[0][i] = 0;
    for(int i = 1; i <= 120; i ++) {
        double x = log(1.0 * pri[i]);
        for(int j = 0; j <= n; j ++) {
            dp[i][j] = dp[i - 1][j];
            pre[i][j] = j;
            num[i][j] = 0;
        }
        for(int j = 0; j <= n; j ++) {
            for(int k = pri[i],times = 1; j + k <= n; k *= pri[i],times ++) {
                if(dp[i][j + k] < dp[i - 1][j] + times * x) {
                    dp[i][j + k] = dp[i - 1][j] + times * x;
                    pre[i][j + k] = j;
                    num[i][j + k] = times;
                }
            }
        }
    }
    //cout << dp[120][n] << endl;
    get_ans(120,n);
    output(n);
}

            
int main()
{
    prime();
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        solve(n);
    }
    return 0;
}