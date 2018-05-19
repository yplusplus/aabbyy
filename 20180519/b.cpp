#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <map>
using namespace std;

const int N = 1010;
char s[N], str[N];

int main()
{
    /*
    for (int n = 1; n <= 20; n++) {
        for (int a = 1; a <= n; a++) {
            int ans = 0;
            for (int h = n / 2; h <= n; h++) {
                for (int k = h; k <= n; k++) {
                    int tot = k - h;
                    for (int j = 1; j <= h; j++) {
                        tot += max(1, (h - (k - j) + (a - 1)) / a);
                    }
                    if (tot <= n) ans = h;
                }
            }
            cout << ans << " ";
        }
        cout << endl;
    }*/
    int n, a;
    while (scanf("%d%d", &n, &a) != EOF) printf("%d\n", (n + a) / 2);
    return 0;
}