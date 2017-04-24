#include <bits/stdc++.h>
using namespace std;

const int N = 77;
typedef bitset<N> BS;
int best[N], current[N], bestSize, id[N];
vector<BS> matrix;

void convert(const string &s, BS &bs) {
	bs.reset();
	for (unsigned i = 0; i < s.length(); ++i) {
		bs[i] = s[i] & 1;
	}
}

BS endStatus;
void dfs(int position, int total, int n, const BS &status) {
	if (bestSize <= total) return ;
	if (status == endStatus) {
		if (bestSize > total) {
			bestSize = total;
			for (int i = 0; i < total; ++i) {
				best[i] = current[i];
			}
		}
		return ;
	}
	if (position >= n) return ;
	if ((status & matrix[id[position]]) != matrix[id[position]]) {
		current[total] = id[position] + 1;
		dfs(position + 1, total + 1, n, status | matrix[id[position]]);
	}
	dfs(position + 1, total, n, status);
}

inline bool cmp(int a, int b) { return matrix[a].count() > matrix[b].count(); }

int run() {
	string temp;
	int n, cas = 0;
	while (cin >> n) {
		matrix.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> temp;
			convert(temp, matrix[i]);
			matrix[i][i] = 1;
		}
		bestSize = INT_MAX;
		endStatus = BS(string(n, '1'));
		for (int i = 0; i < n; ++i) {
			id[i] = i;
		}
		sort(id, id + n, cmp);
		//for (int i = 0; i < n; ++i) { cout << id[i] << ' '; } cout << endl;
		dfs(0, 0, n, BS());
		cout << "Case " << ++cas << ": " << bestSize;
		for (int i = 0; i < bestSize; ++i) {
			cout << ' ' << best[i];
		}
		cout << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}