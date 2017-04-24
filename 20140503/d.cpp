#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int min_cut[N][N];
int n;

vector<pair<pair<int, int>, int> > tree_edge;

bool solve(const vector<int> &vec) {
	//cout << vec.size() << endl;
	if (vec.size() == 1) return true;
	int d = INT_MAX;
	int u = -1, v = -1;
	vector<int> points[2];
	for (int i = 0; i < vec.size(); i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (d > min_cut[vec[i]][vec[j]]) {
				d = min_cut[vec[i]][vec[j]];
				u = vec[i];
				v = vec[j];
			}
		}
	}
	points[0].push_back(u);
	points[1].push_back(v);
	tree_edge.push_back(make_pair(make_pair(u, v), d));
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == u || vec[i] == v) continue;
		if (min_cut[u][vec[i]] > d) {
			points[0].push_back(vec[i]);
		} else {
			points[1].push_back(vec[i]);
		}
	}
	for (int i = 0; i < points[0].size(); i++) {
		for (int j = 0; j < points[1].size(); j++) {
			if (min_cut[points[0][i]][points[1][j]] > d) return false;
		}
	}
	return solve(points[0]) && solve(points[1]);
}

int main() {
	ios::sync_with_stdio(false);
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> min_cut[i][j];
		}
	}
	vector<int> vec;
	for (int i = 1; i <= n; i++) vec.push_back(i);
	tree_edge.clear();
	if (solve(vec)) {
		cout << "YES" << endl;
		cout << tree_edge.size() << endl;
		for (int i = 0; i < tree_edge.size(); i++) {
			cout << tree_edge[i].first.first << " " << tree_edge[i].first.second << " " << tree_edge[i].second << endl;
		}
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
