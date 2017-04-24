#include <bits/stdc++.h>
using namespace std;

const int N = 5;
const int M = 12;
char board[N][100];
int visit[15];
const int pos[][2] = {
				{0, 4},
   	{1, 1}, {1, 3}, {1, 5}, {1, 7},
		{2, 2},		   {2, 6},
	{3, 1}, {3, 3}, {3, 5}, {3, 7},
				{4, 4}
};

const int equ[6][4] = {
	{0, 2, 5, 7},
	{1, 2, 3, 4},
	{0, 3, 6, 10},
	{7, 8, 9, 10},
	{1, 5, 8, 11},
	{4, 6, 9, 11}
};

bool check() {
	for (int i = 0; i < 6; i++) {
		int xcnt = 0;
		int sum = 0;
		for (int j = 0; j < 4; j++) {
			int id = equ[i][j];
			int x = pos[id][0], y = pos[id][1];
			if (board[x][y] == 'x') xcnt++;
			else {
				sum += board[x][y] - 'A' + 1;
			}
		}
		if (sum == 26 && xcnt > 0) return false;
		if (sum > 26) return false;
		if (xcnt == 0 && sum != 26) return false;
	}
	return true;
}

bool dfs(int id) {
	if (id == 12) return true;
	int x = pos[id][0], y = pos[id][1];
	if (board[x][y] != 'x') {
		return dfs(id + 1);
	}
	for (int i = 0; i < M; i++) {
		if (visit[i]) continue;
		visit[i] = true;
		board[x][y] = 'A' + i;
		if (check() && dfs(id + 1)) return true;
		board[x][y] = 'x';
		visit[i] = false;
	}
	return false;
}

int main() {
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < N; i++) {
		scanf("%s", board[i]);
	}
	for (int i = 0; i < M; i++) {
		int x = pos[i][0], y = pos[i][1];
		if (board[x][y] != 'x') {
			visit[board[x][y] - 'A'] = true;
		}
	}
	dfs(0);
	for (int i = 0; i < N; i++) {
		printf("%s\n", board[i]);
	}
	return 0;
}
