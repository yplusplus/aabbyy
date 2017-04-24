#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 5555;
typedef pair<int, int> pii;
pii seg[N];
int n;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d", &seg[i].first, &seg[i].second);
		sort(seg, seg + n);
		int now = 0;
		int pos = 0;
		int ans = 0;
		priority_queue<int> que;
		while (now < n) {
			while (pos < n && seg[pos].first <= now + 1) {
				que.push(seg[pos].second);
				pos++;
			}
			now = que.top();
			que.pop();
			ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
