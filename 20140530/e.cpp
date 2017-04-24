#include <vector>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;
typedef vector<Point> VP;
typedef vector<VP> Set;
#define x first
#define y second
const int N = 30;
const int K = 5;
const int D = 8;
const int M = K * 3;
VP figure[N];
inline int getid(char c) { return c - 'A'; }

void preRun1() {
	for (int i = 0; i < N; ++i) figure[i].clear();
	int id;
	id = getid('F');
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(0, 2));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 1));
	id = getid('I');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(2, 0));
	figure[id].push_back(Point(3, 0));
	figure[id].push_back(Point(4, 0));
	id = getid('L');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(2, 0));
	figure[id].push_back(Point(3, 0));
	figure[id].push_back(Point(3, 1));
	id = getid('N');
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 0));
	figure[id].push_back(Point(2, 1));
	figure[id].push_back(Point(3, 0));
	id = getid('P');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 0));
	id = getid('T');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(0, 2));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 1));
	id = getid('U');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(0, 2));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(1, 2));
	id = getid('V');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(2, 0));
	figure[id].push_back(Point(2, 1));
	figure[id].push_back(Point(2, 2));
	id = getid('W');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 1));
	figure[id].push_back(Point(2, 2));
	id = getid('X');
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(1, 2));
	figure[id].push_back(Point(2, 1));
	id = getid('Y');
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(1, 0));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 1));
	figure[id].push_back(Point(3, 1));
	id = getid('Z');
	figure[id].push_back(Point(0, 0));
	figure[id].push_back(Point(0, 1));
	figure[id].push_back(Point(1, 1));
	figure[id].push_back(Point(2, 1));
	figure[id].push_back(Point(2, 2));
}

bool matrix[N][D][K][K];

void print(int a, int b) {
	for (int i = 0; i < K; ++i) {
		for (int j = 0; j < K; ++j) {
			cout << matrix[a][b][i][j];
		}
		cout << endl;
	}
}

void preRun2() {
	for (int i = 0; i < N; ++i) {
		if (figure[i].size()) {
			assert(figure[i].size() == 5);
			VP &f = figure[i];
			for (int j = 0; j < K; ++j) {
				matrix[i][0][f[j].x][f[j].y] = 1;
				matrix[i][1][K - 1 - f[j].y][f[j].x] = 1;
				matrix[i][2][f[j].y][K - 1 - f[j].x] = 1;
				matrix[i][3][K - 1 - f[j].x][K - 1 - f[j].y] = 1;
				matrix[i][4][K - 1 - f[j].x][f[j].y] = 1;
				matrix[i][5][f[j].y][f[j].x] = 1;
				matrix[i][6][K - 1 - f[j].y][K - 1 - f[j].x] = 1;
				matrix[i][7][f[j].x][K - 1 - f[j].y] = 1;
			}
		}
		//if (i == 24) { for (int j = 0; j < D; ++j) { print(i, j); } }
	}
}

Set possibleSet[N][N];
bool current[M][M];

void print() {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			cout << current[i][j];
		}
		cout << endl;
	}
}

void getSet(const int ia, const int ib, Set &s) {
	VP temp;
	for (int i = 0; i < D; ++i) { 
		for (int j = 0; j < D; ++j) {
			for (int x = 0; x <= (M - K); ++x) {
				for (int y = 0; y <= (M - K); ++y) {
					memset(current, 0, sizeof current);
					bool ok = 1;
					for (int p = 0; p < K; ++p) {
						for (int q = 0; q < K; ++q) {
							current[p + K][q + K] = matrix[ia][i][p][q];
						}
					}
					for (int p = 0; p < K && ok; ++p) {
						for (int q = 0; q < K && ok; ++q) {
							if (matrix[ib][j][p][q] && current[p + x][q + y]) {
								ok = 0;
							} else {
								current[p + x][q + y] |= matrix[ib][j][p][q];
							}
						}
					}
					if (ok) {
						//if (ia == getid('V') && ib == getid('Z')) { print(); getchar(); }
						temp.clear();
						for (int i = 0; i < M; ++i) {
							for (int j = 0; j < M; ++j) {
								if (current[i][j]) {
									temp.push_back(Point(i, j));
								}
							}
						}
						sort(temp.begin(), temp.end());
						for (int i = temp.size() - 1; i >= 0; --i) {
							temp[i].x -= temp[0].x;
							temp[i].y -= temp[0].y;
						}
						s.push_back(temp);
					}
				}
			}
		}
	}
	sort(s.begin(), s.end());
	s.resize(unique(s.begin(), s.end()) - s.begin());
}

void preRun3() {
	for (int i = 0; i < N; ++i) {
		if (figure[i].size() == 0) continue;
		for (int j = i; j < N; ++j) {
			if (figure[j].size() == 0) continue;
			getSet(i, j, possibleSet[i][j]);
		}
	}
}

bool check(int a, int b, int c, int d) {
	int i = 0, j = 0;
	while (i < possibleSet[a][b].size() && j < possibleSet[c][d].size()) {
		if (possibleSet[a][b][i] == possibleSet[c][d][j]) {
			//memset(current, 0, sizeof current); for (int k = 0; k < 10; ++k) { current[possibleSet[a][b][i][k].x + K][possibleSet[a][b][i][k].y + K] = 1; } print();
			return 1;
		}
		if (possibleSet[a][b][i] > possibleSet[c][d][j]) ++j;
		else ++i;
	}
	return 0;
}

bool check(char *const a, char *const b) {
	sort(a, a + 2);
	sort(b, b + 2);
	return check(getid(a[0]), getid(a[1]), getid(b[0]), getid(b[1]));
}

int run() {
	preRun1();
	preRun2();
	preRun3();
	char f1[3], f2[3];
	while (~scanf("%s%s", f1, f2)) {
		puts(check(f1, f2) ? "YES" : "NO");
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
