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

int n, a[Maxn];
int ans;
int main() {
    while (~sf("%d", &n)) {
        REP(i, n) sf("%d", &a[i]);
        ans = 0;
        int cnt = 0, mxcnt = 0, id = 0;
        FOR(i, 1, n) {
            cnt++;
            if (cnt > mxcnt) ans = id, mxcnt = cnt; 
            if (a[i] < a[id]) id = i, cnt = 1;
        }
        pf("%d\n", ans + 1);
    }
    return 0;
}


