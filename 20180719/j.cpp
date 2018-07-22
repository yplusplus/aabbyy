#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int N = 100005;
const int mod = 1e9 + 7;

int n, q;
int a[N];
int L[N], R[N];
vector<PII> query[N];
int ans[N];

struct SegTree {
    int val[N << 2];
    void Build(int L, int R, int rt) {
        val[rt] = 0;
        if (L == R) return ;
        int mid = (L + R) >> 1;
        Build(L, mid, rt << 1);
        Build(mid + 1, R, rt << 1 | 1);
    }

    void Update(int k, int c, int L, int R, int rt) {
        if (L == R) {
            val[rt] += c;
            return ;
        }

        int mid = (L + R) >> 1;
        if (k <= mid) Update(k, c, L, mid, rt << 1);
        else Update(k, c, mid + 1, R, rt << 1 | 1);

        val[rt] = val[rt << 1] + val[rt << 1 | 1];
    }

    int Query(int l, int r, int L, int R, int rt) {
        if (l <= L && R <= r) {
            return val[rt];
        }

        int sum = 0;
        int mid = (L + R) >> 1;
        if (l <= mid) sum += Query(l, r, L, mid, rt << 1);
        if (r > mid) sum += Query(l, r, mid + 1, R, rt << 1 | 1);
        return sum;
    }
}seg;

int main()
{
    while (cin >> n >> q) {
        for (int i = 1; i <= n; i++) {
            L[i] = R[i] = 0;
            query[i].clear();
        }

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (L[a[i]] == 0) {
                L[a[i]] = i;
                sum ++;
            }
            R[a[i]] = i;
        }

        int l, r;
        for (int i = 0; i < q; i++) {
            scanf("%d%d", &l, &r);
            l ++;
            r --;
            if (r < l) {
                ans[i] = sum;
            }
            else {
                query[r].push_back(PII(l, i));
            }
        }

        seg.Build(1, n, 1);
        for (int i = 1; i <= n; i++) {
            if (R[a[i]] == i) {
                seg.Update(L[a[i]], 1, 1, n, 1);
            }

            for (int j = 0; j < query[i].size();  j++) {
                int l = query[i][j].first;
                int r = i;
                int idx = query[i][j].second;
                //cout << l << " " << r << " " << seg.Query(l, r, 1, n, 1);
                if (l > r) ans[idx] = sum;
                else ans[idx] = sum - seg.Query(l, r, 1, n, 1);
            }
        }

        for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
