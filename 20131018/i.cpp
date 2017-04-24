#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
bool visit[N];
int n, T;
struct Costomer {
	int m, l, k;
	void read() {
		scanf("%d%d%d", &m, &l, &k);
	}
} c[N];

bool check(int mid) {
	int supported = 0;
	int cnt = mid;
	priority_queue<int, vector<int>, greater<int> > pq;
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < cnt; i++) {
		pq.push(0);
	}
	cnt = 0;
	for (int i = 0; i <= T; i++) {
		while (!pq.empty() && pq.top() == i) {
			pq.pop();
			cnt++;
		}
		for (int j = 0; j < n && cnt; j++) {
			if (visit[j]) continue;
			int t = i % (c[j].l + c[j].k);
			//if (t == 0) t = c[j].l + c[j].k;
			if (t <= c[j].l) {
				if (i + c[j].m > T) return false;
				pq.push(i + c[j].m);
				visit[j] = true;
				cnt--;
				if (++supported == n) return true;
			}
		}
	}
	return false;
}

int main() {
	while (~scanf("%d%d", &n, &T), n + T) {
		for (int i = 0; i < n; i++) c[i].read();
		int l = 1, r = n;
		int ans = n;
		for(int i = 1; i <= n; i ++)
			if(check(i)) {
				ans = i;
				break;
			}
		/*
		while (l <= r) {
			int mid = l + r >> 1;
			if (check(mid)) ans = mid, r = mid - 1;
			else l = mid + 1;
		}*/
		printf("%d\n", ans);
	}
	return 0;
}

