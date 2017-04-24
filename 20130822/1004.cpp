#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1111111;
const int INF = 0x77777777;

int head[N], mx[N], sum[N], htop, tail[N], ttop;

int main() {
    char op[3];
    int n, x;
    while (~scanf("%d", &n)) {
        htop = ttop = 0;
        mx[0] = -INF;
        sum[0] = 0;
        while (n--) {
            scanf("%s", op);
            if (op[0] == 'I') {
                scanf("%d", &x);
                head[++htop] = x;
                sum[htop] = sum[htop - 1] + x;
                mx[htop] = max(mx[htop - 1], sum[htop]);
            }
            if (op[0] == 'L') {
                if (htop == 0) continue;
                tail[++ttop] = head[htop--];
            }
            if (op[0] == 'R') {
                if (ttop == 0) continue;
                head[++htop] = tail[ttop--];
                sum[htop] = sum[htop - 1] + head[htop];
                mx[htop] = max(mx[htop - 1], sum[htop]);
            }
            if (op[0] == 'D') {
                if (htop == 0) continue;
                htop--;
            }
            if (op[0] == 'Q') {
                scanf("%d", &x);
                printf("%d\n", mx[x]);
            }
            //for (int i = 0; i <= htop; i++) cout << sum[i] << ' '; cout << endl;
        }
    }
    return 0;
}

