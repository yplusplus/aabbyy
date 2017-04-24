#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

map<string, int> id;
const int N = 222;
const int L = 22;
const int INF = 0x777777;
const char *str1[8] = { " has a Killing Spree!", " is Dominating!", " has a Mega Kill!", " is Unstoppable!", " is Wicked Sick!", " has a Monster Kill!!!", " is Godlike!", " is Beyond Godlike! Somebody kill him!!" };
const char *str2[3] = { " just drew First Blood!", " just got a Double Kill!", " just got a Triple Kill!" }; 

char name[N][L];
int get_id(char *s) {
	if (id.find(s) == id.end()) {
		id[s] = id.size();
		strcpy(name[id[s]], s);
	}
	return id[s];
}

int convert(char *s) {
	int mm, ss;
	sscanf(s, "%d:%d", &mm, &ss);
	return mm * 60 + ss;
}

int last_kill[N], cnt1[N], cnt2[N];
char buf[N];

struct Event {
	int t, x, y;
	bool operator < (const Event &a) const { return t < a.t; }
} ev[N];

int main() {
	//freopen("in", "r", stdin);
	int _;
	scanf("%d", &_);
	while (_--) {
		int n = 0;
		while (scanf("%s", buf) && *buf != '#') {
			ev[n].t = convert(buf);
			scanf("%s", buf);
			ev[n].x = get_id(buf);
			scanf("%s", buf);
			scanf("%s", buf);
			ev[n].y = get_id(buf);
			n++;
		}
		sort(ev, ev + n);
		for (int i = 0; i < N; i++) last_kill[i] = -INF, cnt1[i] = 0, cnt2[i] = 0;
		bool fb = 0;
		for (int i = 0; i < n; i++) {
			int x = ev[i].x, y = ev[i].y, t = ev[i].t;
			cnt1[y] = 0;
			cnt1[x]++;
			if (!fb) {
				printf("%s%s\n", name[x], str2[0]);
				fb = 1;
			}
			if (cnt1[x] >= 3) printf("%s%s\n", name[x], str1[min(cnt1[x] - 3, 7)]);
			if (t - last_kill[x] <= 14) {
				cnt2[x]++;
				if (cnt2[x] >= 2) printf("%s%s\n", name[x], str2[min(cnt2[x] - 1, 2)]);
			} else cnt2[x] = 1;
			last_kill[x] = t;
		}
		puts("");
	}
	return 0;
}


