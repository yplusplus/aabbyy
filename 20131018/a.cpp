#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1111;
const int INF = 0x77777777;
typedef pair<int, int> PII;
typedef pair<PII, string> PIS;
PIS year[N];
int n, m;

int main() {
	ios::sync_with_stdio(0);
	int n, m;
	while (cin >> n >> m && (n || m)) {
		string buf;
		int x, y;
		for (int i = 0; i < n; i++) {
			cin >> buf >> x >> y;
			year[i] = PIS(PII(y - x + 1, x), buf);
		}
		sort(year, year + n);
		for (int i = 0; i < m; i++) {
			cin >> x;
			int id = upper_bound(year, year + n, PIS(PII(x, INF), "")) - year;
			id--;
			if (id >= 0) {
				if (x - year[id].first.first + 1 <= year[id].first.second) cout << year[id].second << ' ' << x - year[id].first.first + 1 << endl;
				else cout << "Unknown" << endl;
			} else cout << "Unknown" << endl;
		}
	}
	return 0;
}

