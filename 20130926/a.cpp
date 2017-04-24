#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 200020;
const int M = 200000;
int a[N];
void read(int &t) {
	t = 0;
	char ch = getchar();
	while (!isdigit(ch)) {
		ch = getchar();
	}
	while (isdigit(ch)) {
		t = t * 10 + ch - '0';
		ch = getchar();
	}
}

int process(int a[], int n) {
	sort(a, a + n);
	int alloc = 0;
	for (int i = 0; i < n; ) {
		int j = i;
		int t = a[i];
		int cnt = 0;
		while (j < n && a[j] == t) {
			cnt++;
			j++;
		}
		if (cnt % 3 == 1) a[alloc++] = t;
		else if (cnt % 3 == 2) a[alloc++] = -t;
		i = j;
	}
	return alloc;
}

int bs(int l, int r, int x) {
	int res = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (a[mid] == x) return mid;
		else if (a[mid] > x) r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int ans[2], tot = 0;
		/*
		if (n <= M) {
			for (int i = 0; i < n; i++) read(a[i]);
			sort(a, a + n);
			for (int i = 0; i < n; ) {
				int t = a[i];
				int cnt = 0;
				int j = i;
				while (j < n && a[j] == t) {
					cnt++;
					j++;
				}
				if (cnt % 3 == 1) {
					ans[tot++] = t;
				} else if (cnt % 3) {
					ans[tot++] = t;
				}
				if (tot == 2) break;
				i = j;
			}
		} else {
		*/
			int m = n / 3 * 2;
			for (int i = 0; i < m; i++) read(a[i]);
			int b = process(a, m);
			//cout << b << endl;
			for (int i = 0; i < (n - m); i++) read(a[i + b]);
			int c = process(a + b, n - m);
			//cout << c << endl;
			/*

			for (int i = 0; i < b; i++) {
				cout << a[i] << endl;
			}
			cout << "*********" << endl;
			for (int i = 0; i < c; i++) {
				cout << a[b + i] << endl;
			}
			cout << "*********" << endl;
			*/
			sort(a, a + b);
			for (int i = 0; i < c; i++) {
				//cout << a[i + b] << endl;
				int t = a[i + b];
				int res = bs(0, b - 1, t);
				if (res == -1) res = bs(0, b - 1, -t);
				if (res == -1) {
					if (t > 0) ans[tot++] = t;
					else {
						ans[tot++] = -t;
						ans[tot++] = -t;
					}
				} else {
					if (t > 0) {
						if (a[res] == t) {
							ans[tot++] = t;
							ans[tot++] = t;
						}
					} else {
						if (a[res] == t) {
							ans[tot++] = -t;
						}
					}
				}
				if (res != -1) a[res] = 0;
				if (tot == 2) break;
			}
			//}
			if (tot < 2) {
				for (int i = 0; i < b; i++) {
					if (a[i] != 0) {
						if (a[i] > 0) ans[tot++] = a[i];
						else {
							ans[tot++] = -a[i];
							ans[tot++] = -a[i];
						}
					}
				}
			}
			if (ans[0] > ans[1]) swap(ans[0], ans[1]);
			printf("%d %d\n", ans[0], ans[1]);
	}
	return 0;
}

