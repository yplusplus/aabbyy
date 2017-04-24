#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
int dir[8][2] = {0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};
int dp[22][8][8][8][8][8][8];

bool check(int x,int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void update_max(int &x,int y)
{
    x = max(x,y);
}

void update_min(int &x,int y)
{
    x = min(x,y);
}

bool check(int x1,int y1,int x2,int y2,int x3,int y3)
{
    if(x1 == x2) return false;
    if(x1 == x3) return false;
    if(y1 == y2) return false;
    if(y1 == y3) return false;
    return true;
}
    
bool check(int x1,int y1,int x2,int y2)
{
    if(x1 == x2 && abs(y1 - y2) == 1) return false;
    if(y1 == y2 && abs(x1 - x2) == 1) return false;
    if(x1 != x2 && y1 != y2 && abs(x1 - x2) + abs(y1 - y2) == 2) return false;
    return true;
}
    
        
int dfs(int dep,int x1,int y1,int x2,int y2,int x3,int y3)
{
    //if(dep == 1) cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << endl;
    if(dep > 20) return oo;
    //if(!check(x1,y1)) cout << "fuck" << endl;
    //if(!check(x2,y2)) cout << "fuck" << endl;
    //if(!check(x3,y3)) cout << "fuck" << endl;
    if(dp[dep][x1][y1][x2][y2][x3][y3] != -1) return dp[dep][x1][y1][x2][y2][x3][y3];
    if(dep & 1) {
        for(int k = 0; k < 8; k ++) {
            int tx = x1 + dir[k][0];
            int ty = y1 + dir[k][1];
            if(!check(tx,ty)) continue;
            if(tx == x2 && ty == y2 && x2 != x3 && y2 != y3) return dp[dep][x1][y1][x2][y2][x3][y3] = oo;
            if(tx == x3 && ty == y3 && x2 != x3 && y2 != y3) return dp[dep][x1][y1][x2][y2][x3][y3] = oo;
        }        
        //if(!check(x1,y1,x2,y2,x3,y3)) return 0;
        dp[dep][x1][y1][x2][y2][x3][y3] = 0;
        bool flag = false;
        for(int k = 0; k < 8; k ++) {
            int tx = x1 + dir[k][0];
            int ty = y1 + dir[k][1];
            if(!check(tx,ty)) continue;
            if(tx == x2 && ty == y2) continue;
            if(tx == x3 && ty == y3) continue;
            if(!check(tx,ty,x2,y2,x3,y3)) continue;
            flag = true;
            update_max(dp[dep][x1][y1][x2][y2][x3][y3],dfs(dep + 1,tx,ty,x2,y2,x3,y3) + 1);
        }
        if(!flag && check(x1,y1,x2,y2,x3,y3)) return dp[dep][x1][y1][x2][y2][x3][y3] = oo;
        if(!flag && !check(x1,y1,x2,y2,x3,y3)) return dp[dep][x1][y1][x2][y2][x3][y3] = 0;
        return dp[dep][x1][y1][x2][y2][x3][y3];
    }
    int mix = oo;
    for(int i = 1; x2 + i < 8; i ++) {
        if(y2 == y3 && x2 + i == x3) break;
        bool flag = check(x2 + i,y2,x1,y1);
        if(!flag) {
            if(y2 == y3) flag = true;
            if(x2 + i == x3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2 + i,y2,x3,y3) + 1);
    }
    for(int i = 1; x2 - i >= 0; i ++) {
        if(y2 == y3 && x2 - i == x3) break;
        bool flag = check(x2 - i,y2,x1,y1);
        if(!flag) {
            if(y2 == y3) flag = true;
            if(x2 - i == x3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2 - i,y2,x3,y3) + 1);        
    }
    for(int i = 1; y2 + i < 8; i ++) {
        if(x2 == x3 && y2 + i == y3) break;
        bool flag = check(x2,y2 + i,x1,y1);
        if(!flag) {
            if(x2 == x3) flag = true;
            if(y2 + i == y3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2,y2 + i,x3,y3) + 1);
    }
    for(int i = 1; y2 - i >= 0; i ++) {
        if(x2 == x3 && y2 - i == y3) break;
        bool flag = check(x2,y2 - i,x1,y1);
        if(!flag) {
            if(x2 == x3) flag = true;
            if(y2 - i == y3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2,y2 - i,x3,y3) + 1);
    }    
    
    int xx2 = x2,yy2 = y2,xx3 = x3,yy3 = y3;
    swap(x2,x3);
    swap(y2,y3);
    for(int i = 1; x2 + i < 8; i ++) {
        if(y2 == y3 && x2 + i == x3) break;
        bool flag = check(x2 + i,y2,x1,y1);
        if(!flag) {
            if(y2 == y3) flag = true;
            if(x2 + i == x3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2 + i,y2,x3,y3) + 1);
    }
    for(int i = 1; x2 - i >= 0; i ++) {
        if(y2 == y3 && x2 - i == x3) break;
        bool flag = check(x2 - i,y2,x1,y1);
        if(!flag) {
            if(y2 == y3) flag = true;
            if(x2 - i == x3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2 - i,y2,x3,y3) + 1);        
    }
    for(int i = 1; y2 + i < 8; i ++) {
        if(x2 == x3 && y2 + i == y3) break;
        bool flag = check(x2,y2 + i,x1,y1);
        if(!flag) {
            if(x2 == x3) flag = true;
            if(y2 + i == y3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2,y2 + i,x3,y3) + 1);
    }
    for(int i = 1; y2 - i >= 0; i ++) {
        if(x2 == x3 && y2 - i == y3) break;
        bool flag = check(x2,y2 - i,x1,y1);
        if(!flag) {
            if(x2 == x3) flag = true;
            if(y2 - i == y3) flag = true;
        }
        if(flag) update_min(mix,dfs(dep + 1,x1,y1,x2,y2 - i,x3,y3) + 1);
    }    
    return dp[dep][x1][y1][xx2][yy2][xx3][yy3] = mix;
}
        
            
void solve(int t)
{
    char s[15];
    int x1,x2,x3,y1,y2,y3;
    scanf("%s",s);
    x1 = s[0] - 'a';
    y1 = s[1] - '1';
    scanf("%s",s);
    x2 = s[0] - 'a';
    y2 = s[1] - '1';
    scanf("%s",s);
    x3 = s[0] - 'a';
    y3 = s[1] -  '1';
    printf("%d\n",(1 + dfs(0,x1,y1,x2,y2,x3,y3)) / 2);
}

int main()
{
    memset(dp,-1,sizeof(dp));
    int t;
    scanf("%d",&t);
    for(int i = 1; i <= t; i ++) {
        solve(i);
    }
    return 0;
}



