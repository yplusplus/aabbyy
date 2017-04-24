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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

int main() {
    int n, g;
    while (~scanf("%d%d", &n, &g)) {
        int ans = 0;
        vector<int> vec;
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a > b) ans += 3;
            else vec.push_back(b - a);
        }
        sort(vec.begin(), vec.end());
        int i;
        for (i = 0; i < vec.size() && g; i++) {
            if (g >= vec[i] + 1) {
                ans += 3;
                g -= vec[i] + 1;
            } else if (g == vec[i]) {
                ans++;
                break;
            } else break;
        }
        for (; i < vec.size(); i++) {
            if (vec[i] == 0) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
