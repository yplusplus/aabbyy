#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> V2I;
typedef pair<int, int> PI2;
typedef priority_queue<PI2, vector<PI2>, greater<PI2> > PRIQ;
V2I packet;
VI message;
int n, m;
#define x first
#define y second

int cal(const VI &id, int n, int m) {
	vector<PRIQ> buffer(n + 1);
	VI buffer_size(n + 1, 0), output_start(n + 1, 1);
	int cur = 0, mx = 0;
	for (int i = 0; i < m; ++i) {
		buffer[packet[i][0]].push(PI2(packet[i][1], packet[i][2]));
		buffer_size[packet[i][0]] += packet[i][2] - packet[i][1] + 1;
		while (cur < n && !buffer[id[cur]].empty() && output_start[id[cur]] == buffer[id[cur]].top().x) {
			PI2 tmp = buffer[id[cur]].top();
			output_start[id[cur]] = tmp.y + 1;
			buffer_size[id[cur]] -= tmp.y - tmp.x + 1;
			buffer[id[cur]].pop();
			if (output_start[id[cur]] > message[id[cur]]) ++cur;
		}
		if (cur < n) mx = max(accumulate(buffer_size.begin(), buffer_size.end(), 0), mx);
	}
	//for (int i = 0; i < n; ++i) cout << id[i] << ' '; cout << mx << endl;
	return mx;
}

int run() {
	int cas = 0;
	while (cin >> n >> m && (n + m)) {
		message.clear();
		message.resize(n + 1);
		packet.clear();
		packet.resize(m, VI(3));
		for (int i = 1; i <= n; ++i) cin >> message[i];
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < 3; ++j) cin >> packet[i][j];
		}
		int ans = INT_MAX;
		VI arr(n);
		for (int i = 0; i < n; ++i) arr[i] = i + 1;
		do {
			ans = min(cal(arr, n, m), ans);
		} while (next_permutation(arr.begin(), arr.end()));
		cout << "Case " << ++cas << ": " << ans << endl << endl;
	}
	return 0;
}

int main() {
	//freopen("in_g", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
