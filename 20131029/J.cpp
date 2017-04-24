#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3000010;
const int err = 1500000;
int sum[N];
int dir[4][2] = {1,1,-1,1,1,-1,-1,-1};
int X[N / 3],Y[N / 3];
int main()
{
    int n,m;
    cin >> n >> m;
    memset(sum,0,sizeof(sum));
    int x = 1,y = 1;
    int down = 1;
    int dirt = 0;
    long long ans = 0;
    int cnt = 0;
    while(1) {
        int tx,ty,dt;
        if(dirt == 0) {
            int d = min(n - x,m - y);
            tx = x + d * dir[dirt][0];
            ty = y + d * dir[dirt][1];
            if(tx == n) dt = 1;
            else dt = 2;
            ans += d;
        }
        else if(dirt == 1) {
            int d = min(x - 1,m - y);
            tx = x + d * dir[dirt][0];
            ty = y + d * dir[dirt][1];
            if(tx == 1) dt = 0;
            else dt = 3; 
            ans += d;
        }
        else if(dirt == 2) {
            int d = min(n - x,y - 1);
            tx = x + d * dir[dirt][0];
            ty = y + d * dir[dirt][1];
            if(tx == n) dt = 3;
            else dt = 0;
            ans += d;
        }
        else if(dirt == 3) {
            int d = min(x - 1,y - 1);
            tx = x + d * dir[dirt][0];
            ty = y + d * dir[dirt][1];            
            if(tx == 1) dt = 2;
            else dt = 1;
            ans += d;
        }
        if(down) sum[x - y + err] = 1;
        else {
            X[cnt] = min(x - y,tx - ty) + err;
            Y[cnt ++] = max(x - y,tx - ty) + err;
        }
        if((tx == 1 || tx == n) && (ty == 1 || ty == m)) break;
        down ^= 1;
        ans += 2;
        x = tx,y = ty,dirt = dt;
    }
    for(int i = 1; i < N; i ++) sum[i] += sum[i - 1];
    for(int i = 0; i < cnt; i ++) {
        ans -= 2 * (sum[Y[i]] - sum[X[i] - 1]);
    }
    cout << ans + 1 << endl;    
    return 0;
}



