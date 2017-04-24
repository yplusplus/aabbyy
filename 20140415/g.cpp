#include <iostream>
using namespace std;

int encode(char ch) {
    if (ch == '+') return 0;
    if (ch == '-') return 1;
    if (ch == '*') return 2;
    if (ch == '/') return 3;
    if (ch == '%') return 4;
    return -1;
}

int calc(int a, int b, char ch) {
    switch (ch) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
    }
    return -1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string sign1, sign2;
        int a, b, c;
        cin >> a >> sign1 >> b >> sign2 >> c;
        int d = encode(sign1[0]);
        int e = encode(sign2[0]);
        int ans;
        if (d <= 1 && e >= 2) {
            ans = calc(a, calc(b, c, sign2[0]), sign1[0]);
        } else {
            ans = calc(calc(a, b, sign1[0]), c, sign2[0]);
        }
        cout << ans << endl;
    }
    return 0;
}
