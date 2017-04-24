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

int n, m;
pii cour[Maxn];
pii d[Maxn*2];
int que[Maxn], ans;
int main() {
    while (~sf("%d", &n)) {
        m = 0;
        FOR(i, 1, n + 1) {
            sf("%d%d", &cour[i].fi, &cour[i].se);
            d[m++] = mp(cour[i].fi, i);
            d[m++] = mp(cour[i].se, -i);
            cour[i] = mp(-1, i);
        }
        sort(d, d+m);
        int tail = 0;
        ans = 0;
        REP(i, m) {
            if (d[i].se > 0) {
                que[tail++] = d[i].se;
                cour[d[i].se].fi = -2;
            }
            else {
                int tmp = -d[i].se;
                if (cour[tmp].fi != -2) continue;
                ans++;
                REP(j, tail) cour[que[j]].fi = ans;
                tail = 0;
            }
        }
        pf("%d\n", ans);
        sort(cour + 1, cour + n + 1);
        FOR(i, 1, n + 1) {
            printf("%d", cour[i].se);
            if (i > n || cour[i+1].fi != cour[i].fi) puts("");
            else printf(" ");
        }
    }
    return 0;
}

