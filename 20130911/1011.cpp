include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1111111;
int a[11], b[11];
char buf[N];

bool check(int x) {
    for (int i = 0, j; i <= x; i++) {
        j = x - i;
        if (a[i] && b[j]) {
            a[i]--, b[j]--;
            return true;
        }
    }
    for (int i = 0, j; i <= 9; i++) {
        j = x + 10 - i;
        if (j > 9) continue;
        if (a[i] && b[j]) {
            a[i]--, b[j]--;
            return true;
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        char *p;
        cin >> buf;
        p = buf;
        memset(a, 0, sizeof(a));
        while (*p) {
            a[*p - '0']++;
            p++;
        }
        cin >> buf;
        p = buf;
        memset(b, 0, sizeof(b));
        while (*p) {
            b[*p - '0']++;
            p++;
        }
        int l = strlen(buf);
        int mi, mj, mx = -1;
        for (int i = 1; i <= 9; i++) {
            if (!a[i]) continue;
            for (int j = 1; j <= 9; j++) {
                if (!b[j]) continue;
                if (mx < (i + j) % 10) mx = (i + j) % 10, mi = i, mj = j;
            }
        }
        if (mx == -1) {
            for (int i = 0; i <= 9; i++) {
                if (!a[i]) continue;
                for (int j = 0; j <= 9; j++) {
                    if (!b[j]) continue;
                    if (mx < (i + j) % 10) mx = (i + j) % 10, mi = i, mj = j;
                }
            }
            buf[0] = mx + '0';
            a[mi]--, b[mj]--;
            buf[1] = 0;
        } else {
            buf[0] = mx + '0';
            a[mi]--, b[mj]--;
            //cout << mi << ' ' << mj << endl;
            int ci = 9;
            for (int i = 1; i < l; i++) {
                while (!check(ci)) ci--;
                buf[i] = ci + '0';
            }
            buf[l] = 0;
        }
        p = buf;
        while (*p == '0') p++;
        if (!*p) p--;
        cout << "Case #" << cas << ": " << p << endl;
    }
    return 0;
}

