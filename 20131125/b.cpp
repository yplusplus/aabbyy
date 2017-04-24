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

const int N = 111111;
char s[N], t[N];

int main() {
    while (~scanf("%s", s + 1) && s[1] != '0') {
        scanf("%s", t + 1);
        int slen = strlen(s + 1);
        int tlen = strlen(t + 1);
        for (int i = 1; i <= tlen; i++) {
            int j = i % slen;
            if (j == 0) j = slen;
            t[i] = (t[i] - 'A' + 1 + s[j] - 'A' + 1) % 26;
            if (t[i] == 0) t[i] = 26;
            t[i] += 'A' - 1;
        }
        puts(t + 1);
    }
    return 0;
}
