#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
const int M = 3;
typedef long long ll;
const ll KEY1[M] = {100003, 400009, 31};
const ll KEY2[M] = {786433, 131, 200003}; 
const ll MOD[M] = {(long long)1e9 + 7, 1600033, 15485863};
const ll delta[M] = {6400013, 97, 113};

vector<int> vec[N];
int son[N];
int id[N];
int dep[N];
int n;

struct Node {
	ll h[M];
	Node() { for (int i = 0; i < M; i++) h[i] = 0; }
	bool operator <(const Node &x) const {
		for (int i = 0; i < M; i++) {
			if (h[i] != x.h[i]) return h[i] < x.h[i];
		}
		return false;
	}
	bool operator == (const Node &x) const {
		for (int i = 0; i < M; i++) {
			if (h[i] != x.h[i]) return false;
		}
		return true;
	}
} val[N];
map<Node, int> mp;

bool cmp(int x, int y) { return val[x] < val[y]; }

void dfs(int u) {
	dep[u] = 0;
	son[u] = 1;
	for (int i = 0; i < vec[u].size(); i++) { 
		int v = vec[u][i];
		dfs(v);
		dep[u] = max(dep[u], dep[v] + 1);
		son[u] += son[v];
   	}
	sort(vec[u].begin(), vec[u].end(), cmp);
	Node res;
	for (int i = 0; i < vec[u].size(); i++) {
		for (int j = 0; j < M; j++) {
			res.h[j] = (res.h[j] * KEY1[j] + KEY2[j] * val[vec[u][i]].h[j]) % MOD[j];
		}
	}
	for (int i = 0; i < M; i++) {
		res.h[i] = (res.h[i] + son[u] * delta[i] + dep[u]) % MOD[i];
	}
	val[u] = res;
	if (mp.count(val[u])) id[u] = mp[val[u]];
	else {
		int sz = (int)mp.size() + 1;
		mp[val[u]] = sz;
		id[u] = sz;
	}
}

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) vec[i].clear();
	for (int i = 2, fa; i <= n; i++) {
		cin >> fa;
		vec[fa].push_back(i);
	}
	mp.clear();
	dfs(1);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < M; j++) {
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << id[i];
		if (i == n) cout << endl;
		else cout << ' ';
	}
	return 0;
}
