#include <bits/stdc++.h>
using namespace std;

const int N = 55;
vector<int> plate[N], id[N * N], diameter;
int dp[N * N][N];
int n, m;
inline int getID(int x) { return lower_bound(diameter.begin(), diameter.end(), x) - diameter.begin(); }
inline bool hasID(int a, int b) { return binary_search(id[a].begin(), id[a].end(), b); }
inline void update(int &a, int b) { a = max(b, a); }

int run() {
	int cas = 0;
	while (cin >> n) {
		int cntSplit = 0;
		diameter.clear();
		for (int i = 0; i < N * N; ++i) id[i].clear();
		for (int i = 0, k; i < n; ++i) {
			cin >> k;
			plate[i].resize(k);
			for (int j = 0; j < k; ++j) {
				cin >> plate[i][j];
				diameter.push_back(plate[i][j]);
			}
			sort(plate[i].begin(), plate[i].end());
			plate[i].resize(unique(plate[i].begin(), plate[i].end()) - plate[i].begin());
			cntSplit += plate[i].size() - 1;
			//cout << cntSplit << endl;
		}
		sort(diameter.begin(), diameter.end());
		m = unique(diameter.begin(), diameter.end()) - diameter.begin();
		diameter.resize(m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < plate[i].size(); ++j) {
				id[getID(plate[i][j])].push_back(i);
			}
		}
		for (int i = 0; i < m; ++i) {
			sort(id[i].begin(), id[i].end());
			id[i].resize(unique(id[i].begin(), id[i].end()) - id[i].begin());
			//cout << diameter[i] << ": "; for (int j = 0; j < id[i].size(); ++j) cout << id[i][j] << ' '; cout << endl;
		}
		memset(dp, 0, sizeof dp);
		for (int i = 1; i < m; ++i) {
			int maxElem = *max_element(dp[i - 1], dp[i - 1] + n);
			for (int j = 0; j < n; ++j) {
				if (hasID(i - 1, j) && hasID(i, j)) {
					if (id[i - 1].size() == 1) {
						update(dp[i][j], dp[i - 1][j] + 1);
					}
					for (int k = 0; k < n; ++k) {
						if (k == j) continue;
						update(dp[i][j], dp[i - 1][k] + 1);
					}
				} else {
					dp[i][j] = maxElem;
				}
			}
		}
		//for (int i = 0; i < m; ++i) { for (int j = 0; j < n; ++j) { cout << dp[i][j] << ' '; } cout << endl; }
		//cout << cntSplit << ' ' << *max_element(dp[m - 1], dp[m - 1] + n) << ' ' << n << endl;
		cntSplit -= *max_element(dp[m - 1], dp[m - 1] + n);
		cout << "Case " << ++cas << ": " << ((cntSplit + n << 1) - n - 1) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
