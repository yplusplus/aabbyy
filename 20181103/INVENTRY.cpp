#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 100000 + 10;
char str[N];
int n;
int pos[N];

long long solve() {
    scanf("%d%s", &n, str);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == '#') pos[i] = cnt++;
    }

    long long ans = 0;
    int i = 0;
    while (i < n && str[i] == '#') i++;
    for (; i < n; i++) {
        if (str[i] == '.') continue;
        int j = i;
        int empty = 0;
        vector<int> boxs;
        for (; j < n; j++) {
            if (str[j] == '#') boxs.push_back(j);
            else empty++;
            if (empty >= boxs.size()) break;
        }
        //cout << i << " " << j << " " << boxs.size() << endl;
        if (j == n) return -1;
        for (int k = 0; k < boxs.size(); k++) {
            ans += abs(boxs[k] - (i + k * 2));
            ans += abs((i + k * 2) - pos[boxs[k]]);
        }
        i = j;
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long ans = solve();
        cout << ans << endl;
    }
    return 0;
}
