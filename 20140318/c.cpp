#include <bits/stdc++.h>
using namespace std;

const int N = 5;
const int M = 1 << 8;
const int K = 26;
char mat[N][N];
int x[M], y[M];
int cx, cy, cur_letter;

inline void init() {
	cx = cy = 0;
	memset(x, -1, sizeof x);
	memset(y, -1, sizeof y);
	cur_letter = -1;
}

inline char get_ins() {
	++cur_letter;
	if (cur_letter + 'A' == 'J') ++cur_letter;
	cur_letter %= K;
	return cur_letter + 'A';
}

inline void fill(const char &c) {
	if (~x[c]) return ;
	mat[cx][cy] = c;
	x[c] = cx;
	y[c] = cy;
	++cy;
	if (cy >= N) cy = 0, ++cx;
}

string convert(const string &s) {
	//cout << s << endl;
	int ax = x[s[0]], ay = y[s[0]];
	int bx = x[s[1]], by = y[s[1]];
	string ret;
	if (ax == bx) ++ay, ++by;
	else if (ay == by) ++ax, ++bx;
	else swap(ay, by);
	ax %= N;
	bx %= N;
	ay %= N;
	by %= N;
	ret += mat[ax][ay];
	ret += mat[bx][by];
	return ret;
}

inline string fix(const string &s) {
	int l = s.length();
	string t;
	for (int i = 0; i < l; ++i) {
		char c = islower(s[i]) ? s[i] - 32 : s[i];
		if ('J' == c) c = 'I';
		if (!isalpha(c)) continue;
		t += c;
	}
	return t;
}

void print_mat() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) cout << mat[i][j];
		cout << endl;
	}
}

void get_mat(const string &key) {
	string s = fix(key);
	//cout << "Debug " << s << endl;
	init();
	int l = s.length();
	for (int i = 0; i < l; ++i) fill(s[i]);
	for (int i = 0; i < K; ++i) if (i + 'A' != 'J') fill(i + 'A');
	//print_mat();
}

string get_cipher(const string &plain) {
	string s = fix(plain), ans;
	//cout << "Debug " << s << endl;
	int cur = 0, l = s.length();
	while (cur < l) {
		if (s[cur + 1] && s[cur] != s[cur + 1]) ans += convert(s.substr(cur, 2)), cur += 2;
		else {
			char c;
			while (s[cur] == (c = get_ins())) ;
			ans += convert(s.substr(cur, 1) + c), ++cur;
		}
	}
	return ans;
}

int run() {
	int _;
	cin >> _;
	string buf;
	getline(cin, buf);
	for (int cas = 1; cas <= _; ++cas) {
		string key, plain;
		getline(cin, key);
		getline(cin, plain);
		get_mat(key);
		cout << "Case " << cas << ": " << get_cipher(plain) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_c", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
