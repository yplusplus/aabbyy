#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

long long x,y;
long long ex_gcd(long long a,long long b)
{
    if(!b) {
        x = 1,y = 0;
        return a;
    }
    long long d = ex_gcd(b,a % b);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return d;
}

int main()
{
    long long a,b,c;
    ios::sync_with_stdio(0);
    while(cin >> a >> b >> c) {
        if(!a && !b && !c) break;
        if(!a) {
            if(c % b) cout <<"Unquibable!" << endl;
            else {
                if(c / b != 1) cout <<"0 fooms and " << c / b << " foobs for a twob!" << endl;
                else cout <<"0 fooms and " << c / b << " foob for a twob!" << endl;
            }
            continue;
        }
        long long d = ex_gcd(a,b);
        if(c % d) {
            cout <<"Unquibable!" << endl;
            continue;
        }
        long long mul = c / d;
        long long e = b / d;
        mul %= e,x %= e;
        x = x * mul % e;
        if(x < 0) x += e;
        if(c / a < x) {
            cout <<"Unquibable!" << endl;
            continue;
        }
        y = (c - a * x) / b;
        if(y < 0) {
            cout <<"Unquibable!" << endl;
            continue;
        }
        if(x != 1) cout << x << " fooms and ";
        else cout << x << " foom and ";
        if(y != 1) cout << y << " foobs for a twob!" << endl;
        else cout << y << " foob for a twob!" << endl;
    }
    return 0;
}
        
        
        
    



