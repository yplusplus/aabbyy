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
const int mod = 1000000007;

int s, b;
int dp[111][222][222];

int dfs(int k, int n, int now) {
    int &ret = dp[k][n][now];
    if (ret != -1) return ret;
    if (k == 1) {
        ret = (n + now) >= 2 ? 0 : 1;
    }
    else {
        ret = 0;
        for (int i = 0; i <= n; i++) {
            ret += dfs(k - 1, n - i, (now + i) / 2);
            if (ret >= mod) ret -= mod;
        }
    }
    return ret;
}
int main() {
    memset(dp, -1, sizeof(dp));
    ios::sync_with_stdio(false);
    while (cin >>s >>b) {
        cout <<dfs(b - 1, s, 0) <<endl;
    }
    return 0;
}


