#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 128;
const int M = 18;
LL rec[N][M], tmp[N][M];
char ch[N], buf[N];

void match(char a) {
	for (int i = 0; i < 17; i++) {
		cin >> buf;
		rec[a][i] = 0;
		char *p = buf;
		while (*p) {
			rec[a][i] <<= 1;
			rec[a][i] |= *p == '*';
			p++;
		}
	}
}

LL tot[M];
void merge() {
	char *p = buf;
	memset(tot, 0, sizeof(tot));
	while (*p) {
		int k = *p;
		for (int i = 0; i < 16; i++) tot[i] |= rec[k][i];
		p++;
	}
}

void print(LL *a) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 43; j++) cout << (a[i] & 1ll << j ? '*' : '.');
		cout << endl;
	}
}

void cal() {
	int n = strlen(buf);
	for (int i = 0; i < n; i++) {
		int x = buf[i];
		memset(tmp[x], 0, sizeof(tmp[x]));
		for (int j = 0; j < n; j++) {
			if (j == i) continue;
			int y = buf[j];
			for (int k = 0; k < 16; k++) {
				tmp[x][k] |= rec[y][k];
			}
		}
	}
}

bool check(char a) {
	for (int i = 0; i < 16; i++) if ((tmp[a][i] ^ rec[a][i]) & rec[a][i]) return 1;
	return 0;
}

int main() {
	int n, k;
	ios::sync_with_stdio(0);
	while (cin >> n >> k) {
		cin >> ch;
		for (int i = 0; i < n; i++) match(ch[i]);
		for (int qry = 1; qry <= k; qry++) {
			cin >> buf;
			//merge();
			cal();
			//print(tot);
			char *p = buf;
			cout << "Query " << qry << ": ";
			while (*p) {
				//print(rec[*p]);
				cout << (check(*p) ? 'Y' : 'N');
				p++;
			}
			cout << endl;
		}
	}
	return 0;
}

