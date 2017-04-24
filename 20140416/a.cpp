#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
const int N = 1 << 11;
int minDist[N][N], answer[N][3], newDist[N][N];
int preVex[N], dist[N], n, ttAnswer;
bool visit[N];
VI nx[N];

void mst() {
	for (int i = 1, current = 1; i < n; ++i) {
		for (int j = 2; j <= n; j++) {
			if (dist[j] > minDist[current][j]) {
				dist[j] = minDist[current][j];
				preVex[j] = current;
			}
		}
		int mark = 0, best = INT_MAX;
		for (int j = 2; j <= n; ++j) {
			if (visit[j]) continue;
			if (best > dist[j]) {
				best = dist[j];
				mark = j;
			}
		}
		nx[preVex[mark]].push_back(mark);
		nx[mark].push_back(preVex[mark]);
		answer[ttAnswer][0] = preVex[mark];
		answer[ttAnswer][1] = mark;
		answer[ttAnswer][2] = dist[mark];
		++ttAnswer;
		current = mark;
		visit[mark] = 1;
	}
}

void init(int n) {
	ttAnswer = 0;
	for (int i = 1; i <= n; ++i) memset(minDist, 0, n + 2 << 2);
	for (int i = 1; i <= n; ++i) nx[i].clear();
	for (int i = 1; i <= n; ++i) dist[i] = INT_MAX;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) newDist[i][j] = INT_MAX;
	memset(visit, 0, sizeof visit);
}

int current;
void dfs(int x, int fa, int d) {
	newDist[current][x] = newDist[x][current]= d;
	for (int i = 0, size = nx[x].size(); i < size; ++i) {
		int &y = nx[x][i];
		if (y == fa) continue;
		dfs(y, x, d + minDist[x][y]);
	}
}

int run() {
	bool pnt = 0;
	while (cin >> n) {
		if (pnt) cout << endl;
		else pnt = 1;
		init(n);
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cin >> minDist[i][j];
		mst();
		for (int i = 1; i <= n; ++i) dfs(current = i, -1, 0);
		//for (int i = 1; i <= n; ++i) { for (int j = 1; j <= n; ++j) cout << newDist[i][j] << ' '; cout << endl; }
		int minEdge = INT_MAX, u, v;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (minDist[i][j] == newDist[i][j]) continue;
				if (minEdge > minDist[i][j]) {
					minEdge = minDist[i][j];
					u = i, v = j;
				}
			}
		}
		if (minEdge == INT_MAX) {
			for (int i = 0; i < 3; ++i) answer[ttAnswer][i] = answer[0][i];
			++ttAnswer;
		} else {
			answer[ttAnswer][0] = u;
			answer[ttAnswer][1] = v;
			answer[ttAnswer][2] = minEdge;
			++ttAnswer;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (j) cout.put(' ');
				cout << answer[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}

int main() {
	//freopen("in_a", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
