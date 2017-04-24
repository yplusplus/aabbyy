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

const int N = 111;
vector<int> vec[N];
int cost[N];
int n;
int to[N];
vector<pii> vote;
bool visit[N];
int cnt[N];

bool cmp(const int &a, const int &b) {
    return cost[a] < cost[b];
}

int solve(int target) {
    int ans = vec[1].size();
    int anscost = 0;
    memset(visit, false, sizeof(visit));
    bool found = false;
    for (int i = 2; i <= n; i++) {
        cnt[i] = vec[i].size();
        if (vec[i].size() >= target) {
            //cout << i << endl;
            int delta = vec[i].size() - target + 1;
            //cout << target << endl;
            //cout << vec[i].size() << " " << delta << endl;
            ans += delta;
            for (int j = 0; j < delta; j++) {
                cnt[i]--;
                anscost += cost[vec[i][j]];
                visit[vec[i][j]] = true;
            }
        }
    }
    for (int i = 0; i < vote.size() && ans < target; i++) {
        if (!visit[vote[i].se]) ans++, anscost += vote[i].fi, cnt[to[vote[i].se]]--;
    }
    for (int i = 2; i <= n; i++) {
        //cout << i << " " << cnt[i] << endl;
        if (cnt[i] + 1 < target) found = true;
    }
    //cout << target << endl;
    //cout << ans << " " << anscost << endl;
        
    if (ans == target && found) return anscost;
    return inf;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) vec[i].clear();
        vote.clear();
        for (int i = 2, x; i <= n; i++) {
            cin >> x;
            vec[x].pb(i);
            to[i] = x;
        }
        for (int i = 2; i <= n; i++) {
            cin >> cost[i];
            if (to[i] != 1) {
                vote.pb(mp(cost[i], i));
            }
        }
        sort(vote.begin(), vote.end());
        for (int i = 1; i <= n; i++) {
            sort(vec[i].begin(), vec[i].end(), cmp);
        }
        int ans = inf;
        for (int i = max((int)vec[1].size(), 1); i < n; i++) {
            //cout << i << endl;
            ans = min(ans, solve(i));
        }
        cout << ans << endl;
    }
    return 0;
}
