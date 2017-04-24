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
char s[N];
stack<int> command;

char *command2str(int x) {
    if (x == 0) return "front 0";
    if (x == 1) return "front 1";
    if (x == 2) return "back 0";
    if (x == 3) return "back 1";
    return "double";
}

void solve(int l, int r) {
    if (l > r) return;
    while (l <= r) {
        if (l < r && s[l] == s[l + 1]) command.push(0 + (s[l] == '1')), l++;
        else if (l + 3 <= r && s[l + 2] == s[l + 3]) command.push(0 + (s[l] == '1')), l++;
        else if (l < r && s[r - 1] == s[r]) command.push(2 + (s[r] == '1')), r--;
        else if (r - 3 >= l && s[r - 3] == s[r - 2]) command.push(2 + (s[r] == '1')), r--;
        else if ((r - l) % 2 == 0) command.push(0 + (s[l] == '1')), l++;
        else break;
    }
    if (l > r) return;
    command.push(4);
    int cnt = -1;
    for (int i = l; i <= r; i += 2) {
        s[++cnt] = s[i];
    }
    solve(0, cnt);
}

int main() {
    while (~scanf("%s", s)) {
        solve(0, strlen(s) - 1);
        cout << command.size() << endl;
        while (!command.empty()) {
            puts(command2str(command.top()));
            command.pop();
        }
    }
    return 0;
}

