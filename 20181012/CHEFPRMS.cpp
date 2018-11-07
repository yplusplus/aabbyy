#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 222;
bool is_prime[N];
bool is_semi_prime[N];

void init() {
    for (int i = 2; i < N; i++) {
        bool found = false;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                found = true;
                break;
            }
        }
        is_prime[i] = !found;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            if (is_prime[i] && is_prime[j] && i * j < N) {
                is_semi_prime[i * j] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    init();

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        bool found = false;
        for (int i = 1; i < n; i++) {
            if (is_semi_prime[i] && is_semi_prime[n - i]) {
                found = true;
                break;
            }
        }
        if (found) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
