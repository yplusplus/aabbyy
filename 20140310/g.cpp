#include <bits/stdc++.h>
using namespace std;

const int N = 230;
const int LCM = 60;
char act_id[N][N];
int size;
int n, m, t, act;
char op[N][LCM + 10];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool check(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; }

int get_dir(char ch) {
	if (ch == 'E') return 3;
	if (ch == 'W') return 2;
	if (ch == 'N') return 1;
	if (ch == 'S') return 0;
	return -1;
}

struct Mat {
	long long val[N][N];
	Mat() { memset(val, 0, sizeof(val)); }
	void clear() { for (int i = 0; i < size; i++) { for (int j = 0; j < size; j++) { val[i][j] = 0; } } }
	void unit() { clear(); for (int i = 0; i < size; i++) val[i][i] = 1; }
};

Mat operator *(const Mat &a, const Mat &b) {
	Mat res;
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			if (a.val[i][k] == 0) continue;
			for (int j = 0; j < size; j++) {
				if (b.val[k][j] == 0) continue;
				res.val[i][j] += a.val[i][k] * b.val[k][j];
			}
		}
	}
	return res;
}

Mat operator ^(Mat a, int n) {
	Mat res;
	res.unit();
	while (n) {
		if (n & 1) res = res * a;
		a = a * a;
		n >>= 1;
	}
	return res;
}

int get_id(int x, int y) { return x * m + y; }

void output(const Mat &a) {
	cout << "*********" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%lld ", a.val[i][j]);
		}
		puts("");
	}
}

Mat a[LCM + 10];
int main() {
	while (~scanf("%d%d%d%d", &n, &m, &t, &act)) {
		size = n * m + 1;
		for (int i = 0; i < n; i++) { scanf("%s", act_id[i]); }
		for (int i = 0; i < act; i++) {
			scanf("%s", op[i]);
			int len = strlen(op[i]);
			for (int j = len; j < LCM; j++) {
				op[i][j] = op[i][j - len];
			}
			//op[i][LCM] = 0; puts(op[i]);
		}
		a[0].unit();
		for (int i = 1; i <= LCM; i++) {
			a[i].clear();
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m; k++) {
					int id = act_id[j][k] - '0';
					char cmd = op[id][i - 1];
					int x = get_id(j, k);
					a[i].val[x][x] = 0;
					if (cmd == 'D') {
						a[i].val[x][x] = 0;
					} else if (isdigit(cmd)) {
						a[i].val[x][x] = 1;
						a[i].val[size - 1][x] = cmd - '0';
					} else {
						int dir = get_dir(cmd);
						assert(dir != -1);
						int xpos = j + dx[dir], ypos = k + dy[dir];
						if (check(xpos, ypos)) {
						//cout << j << " " << k << " " << xpos << " " << ypos << endl;
							a[i].val[x][get_id(xpos, ypos)] = 1;
						}
					}
				}
			}
			a[i].val[size - 1][size - 1] = 1;
			//if (i <= 10) {
			//cout << i << endl;
			//ans = ans * a[i];
			//output(ans);
			//}
			//if (i <= 2) { cout << i << endl; output(a[i]); }
			a[i] = a[i - 1] * a[i];
			//if (i <= 2) { output(a[i]); }
		}
		//output(a[2] ^ 30);
		//output(a[LCM]);
		Mat ans;
		ans.val[0][size - 1] = 1;
		long long max_marbles = 0;
		ans = ans * (a[LCM] ^ (t / LCM)) * a[t % LCM];
		//output(ans);
		for (int i = 0; i < size - 1; i++) {
			max_marbles = max(max_marbles, ans.val[0][i]);
		}
		cout << max_marbles << endl;
	}
	return 0;
}
