#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second
set<PII> ans;
const int N = 222;
int n, f[N];

void work() {
	memset(f, 0, sizeof(f));
	ans.clear();
	int half = n >> 1;
	if ((n & 3) == 1) {
		for (int i = 1; i < n; i++) {
			f[i] = half;
			if ((i & 1) == 0) half--;
		}
	} else {
		for (int i = 0; i < n; i++) {
			f[i] = half;
			if (i & 1) half--;
		}
	}
	//for (int i = 0; i < n; i++) cout << i << ' ' << f[i] << endl;
	for (int i = 0; i < n; i++) {
		int j = 1;
		while (f[i]--) {
			while (f[i + j] == 0) j++;
			ans.insert(PII(i, i + j));
			f[i + j]--, j++;
		}
	}
}

void print() {
	cout << ans.size() << endl;
	for (set<PII>::iterator si = ans.begin(); si != ans.end(); si++) {
		cout << si->x + 1 << ' ' << si->y + 1<< endl;
	}
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n) {
		work();
		print();
	}
	return 0;
}


