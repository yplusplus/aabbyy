#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

double dp[2][35][35];
int dir[4][2] = {0,1,0,-1,1,0,-1,0};
double ans[35][35];
const int times = 3000;
const double eps = 1e-6;
int main()
{
	int n;
	double p;
	//int times;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%lf", &n, &p);

		p /= 100;
		memset(dp,0,sizeof(dp));
		dp[0][(n + 1) / 2][(n + 1) / 2] = 1;
		memset(ans, 0, sizeof(ans));
		for(int i = 0; i < times; i ++) {
			//cout << i << endl;
			memset(dp[i & 1 ^ 1], 0, sizeof(dp[i & 1 ^ 1]));
			for(int j = 1; j <= n; j ++) {
				for(int k = 1; k <= n; k ++) {
					for(int r = 0; r < 4; r ++) {
						int tx = j + dir[r][0];
						int ty = k + dir[r][1];
						if (tx == 0 || tx == n + 1 || ty == 0 || ty == n + 1) ans[tx][ty] += dp[i & 1][j][k] / 4.0;
						else dp[i & 1 ^ 1][tx][ty] += dp[i & 1][j][k] / 4.0;
					}
				}
			}
		}
		//for (int i = 1; i <= n; i++) {
			//cout << ans[0][i] << " ";
		//}
		//cout << endl;
		priority_queue<double> que;
		for (int i = 1; i <= n; i++) {
			que.push(ans[0][i]);
			que.push(ans[n + 1][i]);
			que.push(ans[i][0]);
			que.push(ans[i][n + 1]);
		}
		//cout << que.size() << endl;
		int cnt = 0;
		while (true) {
			if (p < eps || que.empty()) break;
			cnt++;
			p -= que.top();
			que.pop();
		}
		printf("%d\n", cnt);
		/*
		   for(int i = 1; i <= times; i ++) {
		   for(int j = 0; j <= n + 1; j ++)
		   for(int k = 0; k <= n + 1; k ++)
		   if(j == 0 || k == 0 || j == n + 1 || k == n + 1) ans += dp[i][j][k];
		   }
		   cout << ans << endl;
		 */
		//for(int i = 1; i <= n; i ++) {
			//double tot = 0;
			//for(int j = 0; j <= times; j ++) {
				//tot += dp[j][0][i];
			//}
			//printf("%.10lf ",1 / tot);
		//}
		//cout << endl;
	}
	return 0;
}
