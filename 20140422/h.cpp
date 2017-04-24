#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
char str[N];
int n;

bool check() {
	int bcnt = 0, wcnt = 0;
	for (int i = 1; i <= n; i++) {
		if (str[i] == 'B') bcnt++;
		else wcnt++;
	}
	if (!bcnt || !wcnt) return false;
	if (str[1] == 'W' || str[n] == 'B') return false;
	return true;
}

bool check_one_step() {
	int i;
	for (i = 1; i <= n; i++) {
		if (str[i] != 'B') break;
	}
	for (; i <= n; i++) {
		if (str[i] == 'B') return false;
	}
	return true;
}

void print(const vector<int> &pos) {
	printf("%d", (int) pos.size());
	for (int i = 0; i < pos.size(); i++) {
		printf(" %d", pos[i]);
	}
	puts("");
}
void solve() {
	if (!check()) {
		puts("IMPOSSIBLE");
		return;
	}
	if (check_one_step()) {
		puts("1");
		printf("%d", n);
		for (int i = 1; i <= n; i++) {
			printf(" %d", i);
		}
		puts("");
	} else {
		puts("2");
		vector<int> pos;
		pos.push_back(1);
		for (int i = 2; i < n; i++) {
			if (str[i] == 'W') pos.push_back(i);
		}
		print(pos);
		pos.clear();
		for (int i = 2; i < n; i++) {
			if (str[i] == 'B') pos.push_back(i);
		}
		pos.push_back(n);
		print(pos);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str + 1);
		n = strlen(str + 1);
		solve();
	}
}
