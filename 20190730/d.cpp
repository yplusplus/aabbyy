#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int K = 30;
const int N = 500000 +50;

int a[N * 2];
int n, k;

inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

bool check(int x) {
    //cout << x << endl;
    int y = 0;
    int m = 0;
    for (int i = 1; i <= n; i++) {
        y |= a[i];
        m = i;
        if ((y & x) == x) break;
    }
    if ((y & x) < x) return false;

    vector<int> vec;
    for (int i = m, y = 0, last = 0; i >= 1; i--) {
        y |= a[i];
        if (y > last) {
            vec.push_back(i);
            //cout << i << endl;
        }
        last = y;
    }

    for (auto idx: vec) {
        int cnt = 0;
        int y = 0;
        for (int i = idx; i < idx + n; i++) {
            y |= a[i];
            if ((y & x) == x) {
                cnt++;
                y = 0;
            }
        }
        if (cnt >= k) return true;
    }
    return false;
}

void solve() {
    n = read();
    k = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        a[i + n] = a[i];
    }
    
    int ans = 0;
    for (int i = K; i >= 0; i--) {
        if (check(ans | (1 << i))) {
            ans |= (1 << i);
        }
    }
    printf("%d\n", ans);
}

int main() {
    solve();
    return 0;
}
