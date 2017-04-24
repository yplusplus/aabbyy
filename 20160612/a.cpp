#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct matrix {
    int a[2][2];
    matrix() {
        memset(a, 0, sizeof(a));
    }
    matrix operator * (const matrix &p) {
        matrix c; 
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++)
                   c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]);
                c.a[i][j] %= 7;
            }
        return c;
    }
}a[2017];

char s[100010];
int mod(int p) {
    int ans = 0;
    for(int i = 0; s[i]; i++) {
        ans = (10 * ans + s[i] - '0') % p;
    }
    return ans;
}
  
int main()
{
    while (scanf("%s", s) != EOF) {
        int x = mod(2016);
        if (!x) x += 2016;
        scanf("%d%d%d%d", &a[1].a[0][0], &a[1].a[0][1], &a[1].a[1][0], &a[1].a[1][1]);
        for (int i = 2; i <= x; i++) a[i] = a[i - 1] * a[1];
        printf("%d %d\n%d %d\n", a[x].a[0][0], a[x].a[0][1], a[x].a[1][0], a[x].a[1][1]);
    }
    return 0;
}