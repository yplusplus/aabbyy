#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
const int INF = 1e9 + 7;

int n, m;
int a[N];
struct SegTree {
    int val[N << 2];

    void Up(int rt) {
        val[rt] = min(val[rt << 1], val[rt << 1 | 1]);
    }

    void Build(int l, int r, int rt) {
        if (l == r) {
            val[rt] = a[l];
            return ;
        }
        int mid = (l + r) >> 1;
        Build(l, mid, rt << 1);
        Build(mid + 1, r, rt << 1 | 1);

        Up(rt);
    }

    void Update(int k, int l, int r, int rt) {
        if (l == r) {
            val[rt] = INF;
            return ;
        }
        int mid = (l + r) >> 1;
        if (k <= mid) {
            Update(k, l, mid, rt << 1);
        }
        else {
            Update(k, mid + 1, r, rt << 1 | 1);
        }
        Up(rt);
    }

    int Query(int k, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        if (val[rt << 1] <= k) return Query(k, l, mid, rt << 1);
        if (val[rt << 1 | 1] <= k) return Query(k,mid + 1, r, rt << 1 | 1);
        return -1;
    }
}seg;
int q, d[N];
int cnt[N], ans[N];

int main()
{
    while (cin >> n >> m) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        cin >> q;
        int mx_d = 0;
        for (int i = 0; i < q; i++) {
            scanf("%d", &d[i]);
            mx_d = max(mx_d, d[i]);
        }

        cnt[0] = 0, ans[0] = 0;
        seg.Build(1, n, 1);
        for (int i = 1; i <= mx_d; i++) {
            ans[i] = ans[i - 1];
            cnt[i] = cnt[i - 1];
            if (sum == 0) continue;
            else ans[i] += m;
            while (true) {
                int idx = seg.Query(ans[i], 1, n, 1);
                if (idx == -1) break;
                ans[i] -= a[idx];
                cnt[i] ++;
                sum -= a[idx];
                seg.Update(idx, 1, n, 1);
            }
        }
        for (int i = 0; i < q; i++) {
            int idx = d[i];
            printf("%d %d\n", cnt[idx], ans[idx]);
        }
    }
    return 0;
}

