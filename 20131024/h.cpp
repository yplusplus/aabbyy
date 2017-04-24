#include <bits/stdc++.h>
using namespace std;

map<string, int> id;
const int N = 333;
string name[N];
vector<int> vec[N];
int alloc;
int rank[N];
void solve() {
	memset(rank, -1, sizeof(rank));
	queue<int> que;
	if (id.count("Isenbaev") != 0) {
		int s = id["Isenbaev"];
		que.push(s);
		rank[s] = 0;
	}
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i];
			if (rank[v] == -1) {
				rank[v] = rank[u] + 1;
				que.push(v);
			}
		}
	}
	for (map<string, int>::iterator it = id.begin(); it != id.end(); it++) {
		cout << it->first << " ";
		if (rank[it->second] == -1) cout << "undefined" << endl;
		else cout << rank[it->second] << endl;
	}
}

int main() {
	int n;
	while (cin >> n) {
		int a[3];
		string str;
		alloc = 0;
		id.clear();
		for (int i = 0; i < N; i++) vec[i].clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> str;
				if (id.count(str) == 0) {
					id[str] = ++alloc;
				}
				a[j] = id[str];
				name[a[j]] = str;
				for (int k = 0; k < j; k++) {
					vec[a[j]].push_back(a[k]);
					vec[a[k]].push_back(a[j]);
				}
			}
		}
		solve();
	}
	return 0;
}

