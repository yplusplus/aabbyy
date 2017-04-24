#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 100010;
struct point
{
    int flag,x;
    point() {}
    point(int x,int flag):x(x),flag(flag) {}
}a[N * 2];

int b[N],c[N];
void unions(int n,int m)
{
    int ct = 0;
    int i = 1, j = 1;
    while(i <= n && j <= m) {
        if(b[i] <= c[j]) {
            a[++ ct] = point(b[i ++],0);
        }
        else {
            a[++ ct] = point(c[j ++],1);
        }
    }
    while(i <= n) a[++ ct] = point(b[i ++],0);
    while(j <= m) a[++ ct] = point(c[j ++],1);
}

double pre[N * 2],nxt[N * 2];

void solve(int n,int xx,int yy)
{
    if(n == 2) {
        printf("0.00\n");
        return;
    }
    double x = 1.0 * (xx - yy) * (xx - yy);
    double ans = 0;
    int i = 1;
    if(a[1].flag) {
        while(i <= n && a[i].flag) i ++;
        for(int j = 1; j < i; j ++)
            ans += sqrt(x + 1.0 * (a[j].x - a[i].x) * (a[j].x - a[i].x));
        i --;
    }   
    else {
        while(i <= n && !a[i].flag) i ++;
        for(int j = 1; j < i; j ++)
            ans += sqrt(x + 1.0 * (a[j].x - a[i].x) * (a[j].x - a[i].x));      
        i --;
    }  
    //cout << ans << endl;
    while(i < n) {
        int j = i + 1;
        while(j <= n && a[j].flag != a[i].flag) j ++;
        if(j > n) {
            for(int k = i + 2; k <= n; k ++) {
                ans += sqrt(x + 1.0 * (a[k].x - a[i].x) * (a[k].x - a[i].x));
            }
            break;
        }
        if(i + 1 == j) {
            i ++;
            continue;
        }
        pre[i] = 0,nxt[j] = 0;
        for(int k = i + 1; k < j; k ++) {
            pre[k] = pre[k - 1] + sqrt(x + 1.0 * (a[k].x - a[i].x) * (a[k].x - a[i].x));
        }
        for(int k = j - 1; k > i; k --) {
            nxt[k] = nxt[k + 1] + sqrt(x + 1.0 * (a[k].x - a[j].x) * (a[k].x - a[j].x));
        }
        double mix = 1e30;
        for(int k = i + 1; k < j; k ++)
            mix = min(mix,pre[k] + nxt[k]);
        ans += mix;
        /*
        cout << i << " " << j << endl;
        cout << ans << " " << mix << endl;*/
        ans -= sqrt(x + 1.0 * (a[i + 1].x - a[i].x) * (a[i + 1].x - a[i].x));
        i ++;
    }   
    printf("%.2lf\n",ans);
}

int main()
{
    int t;
    int n,m,x;
    int xx,yy;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d%d",&xx,&yy);
        scanf("%d%d",&n,&m);
        for(int i = 1; i <= n; i ++)
            scanf("%d",&b[i]);
        for(int i = 1; i <= m; i ++)
            scanf("%d",&c[i]);
        unions(n,m);
        printf("Case #%d: ",cas);
        solve(n + m,xx,yy);
    }   
    return 0;
}

/*
0 1
2 3
  1 2
0     3 4
*/

