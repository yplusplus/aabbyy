#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int N = 50010;
char s[N];
int n;
int pre[N];
int a[N];
int first[N][3];
unsigned long long hashs[N];
unsigned long long pows[N];

void init() {
    int vis[3];
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        pre[i] = vis[s[i] - 'a'];
        a[i] = i - pre[i];
        hashs[i] = hashs[i - 1] + a[i] * pows[i];
        vis[s[i] - 'a'] = i;
    }

    first[n + 1][0] = first[n + 1][1] = first[n + 1][2] = n + 1;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 3; j++)
            first[i][j] = first[i + 1][j];
        first[i][s[i] - 'a'] = i;
    }
}

int get_letter(int x, int y) {
    if (y > n) return 0;
    if (pre[y] < x) return y - x + 1;
    else return a[y];
}

unsigned long long get_hash(int x, int len) {
    unsigned long long ans = hashs[x + len - 1] - hashs[x - 1];
    for (int i = 0; i < 3; i++) {
        if (first[x][i] >= x + len) continue;
        int pos = first[x][i];
        ans -= a[pos] * pows[pos];
        ans += get_letter(x, pos) * pows[pos];
    }
    return ans;
}

int get_lcp(int x, int y) {
    if (x > y) swap(x, y);
    int lt = 1, rt = n - y + 1, mid, lcp = 0;
    while (lt <= rt) {
        mid = (lt + rt) >> 1;
        if (get_hash(x, mid) * pows[y - x] == get_hash(y, mid)) lcp = mid, lt = mid + 1;
        else rt = mid - 1;
    }
    return lcp;
}

bool cmp(int x, int y) {
    int lcp = get_lcp(x, y);
    return get_letter(x, x + lcp) < get_letter(y, y + lcp);
}

int rak[N];
unsigned long long key = 1000007;

int main()
{
    pows[0] = 1;
    for (int i = 1; i < N; i++)
        pows[i] = pows[i - 1] * key;

    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        a[n + 1] = 0;
        init();
        //cout << get_lcp(1, 2) << " " << get_hash(1, 1) * key << " " << get_hash(2, 1) << endl;
        for (int i = 1; i <= n; i++) rak[i] = i;
        sort(rak + 1, rak + n + 1, cmp);
        long long ans = 0;
        for (int i = 1; i <= n; i++)
            if (i == 1) ans += n - rak[i] + 1;
            else {
                int lcp = get_lcp(rak[i], rak[i - 1]);
                ans += (n - rak[i] + 1) - lcp;
            }

        printf("%lld\n", ans);
    }
    return 0;
}
