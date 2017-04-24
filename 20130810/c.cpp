#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int magic = 10000;
bool visit[magic];

int sign(int a, int b, int c) {
    switch (c) {
        case 0: return a + b;
        case 1: return a - b;
        case 2: return a * b;
        case 3: return a / b;
    }
}

int num[4];
int a[4], b[3], s[5];

bool calc() {
    vector<pii> v;
    v.pb(mp(num[a[0]], 3));
    for (int i = 0; i < 3; i++) {
        v.pb(mp(s[i], i));
        v.pb(mp(num[a[i + 1]], 3));
    }
    for (int i = 0; i < 3; i++) {
        int j;
        for (j = 1; j < (3 - i) * 2 + 1; j += 2) {
            if (v[j].se == b[i]) break;
        }
        if (v[j + 1].fi == 0 && v[j].fi == 3) {
            v[0].fi = 0;
            break;
        }
        int t = sign(v[j - 1].fi, v[j + 1].fi, v[j].fi);
        vector<pii> u;
        for (int k = 0; k < v.size(); k++) {
            if (abs(k - j) > 1) u.pb(v[k]);
            if (k == j) u.pb(mp(t, 3));
        }
        v = u;
    }
    return v[0].fi == 10;
}

bool check() {
    for (int i = 0; i < 4; i++) a[i] = i;
    do {
        for (s[0] = 0; s[0] < 4; s[0]++) {
            for (s[1] = 0; s[1] < 4; s[1]++) {
                for (s[2] = 0; s[2] < 4; s[2]++) {
                    for (int i = 0; i < 3; i++) b[i] = i;
                    do {
                        if (calc()) return true;
                    } while (next_permutation(b, b + 3));
                }
            }
        }
    } while (next_permutation(a, a + 4));
    return false;
}

int main() {
    memset(visit, false, sizeof(visit));

    for (int i = 0; i < magic; i++) {
        int x = i;
        for (int j = 3; j >= 0; j--) {
            num[j] = x % 10;
            x /= 10;
        }
        sort(num, num + 4);
        for (int j = 0; j < 4; j++) {
            x = x * 10 + num[j];
        }
        visit[i] = i == x ? check() : visit[x];
        //cout << i << " " << visit[i] << endl;
    }
    //cout << "ok" << endl;
    char str[10];
    int n;
    while (scanf("%d", &n), n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            //cout << atoi(str) << " " << visit[atoi(str)] << endl;
            if (!visit[atoi(str)]) found = true;
        }
        puts(found ? "BUSTED" : "TRUE");
    }
    return 0;
}
