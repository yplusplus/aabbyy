#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
#define x first
#define y second

void fix(PLL &a) {
	LL gcd = __gcd(abs(a.x), abs(a.y));
	a.x /= gcd;
	a.y /= gcd;
	if (a.y < 0) {
		a.x = -a.x;
		a.y = -a.y;
	}
}

PLL operator + (const PLL &a, const PLL &b) {
	PLL s(a.x * b.y + a.y * b.x, a.y * b.y);
	fix(s);
	return s;
}

PLL operator - (const PLL &a, const PLL &b) {
	PLL s(a.x * b.y - a.y * b.x, a.y * b.y);
	fix(s);
	return s;
}

PLL operator * (const PLL &a, const PLL &b) {
	PLL s(a.x * b.x, a.y * b.y);
	fix(s);
	return s;
}

PLL operator / (const PLL &a, const PLL &b) {
	PLL s(a.x * b.y, a.y * b.x);
	fix(s);
	return s;
}

PLL evaluate(string x) {
	PLL s(0, 1);
	if ('(' == x[0]) x = x.substr(1, x.length() - 2);
	int c = 0, l = x.length();
	if (1 == x.length()) return PLL(x[0] - 48, 1);
	for (int i = 0; i < l; i++) {
		if ('(' == x[i]) c++;
		else if (')' == x[i]) c--;
		else if (!isdigit(x[i])) {
			if (c) continue;
			if ('+' == x[i]) s = evaluate(x.substr(0, i)) + evaluate(x.substr(i + 1, l - i - 1));
			if ('-' == x[i]) s = evaluate(x.substr(0, i)) - evaluate(x.substr(i + 1, l - i - 1));
			if ('*' == x[i]) s = evaluate(x.substr(0, i)) * evaluate(x.substr(i + 1, l - i - 1));
			if ('/' == x[i]) s = evaluate(x.substr(0, i)) / evaluate(x.substr(i + 1, l - i - 1));
			break;
		}
	}
	//cout << "evaluate " << x << ' ' << s.x << ' ' << s.y << endl;
	return s;
}

bool check(const string &s) {
	int l = s.length();
	for (int i = 0; i < l; i++) if (s[i] == 'X') return 1;
	return 0;
}

PLL ans;
int cal(string x, const PLL &s) {
	//cout << x << ' ' << s.x << ' ' << s.y << endl;
	if ("X" == x) {
		ans = s;
		return 1;
	}
	if ('(' == x[0]) x = x.substr(1, x.length() - 2);
	int c = 0, l = x.length();
	for (int i = 0; i < l; i++) {
		if ('X' == x[i]) continue;
		if ('(' == x[i]) c++;
		else if (')' == x[i]) c--;
		else if (!isdigit(x[i])) {
			if (c) continue;
			string a = x.substr(0, i);
			string b = x.substr(i + 1, l - i - 1);
			if (check(a)) {
				PLL vb = evaluate(b);
				if ('+' == x[i]) return cal(a, s - vb);
				if ('-' == x[i]) return cal(a, s + vb);
				if ('*' == x[i]) {
					if (0 == vb.x) {
						if (s.x) return 0;
						else return 2;
					} else return cal(a, s / vb);
				}
				if ('/' == x[i]) return cal(a, s * vb);
			} else {
				PLL va = evaluate(a);
				if ('+' == x[i]) return cal(b, s - va);
				if ('-' == x[i]) return cal(b, va - s);
				if ('*' == x[i]) {
					if (0 == va.x) {
						if (s.x) return 0;
						else return 2;
					} else return cal(b, s / va);
				}
				if ('/' == x[i]) {
					if (0 == s.x) {
						if (va.x) return 0;
						else return 2;
					} else {
						if (va.x) return cal(b, va / s);
						else return 0;
					}
				}
			}
		}
	}
	return -1;
}

void work(const string &s) {
	stringstream in(s);
	string tmp, a, b;
	stack<string> stk;
	while (in >> tmp) {
		//cout << tmp << endl;
		if (isdigit(tmp[0]) || 'X' == tmp[0]) stk.push(tmp);
		else {
			b = stk.top(); stk.pop();
			a = stk.top(); stk.pop();
			tmp = '(' + a + tmp + b + ')';
			stk.push(tmp);
		}
	}
	//cout << stk.top() << endl;
	if (!check(stk.top())) {
		if (evaluate(stk.top()).x) cout << "NONE" << endl;
		else cout << "MULTIPLE" << endl;
		return ;
	}
	int res = cal(stk.top(), PLL(0, 1));
	if (1 == res) cout << "X = " << ans.x << '/' << ans.y << endl;
	else if (0 == res) cout << "NONE" << endl;
	else cout << "MULTIPLE" << endl;
}

int main() {
	//freopen("in", "r", stdin);
	string buf;
	while (getline(cin, buf)) work(buf);
	return 0;
}
/*
1 1 X / /
1 1 X 2 - / /
1 X 1 - /
1 X 4 2 + / 1 - / 1 3 4 - / 1 - 4 2 - 1 + / +
1 1 1 X - / 1 - / 1 -
4 X * 2 + 2 /
2 2 * 
0 2 X / *
1 2 * X * 1 -
9 0 0 * X + 2 - / 5 /
0 X / 0 5 4 2 8 / / + + 5 6 / * - 4 1 - 4 * / 1 5 7 * + +
0 X / 1 -
*/
