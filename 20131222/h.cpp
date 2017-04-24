#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
ll x, target;
int dfs(ll x) {
    if (x <= target) return 0;
    ll mod = (x >> 1) + 1;
    return dfs(x / mod * mod) + 1;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        cin >> x >> target;
        printf("Case %d: %d\n", Case++, dfs(x));
    }
    return 0;
}
