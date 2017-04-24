#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long mod = 100000000000000LL;
struct bignum
{
	long long a[10];
	bignum() {
		memset(a,0,sizeof(a));
	}
	bignum add(bignum p) {
		bignum c;
		for(int i = 0; i < 10; i ++)
			c.a[i] = p.a[i] + a[i];
		for(int i = 0; i < 10; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		return c;
	}
    bignum add(int x) {
        bignum c;
        c.a[0] = a[0] + x;
        for(int i = 1; i < 10; i ++) c.a[i] = a[i];
		for(int i = 0; i < 10; i ++)
			if(c.a[i] >= mod) {
				c.a[i + 1] ++;
				c.a[i] -= mod;
			}
		return c;
	}        
	bignum mult(int x) {
		bignum tmp;
		for(int i = 0; i < 10; i ++) tmp.a[i] = a[i] * x;
		for(int i = 0; i < 10; i ++) {
			if(tmp.a[i] >= mod) {
				tmp.a[i + 1] += tmp.a[i] / mod;
				tmp.a[i] %= mod;
			}
		}
		return tmp;
	}
	bignum sub(bignum p) {
		bignum c;
		for(int i = 0; i < 10; i ++) 
			c.a[i] = a[i] - p.a[i];
		for(int i = 0; i < 10; i ++)
			if(c.a[i] < 0) {
				c.a[i + 1] --;
				c.a[i] += mod;
			}
		return c;
	}
    bignum sub(int x) {
        bignum c;
        c.a[0] = a[0] - x;
        for(int i = 1; i < 10; i ++) c.a[i] = a[i];
		for(int i = 0; i < 10; i ++)
			if(c.a[i] < 0) {
				c.a[i + 1] --;
				c.a[i] += mod;
			}
		return c;
    }        
	void output() {
		int i = 9;
		for(; i >= 0; i --)
			if(a[i]) break;
		if(i == -1) i ++;
		printf("%lld",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%014lld",a[i]);
		printf("\n");
	}
	void init() {
		memset(a,0,sizeof(a));
	}
}c[10032][30],dp[10010];

int a[25][35];
int bit[1 << 20];
int K,S,M;
bignum ans;

void dfs(int X[],int state,int step,int sum,int flag,int pos,int num,int ss)
{
    if(sum < 0) return;
    if(flag) {
        if(!(step & 1) && step % 2 == ss) {
            if(num == 0 && sum >= 2) {
                ans = ans.add(dp[sum]);
                ans = ans.sub(K * sum + 1);
            }
            else if(num == 1 && sum >= 1) {
                ans = ans.add(dp[sum]);
                ans = ans.sub(sum + 1);
            }
            else if(sum >= 0) ans = ans.add(dp[sum]);
        }
        else if(step % 2 == ss && step % 2){
            if(num == 0 && sum >= 2) {
                ans = ans.add(K * sum + 1);                
                ans = ans.sub(dp[sum]);
            }
            else if(num == 1 && sum >= 1) {
                ans = ans.add(sum + 1);                
                ans = ans.sub(dp[sum]);
            }
            else if(sum >= 0) ans = ans.sub(dp[sum]);
        }      
    }
    if(pos == M) return;
    dfs(X,state,step,sum,0,pos + 1,num,ss); 
    int Y[30];
    for(int i = 0; i < K; i ++) {
        Y[i] = max(X[i],a[pos][i]);
        if(Y[i] > X[i]) {
            sum += X[i];
            sum -= Y[i];
            if(!X[i] && Y[i]) num ++;
        }
    }
    dfs(Y,state | (1 << pos),step + 1,sum,1,pos + 1,num,ss);
}
            
void solve()
{
	
	scanf("%d%d%d",&K,&S,&M);
	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < K; j ++) {
			scanf("%d",&a[i][j]);
            a[i][j] = min(a[i][j],S + 1);
		}
	}
	for(int i = 0; i <= S; i ++) {
		if(i == 0) dp[i] = c[i + K - 1][K - 1];
		else dp[i] = dp[i - 1].add(c[i + K - 1][K - 1]);
	}
	int X[30];
    memset(X,0,sizeof(X));
	ans.init();
    dfs(X,0,0,S,1,0,0,0);
    memset(X,0,sizeof(X));
    dfs(X,0,0,S,1,0,0,1);
	ans.output();
}

int main()
{
	for(int i = 1; i < (1 << 20); i ++)
		bit[i] = bit[i >> 1] + (i & 1);
	for(int i = 0; i < 10030; i ++) {
		c[i][0].a[0] = 1;
		if(i < 30) c[i][i].a[0] = 1;
		for(int j = 1; j < i && j < 30; j ++) {
			c[i][j] = c[i - 1][j].add(c[i - 1][j  - 1]);
		}
	}
	int t;
	bool flag = false;
	scanf("%d",&t);
	while(t --) {
		if(flag) printf("\n");
		flag = true;
		solve();
	}
	return 0;
}
