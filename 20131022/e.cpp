#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const char *ans[6] = { "trochee", "iamb", "dactyl", "amphibrach", "anapaest", "not a poem"};
char line[111], word[111];
bool stress[1111111];

char *get_word(char *p) {
	while (*p && (*p == '-' || *p == ' ')) p++;
	if (*p == 0) return 0;
	int t = 0;
	while (*p && *p != '-' && *p != ' ') word[t++] = *p, p++;
	//cout << (int *) p << endl;
	word[t] = 0;
	return p;
}

bool test(int n, int d) {
	for (int i = d; i < n; i++) if (stress[i - d] != stress[i]) return 0;
	return 1;
}

int count(int n) {
	int cnt = 0;
	for (int i = 0; i < n; i++) cnt += stress[i];
	return cnt;
}

int work(int n) {
	bool t1 = test(n, 2), t2 = test(n, 3);
	if (t1 && t2) return 5;
	if (!t1 && !t2) return 5;
	if (t1) {
		int cnt = count(2);
		if (cnt != 1) return 5;
		else if (stress[0]) return 0;
		else return 1;
	} else {
		int cnt = count(3);
		if (cnt != 1) return 5;
		else if (stress[0]) return 2;
		else if (stress[1]) return 3;
		else if (stress[2]) return 4;
	}
	return 5;
}

int main() {
	//freopen("in", "r", stdin);
	int n;
	while (cin >> n) {
		memset(stress, 0, sizeof(stress));
		gets(line);
		int mk = -1;
		for (int i = 0; i < n; i++) {
			int m = 0;
			gets(line);
			if (mk == 5) continue;
			char *p = line;
			//cout << line << endl;
			while (p = get_word(p)) {
				//cout << word << endl;
				if (word[0] == '[') stress[m++] = 1;
				else stress[m++] = 0;
			}
			int t = work(m);
			if (t == 5) mk = 5;
			else if (mk == -1) mk = t;
			else if (mk != t) mk = 5;
		}
		//cout << m << endl;
		//for (int i = 0; i < m; i++) cout << stress[i] << endl;
		cout << ans[mk] << endl;
	}
	return 0;
}




