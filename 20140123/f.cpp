#include <bits/stdc++.h>
using namespace std;

int cnt(int t) {
	int c = 0;
	while (t > 0) {
		c += (t % 10 == 9);
		t /= 10;
	}
	return c;
}

const int N = 10000;
typedef pair<int, int> PII;
#define x first
#define y second
PII t9[N];
int tt, c9[N];

bool cmp(const PII &a, const PII &b) { return a.x > b.x || a.x == b.x && a.y < b.y; }

PII p;
int tp;
bool update(const PII &a, const PII &b) {
	int ta = a.x * 60 + a.y;
	int tb = b.x * 60 + b.y;
	if (10 * abs(tp - tb) >= tp) return 0;
	int ia = a.x * 100 + a.y;
	int ib = b.x * 100 + b.y;
	if (c9[ia] < c9[ib]) return 1;
	else if (c9[ia] > c9[ib]) return 0;
	if (abs(ta - tp) > abs(tb - tp)) return 1;
	if (ia > ib) return 1;
	return 0;
}

void PRE() {
	tt = 0;
	for (int i = 0; i < N; i++) {
		c9[i] = cnt(i);
		if (c9[i]) t9[tt++] = PII(c9[i], i);
	}
	sort(t9, t9 + tt, cmp);
	//for (int i = 0; i < 10; i++) cout << t9[i].x << ' ' << t9[i].y << endl;
}

void work(int &a, int &b) {
	p = PII(a, b); tp = p.x * 60 + p.y;
	PII ans = p, tmp;
	//cout << update(PII(0, 99), PII(0, 90)) << endl;
	for (int i = 0; i < tt; i++) {
		if (t9[i].x < c9[ans.x * 100 + ans.y]) break;
		tmp = PII(t9[i].y / 100, t9[i].y % 100);
		if (update(ans, tmp)) ans = tmp;
	}
	a = ans.x; b = ans.y;
}

int main() {
	int mm, ss;
	PRE();
	while (~scanf("%d:%d", &mm, &ss) && (mm + ss)) {
		work(mm, ss);
		printf("%02d:%02d\n", mm, ss);
	}
	return 0;
}
