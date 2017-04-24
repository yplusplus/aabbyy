#include <iostream>
#include <cstring>
#include <bitset>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 50050;
bitset<N> bs[26];
char s[N], t[N];
int n, q;
bitset<N> b;

int main() {
    while (~scanf("%d%d", &n, &q)) {
        scanf("%s", s);
        for (int i = 0; i < 26; i++) bs[i].reset();
        for (int i = 0; i < n; i++) {
            bs[s[i] - 'a'].set(i);
        }
        for (int i = 0, x; i < q; i++) {
            scanf("%d%s", &x, t);
            if (x == 0) {
                int m = strlen(t);
                b.reset();
                b.flip();
                for (int j = 0; j < m; j++) {
                    b &= (bs[t[j] - 'a'] >> j);
                }
                printf("%d\n", b.count());
            } else {
                x--;
                bs[s[x] - 'a'].reset(x);
                bs[t[0] - 'a'].set(x);
                s[x] = t[0];
            }
        }
    }
    return 0;
}
