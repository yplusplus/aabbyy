#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second
typedef vector<PII> VPII;
const int N = 55;
int n, m;
VPII row[N];
char ans[N][N];
int mk[N][N], ul[N][N];

void fix(char *s) {
	int t = m * 3;
	while (t >= 0 && s[t] == ' ') s[t] = 0, t--;
}

void print_mk() {
	cout << "~~~~~~~~~ table ~~~~~~~~~~" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << mk[i][j] << ' ';
		cout << endl;
	}
	cout << "~~~~~~~~~~ end ~~~~~~~~~~~" << endl;
}

void print_ans() {
	int sz = n << 1 | 1;
	for (int i = 0; i < sz; i++) {
		fix(ans[i]);
		cout << ans[i] << endl;
	}
	cout << endl;
}

void find(int x, int &y) {
	for (int i = 0; i < m; i++) {
		if (mk[x][i] == 0) {
			y = i;
			return ;
		}
	}
}

void convert() {
	int c = 1, x, y;
	m = 0;
	for (int i = 0, sz = row[0].size(); i < sz; i++) m += row[0][i].y;
	//cout << "M " << m << endl;
	memset(mk, 0, sizeof(mk));
	memset(ul, 0, sizeof(ul));
	for (int i = 0; i < n; i++) {
		x = i;
		for (int j = 0, sz = row[i].size(); j < sz; j++) {
			find(x, y);
			ul[x][y] = 1;
			for (int dx = 0; dx < row[i][j].x; dx++) {
				for (int dy = 0; dy < row[i][j].y; dy++) {
					mk[x + dx][y + dy] = c;
				}
			}
			c++;
		}
	}
}

void build() {
	memset(ans, 0, sizeof(ans));
	int n2 = n << 1 | 1, m2 = m * 3 + 1;
	for (int i = 0; i < n2; i++) for (int j = 0; j < m2; j++) ans[i][j] = ' ';
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 || mk[i][j] != mk[i - 1][j]) ans[i << 1][j * 3 + 1] = ans[i << 1][j * 3 + 2] = '-';
			if (j == 0 || mk[i][j] != mk[i][j - 1]) ans[i << 1 | 1][j * 3] = '|';
			if (ul[i][j]) {
				ans[i << 1 | 1][j * 3 + 1] = '1' + i;
				ans[i << 1 | 1][j * 3 + 2] = '1' + j;
			}
		}
	}
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	while (cin >> n && n) {
		int k, x, y;
		for (int i = 0; i < N; i++) row[i].clear();
		for (int i = 0; i < n; i++) {
			cin >> k;
			for (int j = 0; j < k; j++) {
				cin >> x >> y;
				row[i].push_back(PII(x, y));
			}
		}
		convert();
		//print_mk();
		build();
		print_ans();
	}
	return 0;
}
