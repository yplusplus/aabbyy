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

int n, m;
int r, c;
bool vis[50][110][2];
pii peo[3111];
pii conv(string str) {
    pii ret;
    ret.fi = str[0] - 'A' + 1;
    ret.se = atoi(str.substr(1).c_str());
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    while (cin >>r >>c) {
        if (!r && !c) break;
        memset(vis, false, sizeof(vis));
        cin >>n;
        string loc, status;
        REP(i, n) {
            cin >>loc >>status;
            pii tmp = conv(loc);
            if (status == "-") vis[tmp.fi][tmp.se][0] = true, vis[tmp.fi][tmp.se - 1][1] = true;
            else vis[tmp.fi][tmp.se][1] = true, vis[tmp.fi][tmp.se + 1][0] = true;;
        }
        cin >>m;
        REP(i, m) {
            cin >>loc;
            peo[i] = conv(loc);
        }
        sort(peo, peo + m);
        bool ans = true;
        REP(i, m) {
            if (vis[peo[i].fi][peo[i].se][0] && vis[peo[i].fi][peo[i].se][1]) {
                ans = false;
                break;
            }
            if (!vis[peo[i].fi][peo[i].se][0]) {
                vis[peo[i].fi][peo[i].se][0] = true;
                continue;
            }
            if (!vis[peo[i].fi][peo[i].se][1]) {
                vis[peo[i].fi][peo[i].se][1] = true;
                vis[peo[i].fi][peo[i].se + 1][0] = true;
                continue;
            }
        }
        if (ans) cout <<"YES" <<endl;
        else cout <<"NO" <<endl;
    }
    return 0;
}


