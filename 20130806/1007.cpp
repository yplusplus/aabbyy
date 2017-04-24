#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 222;
const int M = 25;
double dp[N][2], p[N];
int val[N];
char sign[N][4];
int n;
int main() {
    int Case = 1;
    while (~scanf("%d", &n)) {
        for (int i = 0; i <= n; i++) scanf("%d", &val[i]);
        for (int i = 1; i <= n; i++) scanf("%s", sign[i]);
        for (int i = 1; i <= n; i++) scanf("%lf", &p[i]), p[i] = 1 - p[i];
        double ans = 0.0;
        for (int i = 0; i < 25; i++) {
            int bit = val[0] >> i & 1;
            memset(dp, 0, sizeof(dp));
            dp[0][bit] = 1.0;
            dp[0][bit ^ 1] = 0.0;
            for (int j = 1; j <= n; j++) {
                int v = val[j] >> i & 1;
                if (sign[j][0] == '|') {
                    if (v) {
                        dp[j][0] = dp[j-1][0] * (1 - p[j]);
                        dp[j][1] = p[j] + dp[j-1][1] * (1 - p[j]);
                    } else {
                        dp[j][0] = dp[j-1][0];
                        dp[j][1] = dp[j-1][1];
                    }
                } else if (sign[j][0] == '&') {
                    if (v) {
                        dp[j][0] = dp[j-1][0];
                        dp[j][1] = dp[j-1][1];
                    } else {
                        dp[j][0] = p[j] + dp[j-1][0] * (1 - p[j]);
                        dp[j][1] = dp[j-1][1] * (1 - p[j]);
                    }
                } else if (sign[j][0] == '^') {
                    if (v) {
                        dp[j][0] = dp[j-1][1] * p[j] + dp[j-1][0] * (1 - p[j]);
                        dp[j][1] = dp[j-1][0] * p[j] + dp[j-1][1] * (1 - p[j]);
                    } else {
                        dp[j][0] = dp[j-1][0];
                        dp[j][1] = dp[j-1][1];
                    }
                }
            }
            ans += (1 << i) * dp[n][1];
        }
        printf("Case %d:\n%.6f\n", Case++, ans);
    }
    return 0;
}

