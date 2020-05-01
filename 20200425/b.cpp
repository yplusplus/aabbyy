#include <iostream>
using namespace std;

const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
long long sum[1001000];

bool is_leap(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 != 0 && year % 4 == 0) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    for (int i = 2000; i < 1001000; i++) {
        sum[i] = sum[i - 1] + 365 + is_leap(i);
    }
    
    int y, m, d;
    while (cin >> y >> m >> d) {
        long long ans = 0;
        if (y != 2000) { ans += sum[y - 1]; }
        for (int i = 1; i < m; i++) { ans += days[i] + (i == 2 && is_leap(y)); }
        ans += d - 1;
        cout << (ans / 4 + 1) << " " << (ans % 4 + 1) << endl;
    }

    return 0;
}
