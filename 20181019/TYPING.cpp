#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

int encode(char ch) {
    if (ch == 'd' || ch == 'f') return 0;
    return 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        map<string, int> mp;
        string str;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> str;
            if (mp.count(str)) ans += mp[str] / 2;
            else {
                int pre = -1;
                int sum = 0;
                for (char ch: str) {
                    int cur = encode(ch);
                    if (pre == cur) sum += 4;
                    else sum += 2;
                    pre = cur;
                }
                mp[str] = sum;
                ans += sum;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
