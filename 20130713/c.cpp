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
int ans[222][222];
int main() {
    ios::sync_with_stdio(false);
    while (cin >>n) {
        n = 2 * n + 1;
        FOR(i, 1, n + 1) {
            int k = i - 1;
            FOR(j, 1, n + 1) {
                ans[i][j] = k++;
                if (i == j) ans[i][j] = 0;
                if (k > n) k = 1;
            }
        }
        FOR(i, 1, n + 1) {
            FOR(j, 1, n + 1) {
                cout <<ans[i][j];
                if (j == n) cout <<endl;
                else cout <<" ";
            }
        }
    }
    return 0;
}


