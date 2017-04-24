#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
const int M = 5;
bool dp[N][M];
pair<int, int> pre[N][M];

char str[N];
int cnt[N];

//state
//0
//1 - b
//2 - i
//3 - bi
//4 - ib

int change(int state, int type) {
	if (state == 0) return type;
	if (state == 1) return type == 1 ? 0 : 3;
	if (state == 2) return type == 2 ? 0 : 4;
	if (state == 3) return type == 2 ? 1 : -1;
	if (state == 4) return type == 1 ? 2 : -1;
	return -1;
}

string ans_str;
void get_path(int a, int b) {
	if (a == 0) return;
	int na = pre[a][b].first, nb = pre[a][b].second;
	get_path(na, nb);
	if (b == nb) {
		ans_str += str[na];
	} else {
		if (nb == 0) {
			if (b == 1) ans_str += "<b>";
			else if (b == 2) ans_str += "<i>";
		}  else if (nb == 1) {
			if (b == 0) ans_str += "</b>";
			else if (b == 3) ans_str += "<i>";
		} else if (nb == 2) {
			if (b == 0) ans_str += "</i>";
			else if (b == 4) ans_str += "<b>";
		} else if (nb == 3) {
			ans_str += "</i>";
		} else if (nb == 4) {
			ans_str += "</b>";
		}
	}
}

int main() {
	freopen("wikipidia.in", "r", stdin);
	freopen("wikipidia.out", "w", stdout);
	gets(str);
	int n = strlen(str);
	memset(cnt, 0, sizeof(cnt));
	for (int i = n - 1; i >= 0; i--) {
		if (str[i] == '\'') {
			cnt[i] = 1 + cnt[i + 1];
		}
	}
	memset(dp, 0, sizeof(dp));
	memset(pre, -1, sizeof(pre));
	dp[0][0] = 1;
	//pre[0][0] = pair<int, int>(-1, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < M; j++) {
			if (!dp[i][j]) continue;
			if (cnt[i] == 0) {
				dp[i + 1][j] = 1;
				pre[i + 1][j] = pair<int, int>(i, j);
			} else {
				if (cnt[i] >= 2) {
					int nj = change(j, 2);
					if (nj != -1) {
						dp[i + 2][nj] = 1;
						pre[i + 2][nj] = pair<int, int>(i, j);
					}
				}
				if (cnt[i] >= 3) {
					int nj = change(j, 1);
					if (nj != -1) {
						dp[i + 3][nj] = 1;
						pre[i + 3][nj] = pair<int, int>(i, j);
					}
				}
			}
		}
	}
	bool valid = dp[n][0];
	if (valid) {
		ans_str = "";
		get_path(n, 0);
		puts(ans_str.c_str());
	} else {
		puts("!@#$%");
	}
	return 0;
}
