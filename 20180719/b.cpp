#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int N = 100010;
int a[N];

long long com(long long n, long long m = 2) {
    return n * (n - 1) / 2;
}

int main()
{
    int n, mod;
    while (scanf("%d%d", &n, &mod) != EOF) {
        a[1] = 0, a[2] = a[3] = 1;
        for (int i = 4; i <= n; i++) {
            a[i] = (1LL * a[i - 1] * (i - 1) +  1LL * (i - 1) * a[i - 2] - com(i - 1) % mod * a[i - 3]) % mod;
            if (a[i] < 0) a[i] += mod;
        }
        printf("%d\n", a[n] % mod);
    }
    return 0;
}
