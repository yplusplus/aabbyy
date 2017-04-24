#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 11;
int dp[444444];
int rot[8][4] = {{0, 1, 4, 3}, {1, 2, 5, 4}, {3, 4, 7, 6}, {4, 5, 8, 7},
	{3, 4, 1, 0}, {4, 5, 2, 1}, {6, 7, 4, 3}, {7, 8, 5, 4}};

int fac[N];

int encode(int a[]) {
	bool found = false;
	for (int i = 0; i < 9; i++) found |= a[i] != 0;
	if (!found) return 0;
	int ret = 0;
	for (int i = 0; i < 9; i++) {
		int cnt = 0;
		for (int j = i + 1; j < 9; j++) {
			if (a[i] > a[j]) cnt++;
		}
		ret += cnt * fac[9 - i - 1];
	}
	return ret + 1;
}

void decode(int value, int a[]) {
	bool vis[10] = {0};
	value--;
	for (int i = 0; i < 9; i++) {
		int cnt = value / fac[9 - i - 1];
		value %= fac[9 - i - 1];
		cnt++;
		for (int j = 0; j < 9; j++) {
			if (!vis[j]) cnt--;
			if (cnt == 0) { vis[j] = true, a[i] = j + 1; break;}
		}
	}
}

void output(int a[]) {
	for (int i = 0; i < 9; i++) cout << a[i];
	cout << endl;
}

void rotate(int a[], int b[], int k) {
	for (int i = 0; i < 9; i++) b[i] = a[i];
	//output(a);
	//cout << "????" << endl;
	//output(b);
	for (int i = 0; i < 3; i++) {
		swap(b[rot[k][i]], b[rot[k][i + 1]]);
	}
	//output(b);
}

int Y, target;
int bfs() {
	queue<int> que;
	int a[N], b[N];
	que.push(1);
	memset(dp, -1, sizeof(dp));
	dp[1] = 0;
	while (!que.empty()) {
		int value = que.front(); que.pop();
		if (value == target) { return dp[value]; }
		if (dp[value] >= Y) continue;
		decode(value, a);
		//output(a);
		//getchar();
		//getchar();
		//cout << "####" << endl;
		for (int i = 0; i < 8; i++) {
			rotate(a, b, i);
			//output(b);
			int v = encode(b);
			//cout << v << endl;
			if (dp[v] == -1) {
				dp[v] = dp[value] + 1;
				que.push(v);
			}
			//getchar();
			//getchar();
		}
	}
	return -1;
}

int main() {
	int Case = 1;
	fac[0] = 1;
	for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i;
	char str[N];
	while (true) {
		scanf("%1d%s", &Y, str);
		int a[N];
		for (int i = 0; i < 9; i++) a[i] = str[i] - '0';
		target = encode(a);
		//cout << Y << " " << target << endl;
		if (Y == 0 && target == 0) break;
		int ans = bfs();
		printf("%d. %d\n", Case++, ans);
	}
	return 0;
}