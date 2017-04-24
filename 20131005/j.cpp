#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

map<string,int> ma;

int main()
{
    string s,str;
    int n;
    cin >> n;
    for(int i = 0; i < (1 << n); i ++) {
        cin >> s >> str;
        ma[str] ++;
    }
    int maxn = 0;
    for(map<string,int>::iterator it = ma.begin(); it != ma.end(); it ++)
        maxn = max(maxn,it->second);
    int ans = 0;
    for(int i = 1; i <= n; i ++) {
        int tot = 1 << (n - i + 1);
        if(tot >= 2 * maxn) {
            ans ++;
        }
        else break;
    }
    cout << ans << endl;
    return 0;
}

