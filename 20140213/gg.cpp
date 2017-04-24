#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 111111;
pair<int, int> seg[N];
vector<int> v;
int n, m;
int c[N];

int get_id(int x) {
    return upper_bound(v.begin(), v.end(), x) - v.begin() - 1;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        v.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &seg[i].first, &seg[i].second);
            v.push_back(seg[i].first);
        }
        v.push_back(0);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        memset(c, 0, sizeof(c));
        for (int i = 0; i < n; i++) { c[get_id(seg[i].first)] = max(c[get_id(seg[i].first)], seg[i].second); }
        for (int i = 1; i < v.size(); i++) { c[i] = max(c[i], c[i - 1]); }
        printf("Case %d:\n", Case++);
        for (int i = 0, pos; i < m; i++) {
            scanf("%d", &pos);
            int l = 0, r = pos;
            int ans = 0;
            while (l <= r) {
                int mid = l + r >> 1;
                int t = get_id(pos - mid);
                if (c[t] - pos >= mid) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
