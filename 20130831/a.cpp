#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
 
using namespace std;
 
typedef long long LL;
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a;}
char str[33];
 
int main() {
    //freopen("in", "r", stdin);
    while (cin >> str) {
        LL A, B, la, lb;
        int i = 0, len = strlen(str);
        while (i < len && str[i] != '.') i++;
        i++;
        A = B = 0;
        la = lb = 0;
        if (isdigit(str[i])) {
            while (i < len && isdigit(str[i])) A = A * 10 + str[i] - '0', i++, la++;
            if (str[i] == '(') {
                i++;
                while (i < len && isdigit(str[i])) B = B * 10 + str[i] - '0', i++, lb++;
            }
        } else {
            if (str[i] == '(') {
                i++;
                while (i < len && isdigit(str[i])) B = B * 10 + str[i] - '0', i++, lb++;
            }
        }
        //cout << A << ' ' << B << ' ' << la << ' ' << lb << endl;
        LL SA = 0, SB = 1;
        while (lb--) SB *= 10;
        if (SB > 1) SB--;
        SA = SB * A + B;
        while (la--) SB *= 10;
        LL GCD = gcd(SA, SB);
        //cout << SA << ' ' << SB << endl;
        if (GCD) cout << SA / GCD << '/' << SB / GCD << endl;
        else cout << "0/1" << endl;
    }
    return 0;
}

