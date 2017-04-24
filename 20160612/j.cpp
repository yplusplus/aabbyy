#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 111111;
vector<int> vec[N];
bool destroy[N];
int v[N], n;

int main() {
    while (~scanf("%d", &n)) {
        vector<pair<int, int> > node(n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
            node[i - 1] = make_pair(v[i], i);
            destroy[i] = false;
            vec[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        sort(node.begin(), node.end());
        long long ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            int u = node[i].second;
            for (int j = 0; j < vec[u].size(); j++) {
                ans += destroy[vec[u][j]] ? 0 : v[vec[u][j]];
            }
            destroy[u] = true;
        }
        cout << ans << endl;
    }
    return 0;
}
