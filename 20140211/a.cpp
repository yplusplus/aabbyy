#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 16;
char str[N], nstr[N << 1];
int p[N << 1];

typedef pair<int, int> PII;
#define x first
#define y second
PII pos[N << 1];
int tt, len;

void manacher(char *s) {
	int id = 0, lf = 0, mx = 1;
	len = strlen(s);
	p[0] = 1;
	tt = 0;
	//cout << s << endl;
	for (int i = 1; i < len; i++) {
		if (lf > 1) p[i] = min(p[(id << 1) - i], lf - i);
		else p[i] = 1;
		while (s[i + p[i]] && s[i + p[i]] == s[i - p[i]]) p[i]++;
		if (lf < i + p[i] - 1) lf = i + p[i] - 1, id = i;
	}
	for (int i = 0; i < len; i++) {
		if (s[i] == '~') {
			int len = p[i] >> 1;
			pos[tt++] = PII((i >> 1) - len, (i >> 1) + len);
		} else {
			int len = p[i] - 1 >> 1;
			pos[tt++] = PII((i >> 1) - len, (i >> 1) + len + 1);
		}
	}
}

int cal(int n) {
	sort(pos, pos + tt);
	//for (int i = 0; i < tt; i++) cout << pos[i].x << ' ' << pos[i].y << endl;
	int end = 0, mx = 0, cnt = 0, i = 0;
	len = strlen(str);
	while (end < len) {
		while (i < tt && pos[i].x <= end) mx = max(pos[i].y, mx), i++;
		cnt++;
		end = mx;
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> str) {
		char *p = str, *q = nstr;
		while (1) {
			*(q++) = '~';
			*(q++) = *p;
			if (!*p) break;
			p++;
		}
		manacher(nstr);
		cout << cal(tt) - 1 << endl;
	}
	return 0;
}
