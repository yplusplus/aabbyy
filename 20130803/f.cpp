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
string s;
int cnt[2];
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >>T;
    while (T--) {
        cin >>s;
        s = s + s;
        int dir = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i + 2 < s.size(); i++) {
            //if (s.substr(i, 4) == "LLRR" || s.substr(i, 4) == "RRLL") {
                //cnt[dir] |= 1;
            //}
            if (s.substr(i, 2) == "RR") {
                cnt[dir] |= 1;
            }
            dir ^= 1;
        }
        int ans = cnt[0] + cnt[1];
        cout <<2 - ans <<endl;
    }
    return 0;
}


