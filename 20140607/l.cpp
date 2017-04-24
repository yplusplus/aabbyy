#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
long long a[N],b[N];
bool visx[N],visy[N];
bool cmp(long long x,long long y)
{
    return x > y;
}
int main()
{
    int n,m,cas = 0;
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 1; i <= n; i ++) scanf("%lld",&a[i]);
        for(int i = 1; i <= m; i ++) scanf("%lld",&b[i]);
        sort(a + 1,a + n + 1,cmp);
        sort(b + 1,b + m + 1,cmp);
        for(int i = n + 1; i <= max(n,m) + 5; i ++) a[i] = 0;
        for(int i = m + 1; i <= max(n,m) + 5; i ++) b[i] = 0;

        memset(visx,0,sizeof(visx));
        memset(visy,0,sizeof(visy));
        int i = 1,j = 1;
        int ii = 2,jj = 2;
        bool flag = false;
        while(i <= n && j <= m) {
            while(i <= n && visx[i]) i ++;
            while(j <= m && visy[j]) j ++;
            if(i > n || j > m) break;
            ii = max(ii,i + 1);
            jj = max(jj,j + 1);
            ii = min(ii,n + 1);
            jj = min(jj,m + 1);
            while(ii <= n && visx[ii]) ii ++;
            while(jj <= m && visy[jj]) jj ++;
            if(a[i] + a[ii] > b[j] + b[jj]) {
                flag = true;
                break;
            }
            if(a[i] < b[j]) {
                a[i] += a[ii];
                visx[ii ++] = true;
            }
            else if(a[i] > b[j]) {
                j ++;
                if(j > m) {
                    flag = true;
                    break;
                }
            }
            else visy[jj ++] = 1;
            while(j <= m && visy[j]) j ++;
            ii = max(ii,i + 1);
            jj = max(jj,j + 1);
            ii = min(ii,n + 1);
            jj = min(jj,m + 1);
            while(ii <= n && visx[ii]) ii ++;
            while(jj <= m && visy[jj]) jj ++;
            while(jj <= m && visy[jj]) jj ++;
            if(b[j] + b[jj] > a[i] + a[ii]) {
                break;
            }
            if(b[j] > a[i]) i ++;
            else if(b[j] < a[i]) {
                b[j] += b[jj];
                visy[jj ++] = 1;
            }
            else visx[ii ++] = 1;
        }
        printf("Case %d: ",++ cas);
        if(flag) printf("Takeover Incorporated\n");
        else printf("Buyout Limited\n");
    }
    return 0;
}


