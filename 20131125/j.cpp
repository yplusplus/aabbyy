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

const int M = 111111;
const int N = 1111;
const ll limit = 1000000000;
ll s[M];
int top, m;
char cmd[M][7];
ll x[M];

ll myabs(ll x) { return x < 0 ? -x : x; }

bool solve(ll val) {
    top = 0;
    s[++top] = val;
    for (int i = 0; i < m; i++) {
        if (strcmp(cmd[i], "INV") == 0) {
            s[top] *= - 1;
        }
        if (strcmp(cmd[i], "NUM") == 0) {
            s[++top] = x[i];
        }
        if (strcmp(cmd[i], "MUL") == 0) {
            if (top < 2) return false;
            s[top - 1] *= s[top];
            top--;
        }
        if (strcmp(cmd[i], "ADD") == 0) {
            if (top < 2) return false;
            s[top - 1] += s[top];
            top--;
        }
        if (strcmp(cmd[i], "DUP") == 0) {
            if (top == 0) return false;
            s[top + 1] = s[top];
            top++;
        }
        if (strcmp(cmd[i], "SWP") == 0) {
            if (top < 2) return false;
            swap(s[top - 1], s[top]);
        }
        if (strcmp(cmd[i], "POP") == 0) {
            if (top == 0) return false;
            top--;
        }
        if (strcmp(cmd[i], "MOD") == 0) {
            if (top < 2 || s[top] == 0) return false;
            s[top - 1] %= s[top];
            top--;
        }
        if (strcmp(cmd[i], "DIV") == 0) {
            if (top < 2 || s[top] == 0) return false;
            s[top - 1] /= s[top];
            top--;
        }
        if (strcmp(cmd[i], "SUB") == 0) {
            if (top < 2) return false;
            s[top - 1] -= s[top];
            top--;
        }
        if (top && myabs(s[top]) > limit) return false;
    }
    if (top != 1) return false;
    printf("%d\n", (int) s[top]);
    return true;
}

int main() {
    m = 0;
    while (~scanf("%s", cmd[m]) && strcmp(cmd[m], "QUIT")) {
        if (strcmp(cmd[m], "NUM") == 0) scanf("%d", &x[m]);
        if (strcmp(cmd[m], "END") == 0) {
            int n;
            scanf("%d", &n);
            for (int i = 0, val; i < n; i++) {
                scanf("%d", &val);
                if (!solve(val)) puts("ERROR");
            }
            m = 0;
            puts("");
        }
        m++;
    }
    return 0;
}
