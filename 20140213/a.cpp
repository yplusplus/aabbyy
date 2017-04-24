#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Node;

int main() {
	int n;
	ios::sync_with_stdio(0);
	while (cin >> n && n) {
		Node ans(0, 0);
		int l, w, h;
		for (int i = 0; i < n; i++) {
			cin >> l >> w >> h;
			ans = max(Node(h, l * w * h), ans);
		}
		cout << ans.second << endl;
	}
	return 0;
}
