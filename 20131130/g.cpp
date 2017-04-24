#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 111;

int main() {
	//freopen("in", "r", stdin);
	int _, n;
	char op[2];
	LL a, b, c;
	scanf("%d", &_);
	for (int  cas = 1; cas <= _; cas++) {
		printf("Case #%d:\n", cas);
		priority_queue<LL> pq[111];
		scanf("%d", &n);
		while (n--) {
			scanf("%s", op);
			if (*op == 'P') {
				scanf("%lld%lld%lld", &a, &b, &c);
				pq[c].push(b - c * a);
			} else {
				scanf("%lld", &a);
				int id = -1;
				LL mx = 0, cur;
				for (int i = N - 1; i >= 0; i--) {
					if (pq[i].empty()) continue;
					cur = i * a + pq[i].top();
					if (cur > mx) id = i, mx = cur;
				}
				pq[id].pop();
				printf("%lld %d\n", mx, id);
			}
		}
	}
	return 0;
}

