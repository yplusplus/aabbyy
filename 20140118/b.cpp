#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 111;
int cnt[10];
int number[N];
int bits[1111];
int a[N];
int n;
vector<int> digit[N];

bool check(int mask, int x) {
	for (int i = 0; i < digit[x].size(); i++) {
		int v = digit[x][i];
		if ((mask & v) == v) return true;
	}
	return false;
}

int main() {
	memset(number, -1, sizeof(number));
	for (int i = 1; i <= 100; i++) {
		int x = i;
		memset(cnt, 0, sizeof(cnt));
		while (x) {
			cnt[x % 10]++;
			x /= 10;
		}
		bool found = false;
		for (int j = 0; j < 10; j++) 
			if (cnt[j] > 1) found = true;
		if (found) continue;
		number[i] = 0;
		for (int j = 0; j < 10; j++) {
			if (cnt[j]) number[i] |= 1 << j;
		}
	}
	for (int i = 1; i <= 100; i++) {
		if (number[i] != -1) digit[i].push_back(number[i]);
		for (int j = 1; j < i; j++) {
			if (number[j] == -1 || number[i - j] == -1) continue;
			if (number[j] & number[i - j]) continue;
			digit[i].push_back(number[j] | number[i - j]);
		}
	}
	bits[0] = 0;
	for (int i = 1; i < 1 << 10; i++) bits[i] = bits[i >> 1] + (i & 1);
	int Case = 1;
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		int ans = -1;
		for (int mask = 0; mask < 1 << 10; mask++) {
			bool found = false;
			for (int i = 0; i < n; i++) {
				if (!check(mask, a[i])) {
					found = true;
					break;
				}
			}
			if (found) continue;
			if (ans == -1) ans = mask;
			else if (bits[mask] < bits[ans]) ans = mask;
			else if (bits[mask] == bits[ans] && mask < ans) ans = mask;
		}
		printf("Case %d: ", Case++);
		for (int i = 9; i >= 0; i--) {
			if (ans >> i & 1) putchar(i + '0');
		}
		puts("");
	}
	return 0;
}
