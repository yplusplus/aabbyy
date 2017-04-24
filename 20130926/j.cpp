#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = -1000000000;
int dp[201][100][35][8];

void update(int &x,int y)
{
	x = max(x,y);
}

void solve()
{
	for(int i = 0; i < 201; i ++)
		for(int j = 0; j < 100; j ++)
			for(int k = 0; k < 35; k ++)
				for(int r = 0; r < 8; r ++) dp[i][j][k][r] = oo;
	int T,HS,A,R,U,D,FI,P;
	int def[210];
	cin >> T >> HS >> A >> R >> U >> D >> FI >> P;
	for(int i = 1; i <= T; i ++) cin >> def[i];
	dp[0][0][0][0] = 0;
	for(int i = 0; i < T; i ++)
		for(int j = 0; D * j < HS; j ++)
			for(int k = 0; k < 35; k ++) {
				for(int r = 0; r < 7; r ++) {
					if(dp[i][j][k][r] < 0) continue;
					int newA = (D * j) / R * U + A;
					int cost = 0;
					if(newA >= def[i + 1]) cost += newA - def[i + 1];
					cost += k * FI;
					int newr = 6;
					int newk = k + 1;
					update(dp[i + 1][j + 1][newk][newr],dp[i][j][k][r] + cost);
					
					cost = 0;
					if(newA >= def[i + 1]) cost += newA - def[i + 1];
					cost += k * FI;
					newr = r;
					if(newr) newr --;
					newk = k;
					if(!newr) newk = 0;
					update(dp[i + 1][j][newk][newr],dp[i][j][k][r] + cost);
				}
			}
	int ans = 0;
	for(int j = 0; j * D < HS; j ++)
		for(int k = 0; k < 35; k ++)
			for(int r = 0; r < 7; r ++)
				if(dp[T][j][k][r] < 0) continue;
				else {
					update(ans,dp[T][j][k][r] - j * D * P);
				}
	cout << ans << endl;
}


	
int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		printf("Case #%d: ",cas);
		solve();
	}
	return 0;
}

