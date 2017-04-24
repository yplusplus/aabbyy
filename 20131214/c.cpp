#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
struct point
{
    double bi,ri,gi;
    void read() {
        scanf("%lf%lf%lf",&bi,&ri,&gi);
        bi /= 100;
        ri /= 100;
    }
}a[110];

int main()
{
    int n;
    while(scanf("%d",&n) != EOF) {
        if(n == -1) break;
        for(int i = 1; i <= n; i ++) a[i].read();
        double ans = 0,well = 1;
        while(1) {
            int id = -1;
            double maxn = -1e30;
            for(int i = 1; i <= n; i ++) {
                if(id == -1) {
                    id = i;
                    maxn = (1 - a[i].bi) * a[i].ri * a[i].gi;
                }
                else {
                    double x = (1 - a[i].bi) * a[i].ri * a[i].gi + (1 - a[i].bi) * (1 - a[id].bi) * a[id].ri * a[id].gi;
                    double y = maxn + (1 - a[id].bi) * (1 - a[i].bi) * a[i].ri * a[i].gi;
                    if(x > y) {
                        id = i;
                        maxn = (1 - a[i].bi) * a[i].ri * a[i].gi;
                    }
                }     
            }
            if(maxn < eps) break;
            ans += maxn * well;
            well *= (1 - a[id].bi);     
            a[id].gi *= (1 - a[id].ri);       
        }
        printf("%.6lf\n",ans);
    }
    return 0;
}
    


