#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

double calc(string base) {
    double res = 100.0;
    double t = 1000.0 / 1024;
    if (base == "B") return res;
    res *= t;
    if (base == "KB") return res;
    res *= t;
    if (base == "MB") return res;
    res *= t;
    if (base == "GB") return res;
    res *= t;
    if (base == "TB") return res;
    res *= t;
    if (base == "PB") return res;
    res *= t;
    if (base == "EB") return res;
    res *= t;
    if (base == "ZB") return res;
    res *= t;
    if (base == "YB") return res;
    return -1;
}

int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        int d;
        string str;
        cin >> d >> str;
        printf("Case #%d: %.02f%%\n", Case++, 100.0 - calc(str.substr(1, str.length() - 2)));
    }
    return 0;
}
