#include <bits/stdc++.h>
using namespace std;

const int N = 3333;
char s[N], t[N];
int slen, tlen;
int dp[N][N];
int mi[N][N];
pair<int, int> pre[N][N];
const int inf = 1 << 28;
int B, C, D, I;

void check(int a, int b, int c, int d) {
	if (mi[a][b] == -1 || dp[mi[a][b]][b] > d) {
		mi[a][b] = c;
	}
}

void update(int a, int b, int c, int d, int e) {
	if (dp[a][b] > e) {
		dp[a][b] = e;
		pre[a][b] = pair<int, int>(c, d);
		int t = mi[a][b];
	}
}

string ans_str;
vector<pair<int, int> > seg;

void dfs(int a, int b) {
	if (!a && !b) return;
	int c = pre[a][b].first;
	int d = pre[a][b].second;
	if (d == b) {
		if (c + 1 == a) {
			if (D < B) {
				ans_str += 'D';
			} else {
				seg.push_back(pair<int, int>(c + 1, a));
			}
		} else {
			seg.push_back(pair<int, int>(c + 1, a));
		}
	} else {
		if (a == c) {
			ans_str += 'I';
		} else {
			ans_str += 'C';
		}
	}
	dfs(c, d);
}

void solve() {
	slen = strlen(s + 1);
	tlen = strlen(t + 1);
	memset(pre, -1, sizeof(pre));
	for (int i = 0; i <= slen; i++) {
		for (int j = 0; j <= tlen; j++) {
			dp[i][j] = inf;
		}
	}
	memset(mi, -1, sizeof(mi));
	mi[0][0] = 0;
	dp[0][0] = 0;
	for (int j = 0; j <= tlen; j++) {
		for (int i = 0; i <= slen; i++) {
			if (i == 0 && j == 0) continue;
			if (i && j && s[i] == t[j]) {
				update(i, j, i - 1, j - 1, dp[i - 1][j - 1] + C);
			}
			if (j) update(i, j, i, j - 1, dp[i][j - 1] + I);
			if (i) update(i, j, i - 1, j, dp[i - 1][j] + D);
			if (i && mi[i - 1][j] != -1) update(i, j, mi[i - 1][j], j, dp[mi[i - 1][j]][j] + B);
			mi[i][j] = mi[i - 1][j];
			check(i, j, i, dp[i][j]);
			//cout << i << " " << j << endl;
		}
	}
	/*
	for (int i = 0; i <= slen; i++) {
		for (int j = 0; j <= tlen; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	*/
	printf("%d\n", dp[slen][tlen]);
	seg.clear();
	ans_str = "";
	dfs(slen, tlen);
	reverse(seg.begin(), seg.end());
	reverse(ans_str.begin(), ans_str.end());
	printf("%d\n", (int) seg.size());
	for (int i = 0; i < seg.size(); i++) {
		printf("%d %d\n", seg[i].first, seg[i].second);
	}
	printf("%s\n", ans_str.c_str());
}

int main() {
	freopen("block.in", "r", stdin);
	freopen("block.out", "w", stdout);
	scanf("%d%d%d%d", &B, &I, &D, &C);
	scanf("%s%s", s + 1, t + 1);
	solve();
	return 0;
}
