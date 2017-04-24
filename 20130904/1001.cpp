#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    unsigned long long n,m;

    ios::sync_with_stdio(0);
    while(cin >> n >> m) {
        if(n % m == 0) cout << n / m << endl;
        else if(n % 2 && m % 2 == 0) cout << "No Solution!" << endl;
        else if(n & 1) {
            unsigned long long x = n / m + 1;
            if(x % 2);
            else x ++;
            cout << x << endl;
        }
        else if(n / m >= 2) {
            unsigned long long x = n / m + 1;
            if(m % 2 && x % 2) x ++;
            cout << x << endl;
        }
        else if(m % 2 == 0) cout << 3 << endl;
        else {
            m = n - m;
            unsigned long long x = n / m;
            if(n % m) x ++;
            if(m % 2 == 0 && x % 2 == 0) x ++;
            else if(m % 2 && x % 2) x ++;
            cout << x << endl;
        }
    }
    return 0;
}