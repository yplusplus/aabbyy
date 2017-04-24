#include <iostream>

using namespace std;

const string day[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

int main()
{
//    int n, s = 0;
//    while (cin >> n) {
//    for (int n = 1; n <= 60; ++n) {
//        int a = 1;
//        for (int i = 1; i <= n; ++i) a *= n, a %= 7;
//        cout << n << ' ' << a << ' ' << (s += a) % 7 << endl;
//    }
    int T, n;
    cin >> T;
    while (T-- && cin >> n) {
        int ans = n / 42 * 6 % 7;
        n %= 42;
        for (int i = 1; i <= n; ++i) {
            int t = 1;
            for (int j = 1; j <= i; ++j) t *= i, t %= 7;
            ans += t;
            ans %= 7;
        }
        cout << day[ans] << endl;
    }
    return 0;
}