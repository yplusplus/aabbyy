#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int N = 100010;

int a[N];
int c[N], num[N];
int n;

int lowbit(int x) {
    return x & (-x);
}

void insert(int c[], int x, int y) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += y;
}

int query(int c[], int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

unordered_map<int, int> mp;
void solve() {
    int m;
    scanf("%d%d", &n, &m);
    mp.clear();
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mp[a[i]]++;
    }

    for (int i = 0; i <= n; i++) {
        c[i] = num[i] = 0;
    }

    for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
        insert(c, it->second, it->second);
        insert(num, it->second, 1);
    }

    int ans = -1;
    for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
        if (it->first < ans) continue;
        int tot = query(num, n) - query(num, it->second - 1);
        int sum = query(c, n) - query(c, it->second - 1);
        long long need = sum - (it->second) - 1LL * (tot - 1) * (it->second - 1);
        if (need <= m) ans = it->first;
    }

    printf("%d\n", ans);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
