#include <bits/stdc++.h>
using namespace std;

typedef vector<string> Matrix;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef vector<PII> VP;
typedef vector<VP> VVP;
Matrix matrix;
VI mask, minIdx;
VVI idx;
VVI hashCode;
//VVP hashCode;
int n, mod;

const int K1 = 59;
const int M1 = 6400013;
const int K2 = 31;
const int M2 = 1000000007;

bool input() {
	matrix.resize(1);
	cin >> matrix[0];
	if (cin.fail()) return 0;
	n = matrix[0].length();
	mod = n - 1;
	matrix.resize(n);
	for (int i = 1; i < n; ++i) {
		cin >> matrix[i];
	}
	idx.resize(n);
	mask.resize(n);
	minIdx.resize(n);
	hashCode.resize(n);
	for (int i = 0; i < n; ++i) {
		idx[i].resize(n);
		hashCode[i].resize(n);
	}
	return 1;
}

inline int getIdx(char ch) { return ch - 'a' + 1; }
int currentRow;
inline bool cmp(int a, int b) {
	if (hashCode[a][n - 1] == hashCode[b][n - 1]) return 0;
	int l = 0, r = n - 1, m, mk = n - 1;
	while (l <= r) {
		m = l + r >> 1;
		if (hashCode[a][m] == hashCode[b][m]) {
			l = m + 1;
		} else {
			mk = m;
			r = m - 1;
		}
	}
	return matrix[currentRow][a + mk & mod] < matrix[currentRow][b + mk & mod];
}

void mySort(int x) {
	currentRow = x;
	for (int i = 0; i < n; ++i) {
		//hashCode[i][0] = PII(getIdx(matrix[x][i]), getIdx(matrix[x][i]));
		hashCode[i][0] = getIdx(matrix[x][i]);
		for (int j = 1; j < n; ++j) {
			//hashCode[i][j] = PII(int(((long long) hashCode[i][j - 1].first * K1 + getIdx(matrix[x][i + j & mod])) % M1), int(((long long) hashCode[i][j - 1].second * K2 + getIdx(matrix[x][i + j & mod])) % M2));
			hashCode[i][j] = hashCode[i][j - 1] * K2 + getIdx(matrix[x][i + j & mod]);
		}
	}
	for (int i = 0; i < n; ++i) {
		mask[i] = i;
	}
	sort(mask.begin(), mask.end(), cmp);
	//cerr << x << ": "; for (int i = 0; i < n; ++i) { cerr << mask[i] << ' '; } cerr << endl;
	for (int i = 0, id = 0; i < n; ++i) {
		int b = mask[i];
		if (i) {
			int a = mask[i - 1];
			id += hashCode[a][n - 1] != hashCode[b][n - 1];
		}
		idx[x][b] = id;
		//cerr << idx[x][b] << ' ';
	}
	//cerr << endl;
}

int cmp(int a, int b, int c, int d) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[a + i & mod][b + j & mod] == matrix[c + i & mod][d + j & mod]) {
				continue;
			}
			return matrix[a + i & mod][b + j & mod] - matrix[c + i & mod][d + j & mod];
		}
	}
	return 0;
}

int run() {
	while (input()) {
		cerr << "Input ends" << endl;
		//cout << n << ' ' << mod << endl;
		for (int i = 0; i < n; ++i) {
			mySort(i);
		}
		int mark;
		for (int i = 0; i < n; ++i) {
			mark = 0;
			for (int j = 0; j < n; ++j) {
				for (int d = 0; d < n; ++d) {
					if (idx[i + d & mod][j] == idx[i + d & mod][mark]) continue;
					if (idx[i + d & mod][j] < idx[i + d & mod][mark]) {
						mark = j;
					}
					break;
				}
			}
			minIdx[i] = mark;
		}
		int answer = 0;
		for (int i = 0; i < n; ++i) {
			if (cmp(i, minIdx[i], answer, minIdx[answer]) < 0) {
				answer = i;
			}
		}
		int x = answer, y = minIdx[answer];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout.put(matrix[x + i & mod][y + j & mod]);
			}
			cout << endl;
		}
	}
	return 0;
}

int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
