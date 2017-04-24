#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int val[N];
int input[N];
int output[N];
int t[N];
vector<int> in[N];
int n, g, m;
int error[N];
vector<pair<int, int> > can[1 << 10];

int char2int(char ch) {
	if (ch == 'a') return 0;
	if (ch == 'o') return 1;
	if (ch == 'x') return 2;
	//if (type[0] == 'n') 
	return 3;
}

int str2int(string str) {
	int res = 0;
	if (str[0] == 'g') res += n;
	res += atoi(str.substr(1, str.length() - 1).c_str());
	return res;
}

int dfs(int u) {
	if (u > n + g) return val[u] = dfs(in[u][0]);
	if (u >= 1 && u <= n) return input[u];
	if (val[u] != -1) return val[u];
	int res;
	if (t[u] == 0) {
		res = 1;
		for (int i = 0; i < in[u].size(); i++) { res &= dfs(in[u][i]); }
	} else if (t[u] == 1) {
		res = 0;
		for (int i = 0; i < in[u].size(); i++) { res |= dfs(in[u][i]); }
	} else if (t[u] == 2) {
		res = 0;
		for (int i = 0; i < in[u].size(); i++) { res ^= dfs(in[u][i]); }
	} else {
		res = dfs(in[u][0]);
		res = !res;
	}
	if (error[u] == 1) res = !res;
	else if (error[u] == 2) res = 0;
	else if (error[u] == 3) res = 1;
	return val[u] = res;
}

bool check() {
	memset(val, -1, sizeof(val));
	for (int i = 1; i <= m; i++) {
		dfs(n + g + i);
	}
	for (int i = 1; i <= m; i++) {
		if (output[i] != val[n + g + i]) return false;
	}
	return true;
}

int main() {
	int Case = 1;
	while (~scanf("%d%d%d", &n, &g, &m), n && g && m) {
		for (int i = 0; i < N; i++) in[i].clear();
		for (int i = 1; i <= g; i++) {
			static char type[10], a[10], b[10];
			scanf("%s", type);
			int u = n + i;
			if (type[0] == 'a') {
				scanf("%s%s", a, b);
				in[u].push_back(str2int(a));
				in[u].push_back(str2int(b));
			} else if (type[0] == 'o') {
				scanf("%s%s", a, b);
				in[u].push_back(str2int(a));
				in[u].push_back(str2int(b));
			} else if (type[0] == 'x') {
				scanf("%s%s", a, b);
				in[u].push_back(str2int(a));
				in[u].push_back(str2int(b));
			} else if (type[0] == 'n') {
				scanf("%s", a);
				in[u].push_back(str2int(a));
			}
			t[u] = char2int(type[0]);
		}
		for (int i = 1; i <= m; i++) {
			int a;
			scanf("%d", &a);
			int u = n + g + i;
			in[u].push_back(a + n);
		}
		//for (int i = 1; i <= g; i++) { cout << n + i; for (int j = 0; j < in[n + i].size(); j++) { cout << " " << in[n + i][j]; } cout << endl; }
		int B;
		scanf("%d", &B);
		for (int i = 0; i <= B; i++) can[i].clear();
		memset(error, 0, sizeof(error));
		for (int j = 1; j <= B; j++) {
			for (int i = 1; i <= n; i++) { scanf("%d", &input[i]); }
			for (int i = 1; i <= m; i++) { scanf("%d", &output[i]); }
			if (check()) can[j].push_back(pair<int, int>(0, 0));
			for (int i = 1; i <= g; i++) {
				int u = n + i;
				for (int k = 1; k <= 3; k++) {
					error[u] = k;
					if (check()) can[j].push_back(pair<int, int>(i, k));
				}
				error[u] = 0;
			}
		}
		for (int i = 2; i <= B; i++) {
			can[0].clear();
			for (int j = 0; j < can[1].size(); j++) {
				for (int k = 0; k < can[i].size(); k++) {
					if (can[1][j] == can[i][k]) {
						can[0].push_back(can[1][j]);
					}
				}
			}
			swap(can[0], can[1]);
		}
		sort(can[1].begin(), can[1].end());
		printf("Case %d: ", Case++);
		if (can[1][0].first == 0) {
			puts("No faults detected");
		} else if (can[1].empty() || can[1].size() >= 2) {
			puts("Unable to totally classify the failure");
		} else {
			assert(can[1][0].first >= 1 && can[1][0].first <= g);
			printf("Gate %d is failing; ", can[1][0].first);
			if (can[1][0].second == 1) puts("output inverted");
			if (can[1][0].second == 2) puts("output stuck at 0");
			if (can[1][0].second == 3) puts("output stuck at 1");
		}
	}
	return 0;
}
