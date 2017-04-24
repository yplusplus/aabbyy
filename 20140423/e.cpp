#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("numbers.in","r",stdin);
    freopen("numbers.out","w",stdout);
    ios::sync_with_stdio(false);
    unsigned long long a,b;
    while(cin >> a >> b) {
        if(!a && !b) break;
        unsigned long long first;
        for(int i = 1; i <= 9; i ++) {
            unsigned long long lt = i,rt = i;
            if(i % b == 0) {
                first = 10;
                cout << i << endl;
                break;
            }
            bool flag = false;
            while(lt <= a) {
                lt = lt * 10;
                if(lt > a) break;
                rt = rt * 10 + 9;
                rt = min(rt,a);
                unsigned long long x = lt / b;
                unsigned long long y = rt / b;
                if(lt % b) x ++;
                if(x <= y) {
                    flag = true;
                    break;
                }
            }
            if(flag) {
                first = i;
                break;
            }
        }
        if(first == 10) continue;
        while(first % b) {
            for(int i = 0; i < 10; i ++) {
                unsigned long long lt = first * 10 + i;
                unsigned long long rt = first * 10 + i;
                bool flag = false;
                if(lt % b == 0) {
                    flag = true;
                    first = first * 10 + i;
                    break;
                }
                while(lt <= a) {
                    lt = lt * 10;
                    if(lt > a) break;
                    rt = rt * 10 + 9;
                    rt = min(rt,a);
                    unsigned long long x = lt / b;
                    unsigned long long y = rt / b;
                    if(lt % b) x ++;
                    if(x <= y) {
                        flag = true;
                        break;
                    }
                }
                if(flag) {
                    first = first * 10 + i;
                    break;
                }
            }
        }
        cout << first << endl;
    }
    return 0;
}
