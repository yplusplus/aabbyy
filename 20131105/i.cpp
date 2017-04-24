#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 111111;
pair<int, int> prob[N];
int n, m, p;

int main() {
	while (~scanf("%d%d%d", &n, &m, &p)) {
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &prob[i].first, &prob[i].second);
		}
		sort(prob, prob + n);
		priority_queue<int> pq;
		int pos = 0;
		for (int i = 0; i < m; i++) {
			while (pos < n && prob[pos].first <= p) {
				pq.push(prob[pos].second);
				pos++;
			}
			if (pq.empty()) break;
			p += pq.top();
			pq.pop();
		}
		printf("%d\n", p);
	}
	return 0;
}
