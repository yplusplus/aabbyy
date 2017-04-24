#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <map>

using namespace std;

typedef long long LL;
const LL INF = 0x333333333333ll;

LL GPU;
void print(LL x) {
	if (x * 10 > GPU) cout << "Slideshow" << endl;
	else if (x * 60 <= GPU) cout << "Perfect" << endl;
	else cout << "So-so" << endl;
}

map<string, int> ops;
set<string> on, off;
set<string>::iterator si;

LL cal(LL x) {
	if (on.size() > 60) return INF;
	for (si = on.begin(); si != on.end(); si++) {
		x *= ops[*si];
		if (x >= INF) return INF;
	}
	return x;
}

int main() {
	LL cur;
	int n, k;
	ios::sync_with_stdio(0);
	while (cin >> n) {
		string buf;
		ops.clear();
		on.clear();
		off.clear();
		for (int i = 0; i < n; i++) {
			cin >> buf >> k;
			ops[buf] = k;
			on.insert(buf);
		}
		int x, y;
		cin >> x >> y >> GPU;
		cur = (LL) x * y;
		cin >> n;
		print(cal(cur));
		for (int i = 0; i < n; i++) {
			cin >> buf;
			if (buf == "Off") {
				cin >> buf;
				on.erase(buf);
				off.insert(buf);
			} else if (buf == "On") {
				cin >> buf;
				off.erase(buf);
				on.insert(buf);
			} else {
				cin >> x >> y;
				cur = (LL) x * y;
			}
			print(cal(cur));
		}
	}
	return 0;
}

