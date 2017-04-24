#include <bits/stdc++.h>
using namespace std;

vector<int> prime;
map<int, long long> dp[155][155];
int mask[155];

bool is_prime(int x) {
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

long long dfs(int u, int state, int start) {
	if (u == 0) return 1;
	if (start > u) return 0;
	if (dp[u][start].count(state)) { return dp[u][start][state]; }
	long long res = 0;
	if (!(mask[start] & state)) res += dfs(u - start, state | mask[start], start + 1); 
	res += dfs(u, state, start + 1);
	dp[u][start][state] = res;
	return res;
}

int main() {
	for (int i = 2; i <= 75; i++) {
		if (is_prime(i)) prime.push_back(i);
	}
	memset(mask, 0, sizeof(mask));
	for (int i = 2; i <= 150; i++) {
		for (int j = 0; j < prime.size(); j++) {
			if (i % prime[j] == 0) mask[i] |= 1 << j;
		}
		//cout << i << " " << mask[i] << endl;
	}
	//cout << prime.size() << endl;
	int n;
	freopen("out.cpp","w",stdout);
	for(n = 1; n <= 150; n ++) {
		long long ans = 0;
		for (int i = 0; i <= n; i++) {
			ans += dfs(n - i, 0, 2);
		}
		cout << ans << ',';
	}
	return 0;
}
