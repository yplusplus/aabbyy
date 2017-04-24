#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t,n;
    char s[15];
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d",&n);
        scanf("%s",s);
        int x = 0,y = 0,z = 0;
        for(int i = 0; s[i]; i ++)
            if(s[i] == 'B') x ++;
            else if(s[i] == 'W') y ++;
            else if(s[i] == 'T') z ++;
        printf("Case %d: ",cas);
        if(x + y == 0 && !z) cout << "ABANDONED" << endl;
        else if(!y && !z) cout << "BANGLAWASH" << endl;
        else if(!x && !z) cout << "WHITEWASH" << endl;
        else if(x == y) cout << "DRAW" << " " << x << " " << z << endl;
        else {
            if(x > y) cout << "BANGLADESH ";
            else cout << "WWW ";
            cout << max(x,y) << " - " << min(x,y) << endl;
        }
    }
    return 0;
}
        
        

