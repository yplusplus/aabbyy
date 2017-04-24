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

int n;
struct Time {
    int x, h, s;
    void read() {
        sf("%d:%d", &h, &s);
        x = h * 60 + s;
    }
    int operator-(const Time &b) {
        return x - b.x;
    }
};
int main() {
    while (~sf("%d", &n), n) {
        Time sunrise, sunset, st, en;
        int tot = 0, nightTime = 0, len;
        bool flag = true;
        REP(i, n) {
            sunrise.read();
            sunset.read();
            st.read();
            en.read();
            if (en - st > 120) {
                flag = false;
            }
            len = en - st;
            tot += len;
            if (en.x <= sunrise.x || st.x >= sunset.x) {
                nightTime += len;
                continue;
            }
            if (st.x <= sunrise.x && (sunrise - st) * 2 >= len) {
                nightTime += len;
                continue;
            }
            if (en.x >= sunset.x && (en - sunset) * 2 >= len) {
                nightTime += len;
                continue;
            }
        }
        if (!flag) puts("NON");
        else {
            if (tot >= 3000 && nightTime >=600) {
                puts("PASS");
            }
            else {
                puts("NON");
            }
        }

    }
    return 0;
}


