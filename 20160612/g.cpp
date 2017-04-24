#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

const int N = 111111;
int a[N];
double sum[N];
double sum2[N];
int n, m;

int main() {
    while (~scanf("%d%d", &n, &m)) {
        sum[0] = sum2[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]); 
            sum[i] = a[i] + sum[i - 1];
            sum2[i] = a[i] * a[i] + sum2[i - 1];
        }
        for (int i = m; i <= n; i++) {
            double ave = (sum[i] - sum[i - m]) / m;
            double ans = (sum2[i] - sum2[i - m]) - 2.0 * ave * (sum[i] - sum[i - m]) + ave * ave * m;
            ans /= (m - 1);
            ans = pow(ans, 0.5);
            printf("%.8f\n", ans);
        }
    }
    return 0;
}
