#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_set>
using namespace std;

const int N = 200010;
unsigned long long pows[N];
int key = 137;
unsigned long long a[N], b[N];
char s[N];
int n;

#define x first
#define y second
void init() {
    pows[0] = 1;
    for (int i = 1; i < N; i++) pows[i] = pows[i - 1] * key;
}

pair<int, int> aa[5];
pair<int, int> bb[5];
int ca, cb;
unordered_set<long long> st;

unsigned long long get_hash_forward(int x, int len) {
    return (a[x + len - 1] - a[x - 1]) * pows[n - x];
}

unsigned long long get_hash_backward(int x, int len) {
    return (b[x - len + 1] - b[x + 1]) * pows[x - 1];
}

void get_first(int x, int y, int &ca, pair<int, int> aa[]) {
    ca = 0;
    if (x > y) return;
    int lt = 1, rt = (y - x + 1) / 2 + ((y - x) + 1) % 2, mid, ans = 0;
    while (lt <= rt) {
        mid = (lt + rt) >> 1;
        if (get_hash_forward(x, mid) == get_hash_backward(y, mid)) ans = mid, lt = mid + 1;
        else rt = mid - 1;
    }
    if (ans == (y - x + 1) / 2 + ((y - x) + 1) % 2) return;

    int xx = x + ans;
    int yy = y - ans;
    aa[ca++] = make_pair(xx, yy);

    xx++, yy--;
    if (xx >= yy) return;

    lt = 1, rt = (yy - xx + 1) / 2 + ((yy - xx) + 1) % 2, ans = 0;
    while (lt <= rt) {
        mid = (lt + rt) >> 1;
        if (get_hash_forward(xx, mid) == get_hash_backward(yy, mid)) ans = mid, lt = mid + 1;
        else rt = mid - 1;
    }

    if (ans == (yy - xx + 1) / 2 + (yy - xx + 1) % 2) return;

    int xxx = xx + ans, yyy = yy - ans;
    aa[ca++] = make_pair(xxx, yyy);

    xxx++, yyy--;
    if (xxx >= yyy) return;

    if (get_hash_forward(xxx, yyy - xxx + 1) != get_hash_backward(yyy, yyy - xxx + 1)) ca = 3;
}

long long encode(long long m1, long long m2) {
    if (m1 > m2) swap(m1, m2);
    return m1 * N + m2;
}

bool check_equal(int x, int y, int nx, int ny) {
    unsigned long long f = get_hash_forward(x, y - x + 1);
    unsigned long long b = get_hash_backward(y, y - x + 1);

    if (nx >= x && nx <= y) {
        f -= pows[nx - x + n] * s[nx];
        f += pows[nx - x + n] * s[ny];

        b -= pows[y - nx + n] * s[nx];
        b += pows[y - nx + n] * s[ny];
    }

    if (ny >= x && ny <= y) {
        f -= pows[ny - x + n] * s[ny];
        f += pows[ny - x + n] * s[nx];

        b -= pows[y - ny + n] * s[ny];
        b += pows[y - ny + n] * s[nx];
    }

    return b == f;
}


void solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    if (n == 1) {
        printf("0\n");
        return;
    }
    for (int i = 1; s[i]; i++) {
        a[i] = a[i - 1] + pows[i] * s[i];
    }

    b[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        b[i] = b[i + 1] + pows[n - i + 1] * s[i];
    }


    st.clear();
    bool all = false;

    for (int i = 1; i < n; i++) {
        get_first(1, i, ca, aa);
        get_first(i + 1, n, cb, bb);

        if (ca + cb > 2) continue;
        if (ca == 0 && cb == 0) {
            all = true;
            if (i % 2 == 1 && (n - i) % 2 == 1) {
                int m1 = (i + 1) >> 1;
                int m2 = i + ((n - i + 1) >> 1);
                if (s[m1] != s[m2]) {
                    st.insert(encode(m1, m2));
                }
            }
            continue;
        } else if (ca == 0 && cb == 1) {
            int x = bb[0].x, y = bb[0].y;

            if (i & 1) {
                int mid = (i + 1) >> 1;
                if (check_equal(i + 1, n, mid, x)) st.insert(encode(mid, x));
                if (check_equal(i + 1, n, mid, y)) st.insert(encode(mid, y));
            }

            if ((n - i) & 1) {
                int mid = i + ((n - i + 1) >> 1);
                if (check_equal(i + 1, n, mid, x)) st.insert(encode(mid, x));
                if (check_equal(i + 1, n, mid, y)) st.insert(encode(mid, y));
            }
        } else if (ca == 0 && cb == 2) {
            int x1 = bb[0].x, y1 = bb[0].y, x2 = bb[1].x, y2 = bb[1].y;
            if (check_equal(i + 1, n, x1, x2)) st.insert(encode(x1, x2));
            if (check_equal(i + 1, n, x1, y2)) st.insert(encode(x1, y2));
            if (check_equal(i + 1, n, y1, x2)) st.insert(encode(y1, x2));
            if (check_equal(i + 1, n, y1, y2)) st.insert(encode(y1, y2));
        } else if (ca == 1 && cb == 0) {
            int x = aa[0].x, y = aa[0].y;
            if (i & 1) {
                int mid = (i + 1) >> 1;
                if (check_equal(1, i, mid, x)) st.insert(encode(mid, x));
                if (check_equal(1, i, mid, y)) st.insert(encode(mid, y));
            }

            if ((n - i) & 1) {
                int mid = i + ((n - i) + 1 >> 1);
                if (check_equal(1, i, mid, x)) st.insert(encode(mid, x));
                if (check_equal(1, i, mid, y)) st.insert(encode(mid, y));
            }
        } else if (ca == 1 && cb == 1) {
            int x1 = aa[0].x, y1 = aa[0].y, x2 = bb[0].x, y2 = bb[0].y;
            if (check_equal(1, i, x1, x2) && check_equal(i + 1, n, x1, x2)) st.insert(encode(x1, x2));
            if (check_equal(1, i, x1, y2) && check_equal(i + 1, n, x1, y2)) st.insert(encode(x1, y2));
            if (check_equal(1, i, y1, x2) && check_equal(i + 1, n, y1, x2)) st.insert(encode(y1, x2));
            if (check_equal(1, i, y1, y2) && check_equal(i + 1, n, y1, y2)) st.insert(encode(y1, y2));
        } else if (ca == 2) {
            int x1 = aa[0].x, y1 = aa[0].y, x2 = aa[1].x, y2 = aa[1].y;
            if (check_equal(1, i, x1, x2)) st.insert(encode(x1, x2));
            if (check_equal(1, i, x1, y2)) st.insert(encode(x1, y2));
            if (check_equal(1, i, y1, x2)) st.insert(encode(y1, x2));
            if (check_equal(1, i, y1, y2)) st.insert(encode(y1, y2));
        }
    }

    long long ans = st.size();
    if (all) {
        int visit[26];
        memset(visit, 0, sizeof(visit));
        for (int i = 1; s[i]; i++)
            visit[s[i] - 'a']++;

        for (int i = 0; i < 26; i++)
            ans += 1LL * visit[i] * (visit[i] - 1) / 2;
    }

    printf("%lld\n", ans);
}

int main()
{
    init();
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
