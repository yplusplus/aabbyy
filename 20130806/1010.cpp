#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

double ans[1000010];

int main()
{
    int t,n,m,cd;
    while(scanf("%d",&t) != EOF) {
        while(t --) {
            scanf("%d%d%d",&cd,&m,&n);
            if(!cd) {
                if(m == 1) printf("%.20lf\n",n * 1.0);
                else {
                    double ans = 0;
                    double mul = 1;
                    for(int i = 1; i <= n; i ++) {
                        ans += mul;
                        mul *= m;
                    }
                    printf("%.20lf\n",ans);
                }
                continue;
            }
            if(m < n) {
                printf("%.20lf\n",0.0);
                continue;
            }
            double pre = 0;
            ans[0] = 1;
            for(int i = 1; i < n; i ++) {
                ans[i] = (pre / (m - i) + 1.0 * m / (m - i));
                pre += i * ans[i];
            }
            double anss = 0;
            for(int i = 0; i < n; i ++)
                anss += ans[i];
            printf("%.20lf\n",anss);
        }
    }
    return 0;
}

