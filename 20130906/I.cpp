#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, PII> PIII;
#define x first
#define y second

const int N = 11111;
PIII rec[N];
bool cmp(PIII a, PIII b) {
	if (a.x == b.x) {
		int i = a.y.x - a.y.y;
		int j = b.y.x - b.y.y;
		i = (i > 0) - (i < 0);
		j = (j > 0) - (j < 0);
		return i > j;
	}
	return a.x > b.x;
}

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &rec[i].y.x, &rec[i].y.y);
			rec[i].x = (LL) rec[i].y.x + rec[i].y.y;
		}
		stable_sort(rec, rec + n, cmp);
		for (int i = 0; i < n; i++) {
			printf("%d+%d=", rec[i].y.x, rec[i].y.y);
			if (rec[i].y.x > rec[i].y.y) printf("[>%I64d]\n", rec[i].x);
			if (rec[i].y.x == rec[i].y.y) printf("[=%I64d]\n", rec[i].x);
			if (rec[i].y.x < rec[i].y.y) printf("[<%I64d]\n", rec[i].x);
		}
		puts("");
	}
	return 0;
}
