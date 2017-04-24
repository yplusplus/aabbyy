#include <bits/stdc++.h>
using namespace std;

char s[3333];
char w[256];
char t[111][1111];
int n, m;
int encode() {
	char str[10];
	scanf("%s", str);
	int a = str[0] - '0';
	int b = w[str[1]];
	if (str[2] == '+') b++;
	else if (str[2] == '-') b--;
	a += b / 12;
	b %= 12;
	return a * 12 + b;
}

double solve(int id) {
	int len = strlen(t[id]);
	int res = 0;
	for (int i = 0; i < 2000 + n; i++) {
		if (i + len < 1000) continue;
		int tmp = 0;
		if (1000 + n - i + 1 < res) break;
		for (int j = 0; j < len && i + j < 2000 + n; j++) {
			if (tmp + len - j <= res) break;
			tmp += s[i + j] == t[id][j];
		}
		res = max(res, tmp);
	}
	return res * 1.0 / len;
}

int main() {
	w['C'] = 0; w['D'] = 2; w['E'] = 4; w['F'] = 5; w['G'] = 7; w['A'] = 9; w['B'] = 11;
	while (~scanf("%d", &n)) {
		memset(s, 0, sizeof(0));
		for (int i = 0; i < n; i++) {
			s[i + 1000] = encode();
			//cout << (int) s[i + 1000] << " ";
		}
		//cout << endl;
		scanf("%d", &m);
		for (int i = 0, cnt; i < m; i++) {
			scanf("%d", &cnt);
			for (int j = 0; j < cnt; j++) {
				t[i][j] = encode();
				//cout << (int) t[i][j] << " ";
			}
			//cout << endl;
			printf("%.8f\n", solve(i));
		}
	}
	return 0;
}

