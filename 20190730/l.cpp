#include <iostream>
using namespace std;

const int N = 2000000 + 50;
int minprime[N];
int prime[N], tot;
bool flag[N];

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

void init() {
    minprime[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!flag[i]) {
            prime[tot++] = i;
            minprime[i] = i;
        }

        for (int j = 0; j < tot; j++) {
            long long p = prime[j];
            if (p * i >= N) break;
            flag[p * i] = true;
            minprime[p * i] = p;
            if (i % p == 0) {
                break;
            }
        }
    }
}

int calc(int n) {
    int primes = 0;
    int res = 1;
    while (n > 1) {
        primes++;
        int cnt = 1;
        int p = minprime[n];
        while (n % p == 0) {
            n /= p;
            cnt++;
        }
        res *= cnt;
    }
    res -= primes;
    return res;
}

int main() {
    init();
    int T = read();
    while (T--) {
        int n = read();
        printf("%d\n", calc(n));
    }
    return 0;
}
