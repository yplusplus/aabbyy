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
int n, m;
int list[N][2];

void add(int &a) {
    a++;
    if (a == n + 1) a = 1;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        if (n == m) {
            for (int i = 1; i <= m; i++) {
                printf("%d", i);
                for (int j = 1; j <= n; j++) {
                    if (j != i) printf(" %d", j);
                }
                puts("");
            }
        } else if (n > m) {
            for (int i = 1; i <= m; i++) {
                printf("%d %d", i, m + 1);
                for (int j = 1; j <= n; j++) {
                    if (j != i && j != m + 1) printf(" %d", j);
                }
                puts("");
            }
        } else {
            int q = m / n, r = m % n;
            int tot = 1;
            int cnt = 0;
            int sid = 1;
            for (int i = 1; i <= m; i++) {
                if (cnt == q + (sid <= r)) cnt = 0, sid++;
                list[i][0] = sid;
                cnt++;
            }
            int t = n - r;
            for (int i = 1; i <= m;) {
                int sid = r;
                add(sid);
                for (int j = i; j < i + q + 1; j++) {
                    if (sid == list[j][0]) add(sid);
                    list[j][1] = sid;
                    add(sid);
                }
                i += q + (list[i][0] <= r);
            }
            for (int i = 1; i <= m; i++) {
                printf("%d %d", list[i][0], list[i][1]);
                for (int j = 1; j <= n; j++) {
                    if (j != list[i][0] && j != list[i][1]) printf(" %d", j);
                }
                puts("");
            }
        }
    }
    return 0;
}

