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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 505;
map<string, int> color_id;
string color_name[N];
vector<pair<int, int> > vec[N];
map<int, double> dp[N][N];
int tot;
int r, n;
bool visit[N][N];

int get_id(const string &color) {
    if (color_id.count(color)) return color_id[color];
    color_id[color] = ++tot;
    color_name[tot] = color;
    return tot;
}

void dfs(int l, int r) {
    if (visit[l][r]) return;
    visit[l][r] = true;
    for (int k = l; k < r; k++) {
        dfs(l, k); dfs(k + 1, r);
        if (dp[l][k].empty() || dp[k + 1][r].empty()) continue;
        for (map<int, double>::iterator it = dp[l][k].begin(); it != dp[l][k].end(); it++) {
            int id = it->first;
            double lp = it->second;
            for (int i = 0; i < vec[id].size(); i++) {
                if (dp[k + 1][r].count(vec[id][i].first)) {
                    double rp = dp[k + 1][r][vec[id][i].first];
                    if (dp[l][r].count(vec[id][i].second) == 0) dp[l][r][vec[id][i].second] = lp * rp;
                    else dp[l][r][vec[id][i].second] = max(dp[l][r][vec[id][i].second], lp * rp);
                }
            }
        }
    }
}

int main() {
    char str[100];
    bool flag = false;
    while (~scanf("%d", &r)) {
        if (flag) puts("");
        else flag = true;
        tot = 0;
        color_id.clear();
        for (int i = 0; i < 3 * r; i++) vec[i].clear();
        for (int i = 0; i < r; i++) {
            scanf("%s", str); int u = get_id(str);
            scanf("%s", str); int v = get_id(str);
            scanf("%s", str); int w = get_id(str);
            vec[u].push_back(make_pair(v, w));
            vec[v].push_back(make_pair(u, w));
        }
        int T;
        scanf("%d", &T);
        while (T--) {
            scanf("%d", &n);
            for (int i = 1; i <= n; i++) {
                for (int j = i; j <= n; j++) {
                    dp[i][j].clear();
                    visit[i][j] = false;
                }
                visit[i][i] = true;
            }
            for (int i = 1; i <= n; i++) {
                while (~scanf("%s", str) && strcmp(str, "END")) {
                    double p;
                    scanf("%lf", &p);
                    dp[i][i][get_id(str)] += p;
                }
            }
            dfs(1, n);
            if (dp[1][n].empty()) {
                puts("GAMEOVER");
            } else {
                double p = -1;
                int id = -1;
                for (map<int, double>::iterator it = dp[1][n].begin(); it != dp[1][n].end(); it++) {
                    if (p < it->second) p = it->second, id = it->first;
                }
                printf("%s\n", color_name[id].c_str());
            }
        }
    }
    return 0;
}
