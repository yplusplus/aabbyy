#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct point
{
    long long x,y,tot;
    int d;
    point() {
        x = y = tot = d = 0;
    }
    point(long long x,long long y,int d):x(x),y(y),d(d) {
        tot = (y - x) / d + 1;
    }
    friend bool operator < (const point &p,const point &q) {
        return p.x < q.x;
    }
}a[N];
int cnt;

void dfs(long long n)
{
    if(n == 1) return;
    if(n == 2) {
        a[++ cnt] = point(1,1,1);
        return;
    }
    if(n & 1LL) {
        a[++ cnt] = point(2,n - 1,2);
        return;
    }
    long long x = n / 2 + 1;
    if(!(x & 1LL)) x ++;
    a[++ cnt] = point(x,n - 1,2);
    long long nn = x - 1;
    if(2 * nn == n) nn += 2;
    a[++ cnt] = point(nn / 2,n / 2,1);
    dfs(nn / 2 - 1);
}
    
int main()
{
    long long n,m;
    while(scanf("%I64d%I64d",&n,&m) != EOF) {
        cnt = 0;
        dfs(n);
        long long ans = -1;
        sort(a + 1,a + cnt + 1);
        for(int i = 1; i <= cnt; i ++) {
            if(a[i].tot < m) m -= a[i].tot;
            else {
                ans = a[i].x + (m - 1) * a[i].d;
                break;
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
