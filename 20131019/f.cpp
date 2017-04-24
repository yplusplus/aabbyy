#include <bits/stdc++.h>
using namespace std;

map<string, int> id; 

const int N = 30;
long double mat[N][N];
long double eps = 1e-6;
bool base[N];
int row_id[N];

void gauss(int row, int col) {
	int r, c, i, j;
	for (r = c = 0; r < row && c < col; r++, c++) {
		if (base[c]) { r--; continue; }
		int idx = r;
		for (i = r; i < row; i++) {
			if (row_id[i] == c) {
				idx = i;
				break;
			}
		}
		i = idx;
		if (i != r) {
			for (j = 0; j < col; j++) {
				swap(mat[i][j], mat[r][j]);
			}
			swap(row_id[i], row_id[r]);
		}
		for (i = r + 1; i < row; i++) {
			long double tmp = mat[i][c] / mat[r][c];
			for (j = 0; j < col; j++) {
				mat[i][j] -= tmp * mat[r][j];
			}
		}
	}
	for (r = row - 1; r >= 0; r--) {
		if (base[row_id[r]]) continue;
		long double tmp = mat[r][row_id[r]];
		for (j = 0; j < col; j++) { mat[r][j] /= tmp; }
		for (i = 0; i < r; i++) {
			long double tmp = mat[i][row_id[r]] / mat[r][row_id[r]];
			for (j = 0; j < col; j++) {
				mat[i][j] -= tmp * mat[r][j];
			}
		}
	}
}

int n;
string name[N];
vector<pair<string, long double> > vec[N];

bool cmp(int a, int b) {
	return name[a] < name[b];
}

long double fix(long double x) {
	if (fabs(x) < eps) return 0.0;
	return x;
}

int main() {
	//freopen("in.txt", "r", stdin);
	string a, b;
	string trash, line;
	id.clear();
	n = 0;
	memset(mat, 0, sizeof(mat));
	memset(base, true, sizeof(base));
	while (cin >> a) {
		cin >> b;
		getline(cin, line);
		istringstream input(line);
		int d;
		if (id.count(a) == 0) { name[n] = string(a); id[a] = n++; }
		mat[id[a]][id[a]] = 100;
		base[id[a]] = false;
		while (input >> b >> d) {
			if (id.count(b) == 0) { name[n] = string(b); id[b] = n++; }
			mat[id[a]][id[b]] -= d;
		}
	}
	for (int i = 0; i < n; i++) row_id[i] = i;
	gauss(n, n);
	for (int i = 0; i < n; i++) vec[i].clear();
	for (int i = 0; i < n; i++) {
		if (base[row_id[i]]) continue;
		for (int j = 0; j < n; j++) {
			if (base[j]) vec[row_id[i]].push_back(make_pair(name[j], -mat[i][j]));
		}
		sort(vec[row_id[i]].begin(), vec[row_id[i]].end());
	}
	for (int i = 0; i < n; i++) row_id[i] = i;
	sort(row_id, row_id + n, cmp);
	for (int i = 0; i < n; i++) {
		if (base[row_id[i]]) continue;
		cout << name[row_id[i]] << " :";
		for (int j = 0; j < vec[row_id[i]].size(); j++) {
			printf(" %s %.10f", vec[row_id[i]][j].first.c_str(), (double) fix(vec[row_id[i]][j].second * 100));
		}
		puts("");
	}
	return 0;
}

