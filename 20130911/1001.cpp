#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const char *a = "*------------*";
const char *b = "|............|";
const char *c = "|------------|";

int main() {
    int T, n, cas = 1;
    cin >> T;
    while (T-- && cin >> n) {
        n = 10 - n / 10;
        printf("Case #%d:\n", cas++);
        puts(a);
        for (int i = 0; i < 10; i++) {
            if (i < n) puts(b);
            else puts(c);
        }
        puts(a);
    }
    return 0;
}

