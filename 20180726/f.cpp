#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int N = 100010;
char s[N];

const int mod = 1000000007;
struct tree {
    int lt, rt;
    int a[15];
    int tot;
}a[N << 2];

int change(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

void update(tree &a, tree b, tree c) {
    a.tot = (b.tot + c.tot + 1LL * b.tot * c.tot) % mod;
    for (int i = 0; i < 15; i++) {
        a.a[i] = b.a[i] + c.a[i];
        if (a.a[i] >= mod) a.a[i] -= mod;
    }

    for (int i = 0; i < 15; i++)
        if (b.a[i])
            for (int j = 0; j < 15; j++) {
                int x = i + j;
                if (x >= 15) x -= 15;
                long long t = 1LL * b.a[i] * c.a[j];
                if (t >= mod) t %= mod;
                add(a.a[x], t);
            }
}

void init(int lt, int rt, int step) {
    a[step].lt = lt;
    a[step].rt = rt;
    memset(a[step].a, 0, sizeof(a[step].a));
    a[step].tot = 0;
    if (lt == rt) {
        int x = change(s[lt]);
        if (!x) a[step].tot++; // a[step].a[0] = 1;
        a[step].a[x % 15]++;
        return;
    }

    int mid = (lt + rt) >> 1;
    init(lt, mid, step << 1);
    init(mid + 1, rt, step << 1 | 1);
    update(a[step], a[step << 1], a[step << 1 | 1]);
}

void modify(int pos, int step, int x) {
    if (a[step].lt == a[step].rt) {
        memset(a[step].a, 0, sizeof(a[step].a));
        a[step].tot = 0;
        if (!x) a[step].tot++; // a[step].a[0] = 1;
        a[step].a[x % 15]++;
        return;
    }

    if (pos <= a[step << 1].rt) modify(pos, step << 1, x);
    else modify(pos, step << 1 | 1, x);

    update(a[step], a[step << 1], a[step << 1 | 1]);
}

tree query(int lt, int rt, int step) {
    if (a[step].lt == lt && a[step].rt == rt) return a[step];
    if (rt <= a[step << 1].rt) return query(lt, rt, step << 1);
    else if (lt > a[step << 1].rt) return query(lt, rt, step << 1 | 1);
    else {
        tree b = query(lt, a[step << 1].rt, step << 1);
        tree c = query(a[step << 1 | 1].lt, rt, step << 1 | 1);
        tree ans;
        update(ans, b, c);
        return ans;
    }
}

int pows[25];
int main()
{
    pows[0] = 1;
    for (int i = 1; i < 25; i++)
        pows[i] = 1LL * pows[i - 1] * 1021 % mod;
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        scanf("%s", s);
        init(0, n - 1, 1);
        while (m--) {
            int cd, l, r;
            scanf("%d", &cd);
            if (cd == 1) {
                scanf("%d%s", &l, s);
                l--;
                modify(l, 1, change(s[0]));
            } else {
                scanf("%d%d", &l, &r);
                l--, r--;
                tree ans = query(l, r, 1);
                int sum = 0;
                sum = ans.tot;
                for (int i = 1; i < 15; i++)
                    sum =(sum + 1LL * ans.a[i] * pows[i]) % mod;
                int x = ans.a[0] - ans.tot;
                if (x < 0) x += mod;
                sum = (sum + 1LL * x * pows[15]) % mod;
                printf("%d\n", sum);
            }
        }
    }
    return 0;
}
