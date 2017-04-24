#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 111;
int g[N][N];
int a[N];
int n, m;
void output(int a[], int start, int number) {
    printf("%d", number);
    for (int i = 0; i < number; i++) {
        printf(" %d", a[start + i]);
    }
    puts("");
}

void solve() {
    int sum = 0;
    for (int i = 0; i < n; i++) a[i] = i + 1;
    while (true) {
        random_shuffle(a, a + n);
        //for (int i = 0; i < n; i++) {
            //cout << a[i] << " ";
        //}
        //cout << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) { sum -= g[a[i]][a[j]]; }
            for (int j = i + 1; j < n; j++) { sum += g[a[i]][a[j]]; }
            if (sum >= m / 2) {
                output(a, 0, i + 1);
                output(a, i + 1, n - i - 1);
                return;
            }
        }
    }
}

int main() {
    srand(time(0));
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(g, 0, sizeof(g));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            g[a][b] = g[b][a] = 1;
        }
        solve();
    }
    return 0;
}
