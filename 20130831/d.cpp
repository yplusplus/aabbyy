#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef long long LL;
typedef pair<LL, string> PIS;

const int N = 111;
const char *p[4] = { "*UP*", "*NEW*", "*DOWN*", "*STAY*"};
PIS rec[N], last[N];

int main() {
	//freopen("in", "r", stdin);
	int n, top = 0, week = 1;
	string name;
	LL val;
	for (int i = 0; i < N; i++) rec[i].first = 0, rec[i].second = "";
	while (cin >> n && n) {
		cout << "----------------WEEK " << week++ << "----------------" << endl;
		for (int i = 0; i < top; i++) last[i] = rec[i], rec[i].first = 0;
		int lt = top;
		while (n-- && cin >> name >> val) {
			int i = 0;
			while (i < top && name != rec[i].second) i++;
			rec[i].second = name, rec[i].first = -val;
			if (i == top) top++;
		}
		sort(rec, rec + top);
		for (int i = 0; i < 5; i++) {
			int j = 0;
			while (j < lt && last[j].second != rec[i].second) j++;
			if (last[j].second == rec[i].second) {
				if (i < j) printf("%d.%-8s", i + 1, p[0]);
				else if (i > j) printf("%d.%-8s", i + 1, p[2]);
				else printf("%d.%-8s", i + 1, p[3]);
			} else printf("%d.%-8s", i + 1, p[1]);
			cout << rec[i].second << endl; //' ' << rec[i].first << endl;
		}
	}
	return 0;
}
