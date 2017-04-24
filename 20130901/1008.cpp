#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[30][4];

bool check(int c[4][4])
{
    for(int i = 0; i < 4; i ++) {
        int state = 0;
        for(int j = 0; j < 4; j ++) {
            state |= (1 << (c[j][i] - 1));
        }
        if(state != 15) return false;
    }
    for(int i = 0; i < 4; i += 2) {
        for(int j = 0; j < 4; j += 2) {
            int state = 0;
            for(int k = 0; k < 2; k ++)
                for(int r = 0; r < 2; r ++)
                    state |= (1 << (c[i + k][r + j] - 1));
            if(state != 15) return false;
        }
    }
    return true;
}

int re[555][4][4],tot = 0;

bool check(int x1,int x2,int x3,int x4)
{
    int c[4][4];
    for(int i = 0; i < 4; i ++) c[0][i] = a[x1][i];
    for(int i = 0; i < 4; i ++) c[1][i] = a[x2][i];
    for(int i = 0; i < 4; i ++) c[2][i] = a[x3][i];
    for(int i = 0; i < 4; i ++) c[3][i] = a[x4][i];
    bool flag = check(c);
    if(flag) {
        for(int i = 0; i < 4; i ++)
            for(int j = 0; j < 4; j ++)
                re[tot][i][j] = c[i][j];
        tot ++;
    }
    return flag;
}


int r[4],c[4],grid[4];

int get_grid(int x,int y)
{
    x /= 2,y /= 2;
    return x * 2 + y;
}

int num;
int aa[4][4];
void dfs(int x,int y)
{
    if(y == 4) {
        x ++,y = 0;
    }
    if(x == 4) {
        num ++;
        return;
    }
    if(num > 1) return;
    if(aa[x][y]) {
        dfs(x,y + 1);
        return;
    }
    for(int i = 0; i < 4; i ++) {
        if(r[x] & (1 << i)) continue;
        if(c[y] & (1 << i)) continue;
        if(grid[get_grid(x,y)] & (1 << i)) continue;
        r[x] |= (1 << i);
        c[y] |= (1 << i);
        grid[get_grid(x,y)] |= (1 << i);
        aa[x][y] = i + 1;
        dfs(x,y + 1);
        r[x] ^= (1 << i);
        c[y] ^= (1 << i);
        grid[get_grid(x,y)] ^= (1 << i);
        aa[x][y] = 0;
    }
}

bool sure(int a[4][4])
{
    for(int i = 0; i < 4; i ++)
        for(int j = 0; j < 4; j ++)
            aa[i][j] = a[i][j];
    //cout << "fuck you" << endl;
    memset(r,0,sizeof(r));
    memset(c,0,sizeof(c));
    memset(grid,0,sizeof(grid));
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if(!a[i][j]) continue;
            r[i] |= (1 << (a[i][j] - 1));
        }
    }
    for(int i = 0; i < 4; i ++)
        for(int j = 0; j < 4; j ++) {
            if(!a[j][i]) continue;
            c[i] |= (1 << (a[j][i] - 1));
        }
    for(int i = 0; i < 4; i += 2)
        for(int j = 0; j < 4; j += 2)
            for(int k = 0; k < 2; k ++)
                for(int p = 0; p < 2; p ++)
                    grid[get_grid(i,j)] |= (1 << (a[k + i][p + j] - 1));
    num = 0;
    //cout << "fuck you" << endl;
    dfs(0,0);
    return num == 1;
}

int main()
{
    cout << 13579392 + 288<< endl;
    /*
    int b[4];
    for(int i = 0; i < 4; i ++) b[i] = i + 1;
    int ct = 0;
    do {
        for(int i = 0; i < 4; i ++) a[ct][i] = b[i];
        ct ++;
    }while(next_permutation(b,b + 4));
    long long ans = 0;
    for(int i = 0; i < 24; i ++) {
        for(int j = 0; j < 24; j ++) {
            for(int k = 0; k < 24; k ++) {
                for(int r = 0; r < 24; r ++) {
                    check(i,j,k,r);
                    //cout << i << " " << j << " " << k << " " << r << " " << tot << endl;
                }
            }
        }
    }
    
    cout << tot << endl;
    
    for(int i = 0; i < tot; i ++) {
        int c[4][4];
        //cout << "fuck" <<endl;
        for(int j = 0; j < (1 << 16); j ++) {
            for(int k = 0; k < 4; k ++)
                for(int r = 0; r < 4; r ++)
                    c[k][r] = re[i][k][r];
            for(int k = 0; k < 16; k ++) {
                if(j & (1 << k)) {
                    c[k / 4][k % 4] = 0;
                }
            }
            if(sure(c)) ans ++;
        }
    }
    cout << ans << endl;*/
    return 0;
}

