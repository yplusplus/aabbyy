#include <bits/stdc++.h>
using namespace std;

const int D = 4;
const int N = 52;
bool visit[N][N];

void floyd() {
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				visit[i][j] |= visit[i][k] & visit[k][j];
			}
		}
	}
}

bool check() {
	for (int i = 0; i < N; ++i) {
		if (visit[i][i]) return 1;
	}
	return 0;
}

int getID(const string &op) {
	if (op == "00") return -1;
	return (op[0] - 'A' << 1) | (op[1] == '+');
}

void connect(int a, int b) {
	b ^= 1;
	//cout << a << ' ' << b << endl;
	visit[a][b] = 1;
}

int run() {
	int n;
	while (cin >> n) {
		string buffer;
		memset(visit, 0, sizeof visit);
		for (int i = 0; i < n; ++i) {
			cin >> buffer;
			for (int j = 0; j < D; ++j) {
				int a = getID(buffer.substr(j << 1, 2));
				if (a == -1) continue;
				for (int k = 0; k < D; ++k) {
					if (j == k) continue;
					int b = getID(buffer.substr(k << 1, 2));
					if (b == -1) continue;
					connect(a, b);
				}
			}
		}
		floyd();
		//for (int i = 0; i < 10; ++i) { for (int j = 0; j < 10; ++j) cout << visit[i][j]; cout << endl; }
		cout << (check() ? "unbounded" : "bounded") << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
