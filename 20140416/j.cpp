#include <bits/stdc++.h>
using namespace std;

const int N = 1111111;
const int inf = 1 << 20;
vector<int> vec[N];
map<int, int> mp[N];
int alloc;
int match[N];
char str[N];
int type[N];

void init() {
	memset(match, -1, sizeof(match));
	int st[N], top = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == '(') {
			st[top++] = i;
		} else if (str[i] == ')') {
			top--;
			match[st[top]] = i;
			match[i] = st[top];
		}
	}
	assert(top == 0);
}

void build(int p, int l, int r) {
	//cout << p << " " << l << " " << r << endl;
	if (l + 1 == r) {
		type[p] = 0;
	} else if (l + 2 == r) {
		type[p] = 1;
	} else {
		type[p] = 2;
		int lson = alloc++;
		int rson = alloc++;
		//cout << p << "'son = " << lson << " " << rson << endl;
		vec[p].push_back(lson);
		vec[p].push_back(rson);
		build(lson, l + 1, match[l + 1]);
		build(rson, match[r - 1], r - 1);
	}
}

int dfs(int u, int balls) {
	if (mp[u].count(balls)) {
		return mp[u][balls];
	}
	if (type[u] != 2) {
		if (balls >= 2) return 1 << 25;
		return mp[u][balls] = abs(balls - type[u]);
	} else {
		assert((int) vec[u].size() == 2);
		int res = 1 << 20;
		int half = balls >> 1;
		if (balls & 1) {
			res = min(res, dfs(vec[u][0], half) + dfs(vec[u][1], half + 1));
			res = min(res, dfs(vec[u][0], half + 1) + dfs(vec[u][1], half));
		} else {
			res = min(res, dfs(vec[u][0], half) + dfs(vec[u][1], half));
		}
		return mp[u][balls] = res;
	}
}

void solve() {
	init();
	alloc = 0;
	int len = strlen(str);
	for (int i = 0; i < N; i++) { vec[i].clear(); }
	build(alloc++, 0, len - 1);
	int balls = 0;
	for (int i = 0; i < len; i++) { balls += str[i] == 'B'; }
	for (int i = 0; i < alloc; i++) { 
		//cout << i << " " << type[i] << endl;
		mp[i].clear();
   	}
	//cout << alloc << endl;
	int ans = dfs(0, balls);
	if (ans == (1 << 20)) {
		puts("impossible");
	} else {
		printf("%d\n", ans / 2);
	}
}

int main() {
	while (~scanf("%s", str)) {
		solve();
	}
	return 0;
}
