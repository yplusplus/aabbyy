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
#define Maxn 111111
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int n, m, a[Maxn];
ll b[Maxn*2];
int main() {
    int T, ca = 0;
    sf("%d", &T);
    while (T--) {
        sf("%d%d", &n, &m);
        FOR(i, 1, n+1) sf("%d", &a[i]);
        ll ans = 0;
        memset(b, 0, sizeof(b));
        FOR(i, 1, n+1) {
            b[i] += b[i-1];
            if (b[i] >= a[i]) continue;
            ll tmp = a[i] - b[i];
            b[i] += tmp;
            b[i+m] -= tmp;
            ans += tmp;
        }
        pf("Case #%d: %lld\n", ++ca, ans);
    }
    
    return 0;
}


