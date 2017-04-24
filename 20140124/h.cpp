#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int N = 1111;
const int M = 222;

int tower[M][M];
int n, w, c, d;
double sw[N];

void update(pair<int, int> &a, pair<int, int> b) {
	if (a.first == -1 || a.first > b.first) a = b;
	else if (a.first == b.first) a.second += b.second;
}

int main() {
	while (~scanf("%d%d%d%d", &n, &w, &c, &d)) {
		memset(tower, 0, sizeof(tower));
		int h = 0;
		for (int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			tower[x][y] = i;
			h = max(h, x);
			sw[i] = 0;
		}
		pair<int, int> ans = make_pair(-1, -1);
		for (int i = h; i >= 0; i--) {
			for (int j = 0; j <= 200; j++) {
				if (tower[i][j] == 0) continue;
				int id = tower[i][j];
				int T = (int) ((c - (sw[id])) / d) + 1; 
				if (fabs(sw[id]) > 1e-6) {
					if (c < sw[id]) T = 0;
					update(ans, make_pair(T, 1));
				}
				if (i) {
					vector<int> vec;
					if (j - 1 >= 0 && tower[i - 1][j - 1]) vec.push_back(tower[i - 1][j - 1]);
					if (tower[i - 1][j + 1]) vec.push_back(tower[i - 1][j + 1]);
					for (int i = 0; i < vec.size(); i++) {
						sw[vec[i]] += (sw[id] + w) / (double) vec.size(); 
					}
				}
			}
		}
		if (ans.first == -1) puts("-1");
		else cout << ans.first << " " << ans.second << endl;
	}
	return 0;
}
