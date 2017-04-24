#include <iostream>
#include <cstring>
#include <string>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 11;
int g[N][N];
int a[N];
char str[222222][12];
bool check(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (g[a[i]][a[i + 1]] == 0) return false;
	}
	return g[a[n - 1]][a[0]] == 1;
}

int n;
int id[222222];

bool cmp(int a, int b) {
	return strcmp(str[a], str[b]) == -1;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &g[i][j]);
			}
		}
		int num = 0;
		for (int mask = 1; mask < (1 << n); mask++) {
			int tot = 0;
			int head = n;
			for (int i = 0; i < n; i++) {
				if (mask >> i & 1) a[tot++] = i, head = min(head, i);
			}
			if (tot < 2) continue;
			do {
				if (a[0] != head) continue;
				if (check(a, tot)) {
					for (int i = 0; i < tot; i++) {
						str[num][i] = a[i] + '0';
					}
					str[num][tot] = 0;
					num++;
				}
			} while (next_permutation(a, a + tot));
		}
		
		for (int i = 0; i < num; i++) id[i] = i;
		sort(id, id + num, cmp);
		for (int i = 0; i < num; i++) {
			puts(str[id[i]]);
		}
		puts("");
	}
	return 0;
}