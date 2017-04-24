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
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 111;
int maz[N][N], ans[N][N];
int n;
bool dfs(vector<int> s) {
    if (s.size() == 0) return false;
    if (s.size() == 1) return true;
    int f = 1 << 30;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size(); j++) {
            f = min(f, maz[s[i]][s[j]]);
        }
    }
    vector<int> a, b;
    a.pb(s[0]);
    for (int i = 1; i < s.size(); i++) {
        if (maz[a[0]][s[i]] == f) b.pb(s[i]);
        else a.pb(s[i]);
    }
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (maz[a[i]][b[j]] > f) return false;
        }
    }
    ans[a[0]][b[0]] = f;
    ans[b[0]][a[0]] = f;
    return dfs(a) & dfs(b);
}

int main() {
    while (~scanf("%d", &n)) {
        vector<int> s;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &maz[i][j]);
                ans[i][j] = 0;
            }
            ans[i][i] = -1;
            s.pb(i);
        }
        if (dfs(s)) {
            puts("YES");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d%c", ans[i][j], j == n - 1 ? '\n' : ' ');
                }
            }
        } else puts("NO");
    }
    return 0;
}

