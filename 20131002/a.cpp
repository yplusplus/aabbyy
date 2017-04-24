#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin >> n) {
       int ans  = 1,sum = 1;
       int tmp = 2;
       while(sum < n) {
          ans ++;
          sum += tmp;
          tmp *= 2;
       }
       cout << ans << endl;
    }
    return 0;
}

