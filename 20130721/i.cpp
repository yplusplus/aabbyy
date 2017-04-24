#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1111111;
int a[N];
char str[N];

bool check(char a, char b) {
    if (a == '(' && b == ')') return true;
    if (a == '{' && b == '}') return true;
    if (a == '[' && b == ']') return true;
    return false;
}

int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        scanf("%s", str);
        stack<pair<char, int> > s;
        int n = strlen(str);
        for (int i = 0; i < n; i++) {
            a[i] = 0;
            if (s.empty()) s.push(mp(str[i], i));
            else {
                if (check(s.top().fi, str[i])) {
                    a[s.top().se] = a[i] = 1;
                    s.pop();
                } else {
                    s.push(mp(str[i], i));
                }
            }
        }
        int ans = 0;
        int cnt = 0;
        for (int i = 0; i < n + 2; i++) {
            if (a[i] == 1) cnt++;
            else {
                ans = max(ans, cnt);
                cnt = 0;
            }
        }
        printf("Case #%d: ", Case++);
        if (ans == 0) puts("I think H is wrong!");
        else printf("%d\n", ans);
    }
    return 0;
}
