#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 111111;
using LL = long long;
using Point = pair<LL, LL>;
vector<pair<int, int> > vec[N];
vector<pair<Point, LL> > candidates[N];
Point path[N];

LL ans[N];
int n;

LL sqr(LL x) { return x * x; }

LL dfs_for_down(int u, int fa, LL fac) {
    candidates[u].clear();
    LL res = 0;
    for (auto e: vec[u]) {
        LL c = e.first;
        int v = e.second;
        if (v == fa) continue;
        LL ret = dfs_for_down(v, u, c);
        ans[u] = max(ans[u], ret);
        candidates[u].push_back({{c, ret}, v});
        LL t = ret + sqr(c - fac);
        res = max(res, t);
    }
    
    return res;
}

inline LL eval(const Point &p, LL x) {
    return p.second + sqr(p.first - x);
}

inline bool check(const Point &a, const Point &b, const Point &c) {
    return (c.second + sqr(c.first) - (b.second + sqr(b.first))) * (b.first - a.first) >=
        (b.second + sqr(b.first) - (a.second + sqr(a.first))) * (c.first - b.first);
}

void calc(vector<pair<Point, LL> > &candidates) {
    vector<Point> st;

    for (auto &can: candidates) {
        const auto &p = can.first;
        int u = can.second;
        while (st.size() >= 2) {
            const Point &latter = st[st.size() - 1];
            const Point &former = st[st.size() - 2];
            if (eval(latter, p.first) < eval(former, p.first)) { st.pop_back(); }
            else { break; }
        }
        if (!st.empty() && u > 0) {
            LL value = eval(st.back(), p.first);
            ans[u] = max(ans[u], value);
            if (value >= path[u].second) {
                path[u] = {abs(p.first), value};
            }
        }
        while (st.size() >= 2 && check(st[st.size() - 2], st[st.size() - 1], p)) { st.pop_back(); }
        st.push_back(p);
    }
}

void dfs_for_up(int u, int fa, LL fac) {

    if (path[u].first != 0) {
        candidates[u].push_back({path[u], 0});
    }

    sort(candidates[u].begin(), candidates[u].end());
    calc(candidates[u]);
    for (auto &c: candidates[u]) { c.first.first *= -1; }
    reverse(candidates[u].begin(), candidates[u].end());
    calc(candidates[u]);

    for (auto e: vec[u]) {
        if (e.second == fa) continue;
        if (path[e.second].first == 0) { path[e.second].first = e.first; }
        dfs_for_up(e.second, u, e.first);
    }
}

void solve() {

    dfs_for_down(1, 0, 0);
    dfs_for_up(1, 0, 0);

    for (int i = 1; i <= n; i++) { printf("%lld\n", ans[i]); }
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            vec[i].clear();
            ans[i] = 0;
            path[i] = {0, 0};
        }
        for (int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vec[a].push_back({c, b});
            vec[b].push_back({c, a});
        }
        solve();
    }
    return 0;
}
