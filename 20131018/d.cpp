#include <bits/stdc++.h>
using namespace std;

map<int, int> state;

char maz[6][5][5];
int fac[10];
//0 - right
//1 - left
//2 - front
//2 - back
int rotate_id[4][6] = {
	{0, 4, 2, 5, 3, 1},
	{0, 5, 2, 4, 1, 3},
	{4, 1, 5, 3, 2, 0}, 
	{5, 1, 4, 3, 0, 2}
};

int rotate_face[4][6] = {
	{1, 1, 3, 1, 1, 1}, 
	{3, 3, 1, 3, 3, 3},
	{0, 3, 2, 1, 0, 2},
	{0, 1, 2, 3, 2, 0}
};

int encode(int id[], int face[]) {
	int t = 0;
	for (int i = 0; i < 6; i++) {
		t += (id[i] * 4 + face[i]) * fac[i];
	}
	return t;
}

void decode(int t, int id[], int face[]) {
	for (int i = 5; i >= 0; i--) {
		int tmp = t / fac[i];
		id[i] = tmp / 4;
		face[i] = tmp % 4;
		t %= fac[i];
	}
}

void rotate(int now, int op, int new_id[], int new_face[]) {
	int id[6], face[6];
	decode(now, id, face);
	for (int i = 0; i < 6; i++) {
		new_id[i] = id[rotate_id[op][i]];
		new_face[i] = (face[rotate_id[op][i]] + rotate_face[op][rotate_id[op][i]]) % 4;
	}
}

void rotate_maz(int id, int face, char new_maz[3][3]) {
	char tmp[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			new_maz[i][j] = tmp[i][j] = maz[id][i][j];
		}
	}
	for (int k = 0; k < face; k++) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				new_maz[i][j] = tmp[2 - j][i];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tmp[i][j] = new_maz[i][j];
			}
		}
	}
}

bool check(int t) {
	int id[6], face[6];
	decode(t, id, face);
	bool f1 = false, f2 = false;
	char new_maz[3][3];
	rotate_maz(id[0], face[0], new_maz);
	for (int i = 0; i < 3; i++) {
		f1 |= new_maz[2][i] == '*';
	}
	rotate_maz(id[2], face[2], new_maz);
	for (int i = 0; i < 3; i++) {
		f2 |= new_maz[2][i] == '*';
	}
	return f1 & f2;
}

int bfs(int init_state) {
	state.clear();
	queue<int> que;
	que.push(init_state);
	int id[6], face[6];
	state[init_state] = 0;
	while (!que.empty()) {
		int now = que.front();
		que.pop();
		//cout << now << endl;
		if (check(now)) return state[now];
		for (int i = 0; i < 4; i++) {
			rotate(now, i, id, face);
			int next = encode(id, face);
			if (state.count(next) > 0) continue;
			state[next] = state[now] + 1;
			que.push(next);
		}
	}
	return -1;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i <= 6; i++) fac[i] = fac[i - 1] * 24;
	while (~scanf("%s", maz[0][0])) {
		if (maz[0][0][0] == '#') break;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == 0 && j == 0) continue;
				scanf("%s", maz[i][j]);
			}
		}
		int id[6], face[6];
		for (int i = 0; i < 6; i++) {
			id[i] = i, face[i] = 0;
		}
		int init_state = encode(id, face);
		//cout << init_state << endl;
		int ans = bfs(init_state);
		printf("%d\n", ans);
	}
	return 0;
}

