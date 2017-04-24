#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    while(cin >> n >> m) {
        int ans = 0;
        for(int i = n; i < m; i ++)
            ans += (m - i);
        cout << ans << endl;
    }
    return 0;
}

