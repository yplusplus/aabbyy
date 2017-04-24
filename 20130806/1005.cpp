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

const int N = 111111;
double value[N];
int n, m;
int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) scanf("%lf", &value[i]);
        for (int i = 0; i < m; i++) {
            int a, b;
            double c;
            scanf("%d%d%lf", &a, &b, &c);
            value[a] += c / 2;
            value[b] += c / 2;
        }
        sort(value + 1, value + n + 1);
        double ans = 0;
        for (int i = 1; i <= n; i++) {
            if (i & 1) ans -= value[i];
            else ans += value[i];
        }
        cout << (ll) ans << endl;
    }
    return 0;
}

