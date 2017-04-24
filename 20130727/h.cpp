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

bool angle[500];
int main() {
    memset(angle, false, sizeof(angle));
    for (int h = 0; h < 12; h++) {
        for (int m = 0; m < 60; m++) {
            int alpha = 30 * h + m / 12 * 6;
            int beta = 6 * m;
            int a = abs(alpha - beta);
            if (a > 180) a -= 180;
            angle[a] = true;
        }
    }
    int q;
    while (cin >> q) {
        puts(angle[q] ? "Y" : "N");
    }
    return 0;
}
