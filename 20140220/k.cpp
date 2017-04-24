#include <bits/stdc++.h>
using namespace std;

const int N = 333;
int gray[N][N];

void get_color(int color[]) {
	char str[20];
	scanf("%s", str);
	for (int i = 1; i < 6; i += 2) {
		int a, b;
		if (isdigit(str[i])) a = str[i] - '0';
		else a = str[i] - 'A' + 10;
		if (isdigit(str[i + 1])) b = str[i + 1] - '0';
		else b = str[i + 1] - 'A' + 10;
		color[(i + 1) / 2] = a * 16 + b;
	}
}

int v[] = {0, 11, 16, 5};

int main() {
	int n, m;
	char brash;
	//freopen("in.txt", "r", stdin);
	while (~scanf("%d%c%d", &n, &brash, &m)) {
		//swap(n, m);
		//cout << n << " " << m << endl;
		int sum = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				int color[11];
				get_color(color);
				//cout << i << " " << j << " " << r << " " << g << " " << b << endl;
				int tmp = 0;
				for (int k = 1; k <= 3; k++) tmp += color[k] * v[k];
				gray[i][j] = tmp / 32;
				sum += gray[i][j];
				//cout << gray[i][j] << " ";
			}
			//cout << endl;
		}
		int ave = sum / (n * m);
		int limit = (192 + 2 * ave) / 3;
		printf("%dx%d\n", n, m);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (gray[i][j] < limit) putchar('9');
				else putchar(' ');
				if (j == n - 1) puts("");
				else putchar(' ');
			}
		}
	}
	return 0;
}

