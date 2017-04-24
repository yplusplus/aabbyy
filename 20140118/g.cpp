#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second
typedef vector<PII> VPII;
typedef long long LL;
template<class T> inline T sqr(T x) { return x * x; }

const int N = 1111;
const int M = N * N;
VPII rec[N];
int issqr[M];

void PRE() {
	for (int i = 1; i < N; i++) issqr[sqr(i)] = i;
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
		int s = sqr(i) + sqr(j);
		if (s < M && issqr[s]) rec[issqr[s]].push_back(PII(i, j));
	}
}

LL work(int a, int b) {
	VPII::iterator vi;
	LL sum = 0;
	for (int i = 1, ha = a >> 1; i <= ha; i++) {
		for (int j = 1, hb = b >> 1; j <= hb; j++) {
			int s = i + j;
			for (vi = rec[s].begin(); vi != rec[s].end(); vi++) {
				int x, y;
				if (i - vi->x > j) x = i << 1;
				else if (j - vi->x > i) x = j << 1;
				else x = i + vi->x + j;
				if (i - vi->y > j) y = i << 1;
				else if (j - vi->y > i) y = j << 1;
				else y = i + vi->y + j;
				if (x > a || y > b) continue;
				if (vi->x && vi->y) sum += (a - x + 1) * (b - y + 1) << 1;
				else sum += (a - x + 1) * (b - y + 1);
			}
		}
	}
	return sum;
}

int main() {
	PRE();
	ios::sync_with_stdio(0);
	int _, h, w;
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> h >> w;
		cout << "Case " << cas << ": " << work(h, w) << endl;
	}
	return 0;
}
