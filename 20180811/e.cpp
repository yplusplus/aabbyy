#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int K = 111;
int n, m, k;
struct Road {
    int x1, x2, y1, y2;
    void read() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    }
} roads[K];


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < k; i++) {
            roads[i].read();
        }
        if (n * m % 2 == 0) {
            printf("%d\n", n * m);
        } else {
            int ans = n * m + 1;
            for (int i = 0; i < k; i++) {
                if (roads[i].x1 == roads[i].x2
                        && roads[i].y1 == roads[i].y2)
                    continue;
                int c1 = (roads[i].x1 ^ roads[i].y1) & 1;
                int c2 = (roads[i].x2 ^ roads[i].y2) & 1;
                //cout << i << endl;
                //cout << c1 << " " << c2 << endl;
                if (c1 == c2 && c1 == 0) {
                    ans = n * m;
                    break;
                }
            }
            printf("%d\n", ans);
        }

    }
    return 0;
}
