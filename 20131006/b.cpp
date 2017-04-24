#include cstdio
#include cstring
#include iostream
#include algorithm
#include set

using namespace std;

typedef pairint, int PII;
const int N = 1111111;

int ci[N];
int main() {
	int _, n, m;
	scanf(%d, &_);
	while (_--) {
		scanf(%d%d, &n, &m);
		for (int i = 1; i = n; i++) ci[i] = n - i;
		int a, b;
		setPII vis;
		while (m--) {
			scanf(%d%d, &a, &b);
			if (a  b) swap(a, b);
			if (vis.find(PII(a, b)) == vis.end()) {
				ci[a]--, ci[b]++;
				vis.insert(PII(a, b));
			}
		}
		bool find = 0;
		int mk;
		for (int i = n; i = 1; i--) {
			if (ci[i] == 0) {
				find = 1;
				mk = i;
				break;
			}
		}
		if (find) printf(2 %dn, mk);
		else puts(1);
	}
	return 0;
}
