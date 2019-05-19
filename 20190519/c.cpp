#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5 + 5;

int n, k, c;
int d[N], x[N];
struct Monster {
	int d, x;
	int count;
	bool operator<(const Monster &other)const {
		return x > other.x;
	}
}monster[N];

int main()
{
	while (cin >> n >> k >> c) {
		LL sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &monster[i].d, &monster[i].x);
			monster[i].count = 0;
			if (monster[i].d > k) {
				monster[i].count = ((monster[i].d + k - 1) / k) - 1;
				sum += 1LL * monster[i].count * monster[i].x;
			}
		}

		sort(monster + 1, monster + n + 1);
		for (int i = 1; i <= n; i++) {
			int count = min(monster[i].count, c);
			c -= count;
			sum -= 1LL * count * monster[i].x;
		}
		cout << sum << endl;
	}
	return 0;
}

