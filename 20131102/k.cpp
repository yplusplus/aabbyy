#include <bits/stdc++.h>
using namespace std;

const int N = 1111;

string name[N];
int rank[N], type[N];
vector<int> vec[N];
bool visit[N];
int match[N];
int n;

bool check(int x, int y) {
	if (abs(rank[x] - rank[y]) != 2) return false;
	if (type[x] == 0 || type[y] == 0 || type[x] + type[y] == 3) return true;
	return false;
}

bool dfs(int u) {
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (visit[v]) continue;
		visit[v] = true;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int Match() {
	memset(match, -1, sizeof(match));
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (rank[i] % 4 < 2) {
			memset(visit, false, sizeof(visit));
			res += dfs(i);
		}
	}
	return res;
}
int main() {
	ios::sync_with_stdio(false);
	while (cin >> n) {
		string str;
		for (int i = 0; i < n; i++) {
			cin >> name[i] >> str >> rank[i];
			if (str[0] == 'a') type[i] = 0;
			else if (str[0] == 's') type[i] = 1;
			else type[i] = 2;
		}
		for (int i = 0; i < n; i++) {
			if (rank[i] % 4 < 2) {
				vec[i].clear();
				for (int j = 0; j < n; j++) {
					if (rank[j] % 4 >= 2 && check(i, j)) {
						vec[i].push_back(j);
					}
				}
			}
		}
		int ret = Match();
		cout << ret << endl;
		for (int i = 0; i < n; i++) {
			if (rank[i] % 4 >= 2 && match[i] != -1) {
				int j = match[i];
				if (type[i] == 1 || type[j] == 2) {
					cout << name[i] << " " << name[j] << endl;
				} else {
					cout << name[j] << " " << name[i] << endl;
				}
			}
		}
	}
	return 0;
}
