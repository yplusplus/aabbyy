#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int state[(10 << 10) + 5][3];
const int H = 0;
const int V = 1;
const int S = 2;

int main() {
    freopen("automata.in", "r", stdin);
    freopen("automata.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int bad = n << n;
    int all = (n << n) + 1;
    for (int i = 0; i < 3; i++) {
        state[bad][i] = bad;
    }
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            int now = (i << n) | mask;
            int ni = (i + 1) % n;
            if (mask >> i & 1) {
                state[now][H] = bad;
            } else {
                state[now][H] = (ni << n) | mask | (1 << i);
            }
            if (ni == 0 || (mask >> i & 1) || (mask >> ni & 1)) {
                state[now][V] = bad;
            } else {
                state[now][V] = (ni << n) | mask | (1 << ni);
            }
            if (~mask >> i & 1) {
                state[now][S] = bad;
            } else {
                state[now][S] = (ni << n) | (mask ^ (1 << i));
            }
        }
    }
    printf("%d %d\n", (n << n) + 1, 1);
    printf("%d %d\n", 1, 1);
    for (int mask = 0; mask < all; mask++) {
        for (int i = 0; i < 3; i++) {
            printf("%d%c", state[mask][i] + 1, i == 2 ? '\n' : ' ');
        }
    }
    return 0;
}
