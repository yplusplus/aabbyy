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
string robot[100];
int ans;
bool alive[110];
char c[256][256];
map<char,int> id;
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >>T;
    memset(c, 0, sizeof(c));
    c['P']['R'] = 1;
    c['S']['P'] = 1;
    c['R']['S'] = 1;
    id['R'] = 0;
    id['S'] = 1;
    id['P'] = 2;
    while (T--) {
        cin >>n;
        ans = 0;
        REP(i, n) {
            cin >>robot[i];
        }
        int K = robot[0].size();
        memset(alive, true, sizeof(alive));
        int cnt[3];
        REP(i, K) {
            int tot = 0;
            memset(cnt, 0, sizeof(cnt));
            REP(j, n) {
                if (alive[j]) {
                    if (cnt[id[robot[j][i]]] == 0) ++tot; 
                    cnt[id[robot[j][i]]]++;
                }
            }
            if (tot == 2) {
                REP(j, n) {
                    if (alive[j]) {
                        REP(x, n)
                            if (x != j && alive[x]) {
                                if (c[robot[j][i]][robot[x][i]]) {
                                    continue;
                                }
                                else if (robot[j][i] != robot[x][i]) alive[j] = false;
                            }
                    }
                }
            }
            //REP(x, n) cout <<alive[x]<<" ";
            //cout <<en:w
        }
        REP(i, n) {
            if (alive[i]) {
                if (ans != 0) {
                    ans = 0;
                    break;
                }
                ans = i + 1;
            }
        }
        cout <<ans <<endl;
    }


    return 0;
}


