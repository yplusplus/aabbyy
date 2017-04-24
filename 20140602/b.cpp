#include <bits/stdc++.h>
using namespace std;

const int N = 10;
string nextStatus[N];
bool input() {
	for (int i = 0; i < N; ++i) {
		cin >> nextStatus[i];
		if (cin.fail()) return 0;
	}
	return 1;
}

const int M = 1 << 21 | 1;
const int T = 100000000;
bool tree[M];

bool simulate() {
	int ptr = M >> 1, maxPtr = INT_MIN, minPtr = INT_MAX;
	char current = 'A';
	memset(tree, 0, sizeof tree);
	for (int i = 0; i < T; ++i) {
		if (0 > ptr || ptr >= M) return 0;
		maxPtr = max(maxPtr, ptr);
		minPtr = min(minPtr, ptr);
		if (current == 'H') {
			cerr << i << ' ' << (M * 10 * 2) << endl;
			cerr << maxPtr << ' ' << minPtr << ' ' << (maxPtr - minPtr) << endl;
			return 1;
		}
		int id = current - 'A' << 1 | tree[ptr];
		current = nextStatus[id][2];
		tree[ptr] = nextStatus[id][0] & 1;
		if (nextStatus[id][1] == 'L') {
			--ptr;
		} else {
			++ptr;
		}
	}
	return 0;
}

int run() {
	while (input()) {
		if (simulate()) cout << "happy beaver" << endl;
		else cout << "unhappy beaver" << endl;
	}
	return 0;
}

int main() {
	freopen("beavers.in", "r", stdin);
	freopen("beavers.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
