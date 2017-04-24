#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int table[2][N];
int size[2];
int n;

void insert(int x, int id) {
	int pos = x % size[id];
	if (table[id][pos] != -1) {
		int y = table[id][pos];
		table[id][pos] = x;
		insert(y, id ^ 1);
	} else {
		table[id][pos] = x;
	}
}

int main() {
	int Case = 1;
	while (~scanf("%d%d%d", &size[0], &size[1], &n)) {
		if (!size[0] && !size[1] && !n) break;
		memset(table, -1, sizeof(table));
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			insert(x, 0);
		}
		vector<pair<int, int> > bag[2];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < size[i]; j++) {
				if (table[i][j] != -1) {
					bag[i].push_back(make_pair(j, table[i][j]));
				}
			}
		}
		printf("Case %d:\n", Case++);
		for (int i = 0; i < 2; i++) {
			if (bag[i].empty()) continue;
			printf("Table %d\n", i + 1);
			for (int j = 0; j < bag[i].size(); j++) {
				printf("%d:%d\n", bag[i][j].first, bag[i][j].second);
			}
		}
	}
	return 0;
}
