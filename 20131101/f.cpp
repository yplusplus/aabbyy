#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 15;
int n;
int belong[N][N];
int cnt[N * N];
int ans[N][N];
bool visit[N * N];
int tot;
ll k;

ll calc() {
	ll res = 1;
	for (int i = 0; i < tot; i++) {
		if (!visit[i]) {
			res *= cnt[i];
		}
	}
	return res;
}

int main() {
	while (cin >> n >> k) {
		memset(belong, -1, sizeof(belong));
		tot = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (belong[i][j] != -1) continue;
				belong[i][j] = tot;
				int x = i, y = j;
				int t;
				for (int k = 0; k < 3; k++) {
					t = x;
					x = y;
					y = n - 1 - t;
					belong[x][y] = tot;
				}
				tot++;
			}
		}
		for (int i = 0; i < tot; i++) cnt[i] = 4;
		memset(visit, false, sizeof(visit));
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visit[belong[i][j]]) {
					ans[i][j] = 0;
					continue;
				}
				cnt[belong[i][j]]--;
				ll ret = calc();
				//cout << ret << endl;
				if (ret >= k) {
					ans[i][j] = 0;
				} else {
					visit[belong[i][j]] = true;
					ans[i][j] = 1;
					k -= ret;
				}
			}
		}
		int sum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << ans[i][j];
				sum += ans[i][j];
			}
			cout << endl;
		}
		//cout << sum << endl;
	}
}
