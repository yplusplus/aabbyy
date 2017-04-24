#include <bits/stdc++.h>
using namespace std;

int n, m;
string get_ans(int acnt, int bcnt) {
	if (acnt > bcnt) return "Ana";
	if (acnt < bcnt) return "Bob";
	return "Draw";
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		int acnt = ((n / 2) * (m / 2) + 1) / 2 * 4;
		int bcnt = n * m - acnt;
		printf("Case #%d: %s\n", Case++, get_ans(acnt, bcnt).c_str());
	}
	return 0;
}
