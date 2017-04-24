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
#define all(a) (a).begin(),(a).end()
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define FORD(i,a,b) for (int i=(a); i>=(b); i--)
#define REP(i,b) FOR(i,0,b)
#define ll long long
#define sf scanf
#define pf printf
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int m, n;
struct Worker{
    int a, b;
}d[100];
int ans;
int dp[110][11][11][11][11];

int dfs(int sum, int a0, int a1, int a2, int a3) {
    if (sum <= 0) return 0;
    int &ret = dp[sum][a0][a1][a2][a3];
    if (ret != -1) return ret;
    ret = maxint;
    REP(i, n) {
        if (d[i].a == 0) continue;
        if (i == a0) {
            continue;
        }
        else if (i == a1) {
            if (d[i].b <= 1) {
                ret = min(ret, dfs(sum - d[i].a, i, a0, n, a2) + 1);
            }
        }
        else if (i == a2) {
            if (d[i].b <= 2) {
                ret = min(ret, dfs(sum - d[i].a, i, a0, a1, a2) + 1);
            }
        }
        else if (i == a3) {
            if (d[i].b <= 3) {
                ret = min(ret, dfs(sum - d[i].a, i, a0, a1, a2) + 1);
            }
        }
        else
            ret = min(ret, dfs(sum - d[i].a, i, a0, a1, a2) + 1);
    }
    ret = min(ret, dfs(sum, n, a0, a1, a2) + 1);
    return ret;
}
int main() {
    while (cin >>m >>n) {
        REP(i, n) cin >>d[i].a >>d[i].b;
        memset(dp, -1, sizeof(dp));
        ans = dfs(m, n, n, n, n);
        cout <<ans <<endl;
    }
    return 0;
}


