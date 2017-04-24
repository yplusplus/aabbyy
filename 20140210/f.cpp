#include <bits/stdc++.h>
using namespace std;

long long dp[1 << 16][16][5];
vector<int> v[1 << 16];
int len[1 << 16];
int main()
{
	int a[35][35];
	for(int i = 0; i < (1 << 16); i ++)
		for(int j = 0; j < 16; j ++)
			if(i & (1 << j)) v[i].push_back(j);
	int n,m;
	scanf("%d%d",&n,&m);
	-- m;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			scanf("%d",&a[i][j]);
	for(int i = 0; i < n; i ++) dp[1 <<i][i][0] = 1;
	int height = 0;
	for(height; (1 << height) < n; height ++);
    for(int i = 1; i < (1 << 16); i ++)
        for(int j = 0; ; j ++)
            if((1 << j) >= v[i].size()) {
                len[i] = j;
                break;
            }
    //double t1 = clock() * 1.0 / CLOCKS_PER_SEC;
	for(int h = 1; h <= height; h ++) {
		for(int i = 1; i < (1 << n); i ++) {
            if(h == 1 && v[i].size() > 2) continue;
            if(h == 2 && v[i].size() != 3 && v[i].size() != 4) continue;
            if(h == 3 && !(v[i].size() <= 8)) continue;
            //if(h == 2 && v[i].size() != 4 && v[i].size() != n % 4) continue;
            if(h == height && (v[i].size() != n)) continue;
			for(int j = 0; j < n; j ++) {
				if(!(i & (1 << j))) continue;
				if(i & (1 << m)) {
					if(j != m) continue;
				}
				for(int st1 = (i - 1) & i; st1; st1 = (st1 - 1) & i) {
					int st2 = i ^ st1;
					if(st1 > st2) continue;
                    if(len[st2] != h - 1 && len[st1] != h - 1) continue;
					if(st1 & (1 << j)) {
						for(int k = 0; k < v[st2].size(); k ++) {
							int x = v[st2][k];
							if(!a[j][x]) continue;
                            if(!dp[st1][j][h - 1] && !dp[st2][x][h - 1]) continue;
							for(int hh = len[st2]; hh <= len[st2] + 1 && hh <= h - 1; hh ++)
								dp[i][j][h] += dp[st1][j][h - 1] * dp[st2][x][hh];
							for(int hh = len[st1]; hh + 1 < h && hh <= len[st1] + 1; hh ++)
								dp[i][j][h] += dp[st1][j][hh] * dp[st2][x][h - 1];
						}
					}
					else {
						for(int k = 0; k < v[st1].size(); k ++) {
							int x = v[st1][k];
							if(!a[j][x]) continue;
                            if(!dp[st1][x][h - 1] && !dp[st2][j][h - 1]) continue;
							for(int hh = len[st2]; hh < h && hh <= len[st2] + 1; hh ++)
								dp[i][j][h] += dp[st1][x][h - 1] * dp[st2][j][hh];
							for(int hh = len[st1]; hh + 1 < h && hh <= len[st1] + 1; hh ++)
								dp[i][j][h] += dp[st1][x][hh] * dp[st2][j][h - 1];
						}
					}
				}
			}
		}
	}
	cout << dp[(1 << n) - 1][m][height] << endl;
    //double t2 = clock() * 1.0 / CLOCKS_PER_SEC;
    //cout << t2 - t1 << endl;
	return 0;
}


