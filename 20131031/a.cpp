#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111111;
char str[N], buf[N];
int next[N];

int sub_len;
void get_next(char *s) {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < sub_len) {
		while (~j && s[i] != s[j]) j = next[j];
		i++, j++;
		next[i] = j;
	}
}

int str_len;
int kmp(char *s, char *t) {
	int i = 0, j = 0;
	while (s[i] && j < sub_len) {
		while (~j && s[i] != t[j]) j = next[j];
		i++, j++;
		if (j >= sub_len) return i - sub_len;
	}
	return -1;
}

int main() {
	//freopen("in", "r", stdin);
	while (gets(str)) {
		str_len = strlen(str);
		gets(buf);
		char *p = strtok(buf, " "), *cur = str;
		int pos;
		bool ok = 1;
		while (p && ok) {
			sub_len = strlen(p);
			//cout << "sub len " << sub_len << ' ' << p << endl;
			get_next(p);
			pos = kmp(cur, p);
			if (pos == -1) ok = 0;
			//cout << pos << ' ' << sub_len << endl;
			for (int i = 0; i < pos; i++) {
				if (cur[i] != ' ') cur[i] = '_';
			}
			if (cur[pos + sub_len] && cur[pos + sub_len] != ' ') cur[pos + sub_len] = '_';
			str_len -= sub_len + 1;
			cur += pos + sub_len + 1;
			//cout << cur << endl;
			p = strtok(0, " ");
		}
		//cout << cur << endl;
		int t = 0;
		while (cur[t]) {
			if (cur[t] != ' ') cur[t] = '_';
			t++;
		}
		//cout << str << endl;
		if (ok) puts(str);
		else puts("I HAVE FAILED!!!");
	}
	return 0;
}


