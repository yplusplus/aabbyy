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
int n;
const int N = 1111;
pii rect[N];
bool cmpy(const pii &a, const pii &b) {
    if (a.se != b.se) return a.se < b.se;
    return a.fi < b.fi;
}

void handle(const vector<pii> &a, const vector<pii> &b, vector<pii> &c, int flag) {
    int p = -1;
    for (int i = 0; i < a.size(); i++) {
        if (flag) while (p + 1 < b.size() && b[p + 1].fi <= a[i].fi) p++;
        else while (p + 1 < b.size() && b[p + 1].se <= a[i].se) p++;
        if (p == -1) continue;
        if (flag) c.pb(mp(a[i].fi, a[i].se + b[p].se));
        else c.pb(mp(a[i].fi + b[p].fi, a[i].se));
    }
}

vector<pii> merge(vector<pii> &a, vector<pii> &b, int flag) {
    if (flag) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
    } else {
        sort(a.begin(), a.end(), cmpy);
        sort(b.begin(), b.end(), cmpy);
    }
    vector<pii> c, d;
    handle(a, b, c, flag);
    handle(b, a, c, flag);
    sort(c.begin(), c.end());
    int limit = inf;
    for (int i = 0; i < c.size(); i++) {
        if (c[i].se < limit) {
            limit = c[i].se;
            d.pb(c[i]);
        }
    }
    return d;
}

int main() {
    int T;
    cin >> T;
    char str[10];
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &rect[i].fi, &rect[i].se);
        }
        stack<vector<pii> > s;
        for (int i = 1; i < n << 1; i++) {
            scanf("%s", &str);
            if (isdigit(str[0])) {
                int idx;
                sscanf(str, "%d", &idx);
                vector<pii> a;
                a.pb(rect[idx]);
                if (rect[idx].fi != rect[idx].se) {
                    swap(rect[idx].fi, rect[idx].se);
                    a.pb(rect[idx]);
                }
                s.push(a);
            } else {
                vector<pii> a = s.top();
                s.pop();
                vector<pii> b = s.top();
                s.pop();
                s.push(merge(a, b, str[0] == 'H'));
            }
        }
        vector<pii> c = s.top();
        s.pop();
        ll ans = 1LL << 60;
        for (int i = 0; i < c.size(); i++) {
            ans = min(ans, 1LL * c[i].fi * c[i].se);
        } 
        cout << ans << endl;
    }
    return 0;
}
