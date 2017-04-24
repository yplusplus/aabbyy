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

int n;
double score[256];
int main() {
    score['A'] = 4.0;
    score['B'] = 3.0;
    score['C'] = 2.0;
    score['D'] = 1.3;
    score['F'] = 0.0;
    while (~scanf("%d", &n)) {
        double a = 0, b = 0;
        bool found = false;
        for (int i = 0; i < n; i++) {
            int c;
            char str[10];
            scanf("%d%s", &c, str);
            if (str[0] == 'P' || str[0] == 'N') continue;
            found = true;
            b += c;
            a += c * (score[str[0]] + (str[1] == '+' ? 0.3 : (str[1] == '-' ? -0.3 : 0)));
        }
        if (!found) puts("0.00");
        else printf("%.2f\n", a / b);
    }
    return 0;
}
