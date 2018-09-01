#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2000010;
const int mod = 1000000007;
long long pows[N];

struct ptree {
    int next[N][10], fail[N], len[N]; 
    long long cnt[N], val[N];
    int s[N];
    int c, n, last;

    ptree() {
        memset(val, 0, sizeof(val));
    }

    void newnode(int l, int suf = 0, long long x = 0) {
        memset(next[c], 0, sizeof(next[c]));
        cnt[c] = 0;
        if (l > 0) {
            if (l > 1) val[c] = (pows[l - 1] * x + val[suf] * 10LL + x) % mod;
            else val[c] = x;
        }
        len[c++] = l;
    }

    void init() {
        c = 0;
        newnode(0);
        newnode(-1);
        last = n = 0;
        s[n] = -1;
        fail[0] = 1;
    }

    int get_fail(int x) {
        while (s[n - len[x] - 1] != s[n]) x = fail[x];
        return x;
    }

    void add(int x) {
        s[++n] = x;
        int suffix = get_fail(last);
        if (!next[suffix][x]) {
            newnode(len[suffix] + 2, suffix, x);
            fail[c - 1] = next[get_fail(fail[suffix])][x];
            next[suffix][x] = c - 1;
        }
        last = next[suffix][x];
        cnt[last]++;
    }

    void sum() {
        long long ans = 0;

        for (int i = 1; i < c; i++) {
            ans = (ans + 1LL * val[i]) % mod;
        }
        printf("%lld\n", ans);
    }

    void print() {
        for (int i = 0; i < c; i++)
            cout << i << " " << len[i] << " " << cnt[i] << endl;
    }
}ptree;

char s[N];

int main()
{
    pows[0] = 1;
    for (int i = 1; i < N; i++) pows[i] = pows[i - 1] * 10 % mod;
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    ptree.init();
    for (int i = 1; i <= n; i++) {
        ptree.add(s[i] - '0');
    }
    ptree.sum();
} 
