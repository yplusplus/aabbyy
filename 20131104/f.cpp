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

const int N = 111;
char str[N];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i <= n; i++) cin >> str;
        n = strlen(str);
        printf("%d\n", n + 2);
        for (int i = 0; i < n; i++) {
            int a = n + 1, b = n + 1, c = n + 1;
            if (str[i] == 'a') a = i + 1;
            else if (str[i] == 'b') b = i + 1;
            else c = i + 1;
            printf("%d %d %d %d 1\n", i, a, b, c);
        }
        printf("%d %d %d %d 0\n", n, n + 1, n + 1, n + 1);
        printf("%d %d %d %d 1\n", n + 1, n + 1, n + 1, n + 1);
        puts("");
    }
    return 0;
}
