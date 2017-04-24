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
#define Maxn 111
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int n;
string g[Maxn];
struct Tnode {
    int x, y, sum;
    bool isAcross, isSolve;
    Tnode() {}
    Tnode(int _x, int _y, int _sum, bool _isAcross):
        x(_x), y(_y), sum(_sum), isAcross(_isAcross), isSolve(false) {}
};
vector<Tnode> rules;

bool check(const Tnode &tar) {
    //cout <<endl <<tar.x <<" "<<tar.y <<" "<<tar.sum <<" "<<tar.isAcross <<endl;
    int tot = 0, s = 0;
    pii pt;
    if (tar.isAcross) {
        for (int i = tar.y; i >= 1; --i) {
            if (g[tar.x][i] == '.') {
                pt = mp(tar.x, i);
                tot++;
                continue;
            }
            if (!isdigit(g[tar.x][i])) break;
            else {
                s += g[tar.x][i] - '0';
            }
        }
        for (int i = tar.y + 1; i <= n; i++) {
            if (g[tar.x][i] == '.') {
                pt = mp(tar.x, i);
                tot++;
                continue;
            }
            if (!isdigit(g[tar.x][i])) break;
            else {
                s += g[tar.x][i] - '0';
            }    
        } 
        if (tot > 1) return false;
    }
    else {
         for (int i = tar.x; i >= 1; --i) {
            if (g[i][tar.y] == '.') {
                pt = mp(i, tar.y);
                tot++;
                continue;
            }
            if (!isdigit(g[i][tar.y])) break;
            else {
                s += g[i][tar.y] - '0';
            }
        }
        for (int i = tar.x + 1; i <= n; i++) {
            if (g[i][tar.y] == '.') {
                pt = mp(i, tar.y);
                tot++;
                continue;
            }
            if (!isdigit(g[i][tar.y])) break;
            else {
                s += g[i][tar.y] - '0';
            }    
        } 
        //cout <<tot <<"----------------" <<endl;
        if (tot > 1) return false;
    }
    if (tot == 0) return true;
    g[pt.fi][pt.se] = '0' + (tar.sum - s);
    return true;
}
void work() {
    int Tasks = rules.size();
    //cout <<Tasks <<"##" <<endl;
    while (Tasks) {
        REP(i, rules.size()) {
            if (rules[i].isSolve) continue;
            if (check(rules[i])) {
                rules[i].isSolve = true;
                Tasks--;
                break;
            }
        }
        //REP(i, rules.size()) cout <<rules[i].isSolve <<" ";
        //cout <<endl;
        //cout <<Tasks <<"........." <<endl;
        //FOR(i, 1, n+1) cout <<g[i] <<endl;
        //system("pause");
    }
    FOR(i, 1, n+1) cout <<g[i].substr(1) <<endl;
    cout <<endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin >>n;
    int nn = 0;
    int a[4], pa = 0;
    while (true) {
        if (!n) break;
        FOR(i, 1, n+1) {
            cin >>g[i];
            g[i] = "#" + g[i];
        }
        rules.clear();
        bool flag = true;
        string s;
        getline(cin, s);
        getline(cin, s);
        while (getline(cin, s)) {
            //cout <<s <<endl;
            if (s == "Down") {
                flag = false;
                continue;
            }
            stringstream strem(s);
            pa = 0;
            while (strem >>a[pa]) pa++;
            if (pa == 1) {
                nn = a[0];
                break;
            }
            else {
                rules.pb(Tnode(a[1], a[0], a[2], flag));
            }
        }
        work();
        n = nn;
    }
    return 0;
}


