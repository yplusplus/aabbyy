#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 111;
double chps;
int n, m;
struct Laptop {
    double c, t, r;
    void read() { scanf("%lf%lf%lf", &c, &t, &r); }
} laptop[N];

bool check(double T, int k) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double delta = laptop[i].r - T * laptop[i].c / laptop[i].t;
        if (delta < 0) sum += delta;
    }
    sum += T * k * chps;
    return sum > 0;
}

int main() {
    int Case = 1;
    while (~scanf("%d%d", &n, &m), n + m) {
        scanf("%lf", &chps);
        double cps = 0;
        for (int i = 0; i < n; i++) {
            laptop[i].read();
            cps += laptop[i].c / laptop[i].t;
        }
        //cout << cps << endl;
        printf("Case %d:\n", Case++);
        printf("%d\n", (int) ceil(cps / chps));
        while (m--) {
            int k;
            scanf("%d", &k);
            double l = 0, r = 1e6;
            double ans = 0;
            for (int i = 0; i < 50; i++) {
                double mid = (l + r) / 2.0;
                if (check(mid, k)) {
                    ans = mid; l = mid;
                } else r = mid;
            }
            if (ans > 1e5) puts("-1.000");
            else printf("%.10f\n", ans); 
        }
    }
    return 0;
}

