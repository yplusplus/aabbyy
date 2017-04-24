#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("crypto.in","r",stdin);
    freopen("crypto.out","w",stdout);
    int n,a,b;
    cin >> n >> a >> b;
    int ans = -1,ansx = -1,ansy = -1;
    for(int i = 1; i <= n; i ++) {
        for(int j = i; j ; j = (j - 1) & i) {
            int val = (a * i + b * j) ^ (a * j + b * i);
            if(val > ans) {
                ans = val;
                ansx = i,ansy = j;
            }
        }
    }
    cout << ansx << " " << ansy << endl;

    return 0;
}
