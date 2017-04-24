#include <map>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 222;
char buf[N];
bool ok[3];
map<char, int> id;
char word[3][N], ch[3];

bool check() {
	for (int i = 0; i < 3; i++) if (!ok[i]) return 0;
	return 1;
}

void get(char *s, char *&p, char end) {
	p++;
	while (*p && *p != end) {
		*s = *p;
		if (isupper(*s)) *s += 32;
		s++, p++;
	}
	*s = 0;
}

void print(int op) {
	if (op) word[0][0] -= 32;
	for (int i = 0; i < 3; i++) {
		if (i) cout << ' ';
		cout << word[i];
	}
}

int main() {
	//freopen("in", "r", stdin);
	id['{'] = 0, id['('] = 1, id['['] = 2;
	id['}'] = 0, id[')'] = 1, id[']'] = 2;
	ch[0] = '}', ch[1] = ')', ch[2] = ']';
	while (gets(buf)) {
		memset(ok, 0, sizeof(ok));
		//cout << buf << endl;
		char *p = buf;
		bool pnt = 1;
		while (*p) {
			if (*p == ',') {
				while (id.find(*p) == id.end()) { cout << *p; p++; }
				continue;
			}
			if (id.find(*p) != id.end()) {
				get(word[id[*p]], p, ch[id[*p]]);
				//cout << "~~~~~~~ " << word[id[*p]] << endl;
				ok[id[*p]] = 1;
			}
			if (check()) {
				print(pnt);
				pnt = 0;
				memset(ok, 0, sizeof(ok));
			}
			p++;
		}
		cout << endl;
	}
	return 0;
}


