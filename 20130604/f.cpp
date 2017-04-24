#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const double eps = 1e-8;
int a[55],b[55],k[55],n;

double f(double x) {
    double ans = 100;
    int id = 0;
    for(int i = 1; i <= n; i ++) {
        double tmp = k[i] * (x - a[i]) * (x - a[i]) + b[i];
        if(tmp < ans) {
            ans = tmp;
            id = i;
        }
    }
   // printf("fuck : %d\n",id);
    if(!id) return 1;
    for(int i = id; i <= id; i ++) {
        double tmp = 2 * k[i] * (x - a[i]);
        tmp = sqrt(tmp * tmp + 1);
        ans = tmp;
    }
    return ans;
}

double simpson(double l, double r) {
    double mid = (l + r) / 2.0;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6.0;
}

double adaptive_simpson(double l, double r) {
    double mid = (l + r) / 2.0;
    double s0 = simpson(l, r);
    double s1 = simpson(l, mid) + simpson(mid, r);
    if (fabs(s0 - s1) < eps) return s0;
    return adaptive_simpson(l, mid) + adaptive_simpson(mid, r);
}

int main() {
    int t;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++)
            scanf("%d%d%d",&k[i],&a[i],&b[i]);
        double ans = 0;
        for(double x = 0; x < 100.0; x += 0.01)
            ans += adaptive_simpson(x,x + 0.01);
        printf("%.2lf\n",ans);
    }
    return 0;
}



