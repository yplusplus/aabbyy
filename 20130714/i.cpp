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

struct User {
    string CurrentTitle;
    ll weeks, down, up;
}u;

const string Rank[] = {"Peasant", "User", "Power_User", "Elite_User", "Crazy_User", "Insane_User", "Veteran_User", "Extreme_User", "Ultimate_User", "Nexus_Master"};

const ll needweek[] = {0, 0, 4, 8, 15, 25, 40, 60, 80, 100};
const ll midownload[] = {0, 0, 50, 120, 300, 500, 750, 1024, 1536, 3072};
const ll needrate[] = {0, 0, 105, 155, 205, 255, 305, 355, 405, 455};
const ll downrate[] = {0, 0, 95, 145, 195, 245, 295, 345, 395, 445};

map<string, int> id;

bool isPeasant() {
    if (u.down >= 5000 && u.up * 100 < u.down * 40) return true;
    if (u.down >= 10000 && u.up * 100 < u.down * 50) return true;
    if (u.down >= 20000 && u.up * 100 < u.down * 60) return true;
    if (u.down >= 40000 && u.up * 100 < u.down * 70) return true;
    if (u.down >= 80000 && u.up * 100 < u.down * 80) return true;
    return false;
}

bool ispromote(int k) {
    return u.weeks >= needweek[k] && u.down >= midownload[k] * 100 && u.up * 100 >= needrate[k] * u.down; 
}

bool isok(int k) {
    return u.up * 100 < u.down * downrate[k];
}
void check() {
    if (isPeasant()) {
        u.CurrentTitle = Rank[0];
        return ;
    }
    int now = id[u.CurrentTitle];
    for (int i = 9; i > now; i--) {
        if (ispromote(i)) {
            u.CurrentTitle = Rank[i];
            return ;
        }
    }
    for (int i = now; i > 1; --i) {
        if (!isok(i)) return;
        else u.CurrentTitle = Rank[i - 1];
    }
}

int main() {
    //freopen("i.in", "r", stdin);
    //freopen("mi.out", "w", stdout);
    int T;
    ios::sync_with_stdio(false);
    cin >>T;
    double tdown, tup;
    REP(i, 10) id[Rank[i]] = i;
    while (T--) {
        cin >>u.CurrentTitle >>u.weeks >>tdown >>tup;
        u.down = (ll)(100 * tdown);
        u.up =  (ll)(100 * tup);
        check();
        cout <<u.CurrentTitle <<endl;
    }
    return 0;
}

