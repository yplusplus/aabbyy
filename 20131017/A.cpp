#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> Seg;
#define x first
#define y second
Seg L, R;

bool contain(const Seg &a, const Seg &b) { return a.x <= b.x && b.y <= a.y;}
void update(Seg &a, int p) { a = Seg(min(a.x, p), max(a.y, p));}

const int N = 111111;
const int INF = 0x77777777;
int a[N], b[N];

bool check(int n) {
	L = R = Seg(INF, -INF);
	int l = 0, r = 0;
	while (l < n && r < n) {
		if (contain(L, R)) {
			update(R, b[r++]);
			continue;
		}
		if (contain(R, L)) {
			update(L, a[l++]);
			continue;
		}
		return 0;
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> a[i], b[i] = a[i];
		reverse(b, b + n);
		if (check(n)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
