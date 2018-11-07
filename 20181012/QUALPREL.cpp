#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int N = 100100;
int a[N];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a, a + n, greater<int>());
        int score = a[k - 1];
        while (a[k] == score) k++;
        cout << k << endl;
    }
    return 0;
}
