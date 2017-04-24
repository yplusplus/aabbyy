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

string s, name[15];
int cnt[15][30];
int n;
int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> s >> n;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            cin >> name[i];
            for (int j = 0; j < name[i].length(); j++) {
                cnt[i][name[i][j] - 'a']++;
            }
        }
        for (int j = 0; j < s.length(); j++) {
            cnt[n][s[j] - 'a']++;
        }

        int ans = 0;
        int tmp[30];
        for (int mask = 1; mask < (1 << n); mask++) {
            memset(tmp, 0, sizeof(tmp));
            int count = 0;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    count++;
                    for (int j = 0; j < 26; j++) tmp[j] += cnt[i][j];
                }
            }
            bool found = true;
            for (int j = 0; j < 26; j++) {
                if (cnt[n][j] < tmp[j]) {
                    found = false;
                    break;
                }
            }
            if (found) ans = max(ans, count);
        }
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
