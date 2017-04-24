#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef map<string, int> MSI;
#define x first
#define y second
const int N = 222;
string buf;
MSI ans;
char *p, str[N];

LL getdg() {
	LL x = 0;
	while (isdigit(*p)) {
		x = x * 10 + *p - '0';
		p++;
	}
	return x;
}

string gete() {
	string s;
	s += *p; p++;
	while (islower(*p)) {
		s += *p;
		p++;
	}
	return s;
}

void cut(string &s) {
	int i = 0;
	while (isdigit(s[i])) i++;
	s.erase(0, i);
}

void merge(MSI &a, MSI &b) { for (MSI::iterator mi = b.begin(); mi != b.end(); mi++) a[mi->x] += mi->y; }
void multi(MSI &a, LL p) { for (MSI::iterator mi = a.begin(); mi != a.end(); mi++) mi->y *= p; }

void print(LL k) {
	MSI::iterator mi = ans.begin();
	if (mi->y > 1) cout << mi->y << mi->x;
	else cout << mi->x;
	for (mi++; mi != ans.end(); mi++) {
		if (mi->y > 1) cout << '+' << mi->y << mi->x;
		else cout << '+' << mi->x;
	}
	cout << endl;
}

MSI dfs() {
	MSI cnt, tmp;
	string elem;
	LL c;
	cnt.clear();
	p++;
	while (1) {
		if (*p == ')') break;
		else if (*p == '(') {
			tmp = dfs();
			merge(cnt, tmp);
		} else if (isalpha(*p)) {
			elem = gete();
			if (isdigit(*p)) c = getdg();
			else c = 1;
			cnt[elem] += c;
		}
	}
	p++;
	if (isdigit(*p)) multi(cnt, getdg());
	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	while (cin >> buf) {
		LL k = 1;
		if (isdigit(buf[0])) {
			k = getdg();
			cut(buf);
		}
		buf = '(' + buf + ')';
		strcpy(str, buf.c_str());
		p = str;
		//cout << k << ' ' << buf << endl;
		ans = dfs();
		print(k);
	}
	return 0;
}
