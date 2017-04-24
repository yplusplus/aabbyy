// Template From SJTU Hao Yuan
#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1 << 8;
class HP {
	public:
		int len, s[MAXLEN];
		HP() { (*this) = 0; }
		HP(int inte) { (*this) = inte; };
		HP(const char *str) { (*this) = str; }
		friend ostream &operator << (ostream &out, const HP &x);
		HP operator = (int inte);
		HP operator = (const char *str);
		HP operator + (const HP &b);
		HP operator - (const HP &b);
		HP operator * (const HP &b);
		HP operator / (const HP &b);
		HP operator % (const HP &b);
		int Compare(const HP &b);
		bool operator == (int inte);
		bool operator == (const HP &b);
} ;

bool HP::operator == (const HP &b) { return Compare(b) == 0; }
bool HP::operator == (int inte) { return Compare(HP(inte)) == 0; }

ostream &operator << (ostream &out, const HP &x) {
	for (int i = x.len; i >= 1; --i) out << x.s[i];
	return out;
}

HP HP::operator = (const char *str) {
	len = strlen(str);
	for (int i = 1; i <= len; ++i) s[i] = str[len - i] - '0';
	return *this;
}

HP HP::operator = (int inte) {
	if (inte == 0) {
		len = 1;
		s[1] = 0;
		return (*this);
	}
	for (len = 0; inte > 0; ) {
		s[++len] = inte % 10;
		inte /= 10;
	}
	return (*this);
}

HP HP::operator * (const HP &b) {
	int i, j;
	HP c;
	c.len = len + b.len;
	for (i = 1; i <= c.len; ++i) c.s[i] = 0;
	for (i = 1; i <= len; ++i) {
		for (j = 1; j <= b.len; ++j) {
			c.s[i + j - 1] += s[i] * b.s[j];
		}
	}
	for (i = 1; i < c.len; ++i) {
		c.s[i + 1] += c.s[i] / 10;
		c.s[i] %= 10;
	}
	while (c.s[i]) {
		c.s[i + 1] = c.s[i] / 10;
		c.s[i] %= 10;
		++i;
	}
	while (i > 1 && !c.s[i]) --i;
	c.len = i;
	return c;
}

HP HP::operator + (const HP &b) {
	int i;
	HP c;
	c.s[1] = 0;
	for (i = 1; i <= len || i <= b.len || c.s[i]; ++i) {
		if (i <= len) c.s[i] += s[i];
		if (i <= b.len) c.s[i] += b.s[i];
		c.s[i + 1] = c.s[i] / 10;
		c.s[i] %= 10;
	}
	c.len = i - 1;
	if (c.len == 0) c.len = 1;
	return c;
}

HP HP::operator - (const HP &b) {
	int i, j;
	HP c;
	for (i = 1, j = 0; i <= len; ++i) {
		c.s[i] = s[i] - j;
		if (i <= b.len) c.s[i] -= b.s[i];
		if (c.s[i] < 0) {
			j = 1;
			c.s[i] += 10;
		} else j = 0;
	}
	c.len = len;
	while (c.len > 1 && !c.s[c.len]) --c.len;
	return c;
}

int HP::Compare(const HP &y) {
	if (len > y.len) return 1;
	if (len < y.len) return -1;
	int i = len;
	while (i > 1 && s[i] == y.s[i]) --i;
	return s[i] - y.s[i];
}

HP HP::operator / (const HP &b) {
	int i, j;
	HP d(0), c;
	for (i = len; i > 0; --i) {
		if (!(d.len == 1 && d.s[1] == 0)) {
			for (j = d.len; j > 0; --j) {
				d.s[j + 1] = d.s[j];
			}
			++d.len;
		}
		d.s[1] = s[i];
		c.s[i] = 0;
		while ((j = d.Compare(b)) >= 0) {
			d = d - b;
			++c.s[i];
			if (j == 0) break;
		}
	}
	c.len = len;
	while ((c.len > 1) && (c.s[c.len] == 0)) --c.len;
	return c;
}

HP HP::operator % (const HP &b) {
	int i, j;
	HP d(0);
	for (i = len; i > 0; --i) {
		if (!(d.len == 1 && d.s[1] == 0)) {
			for (j = d.len; j > 0; --j) {
				d.s[j + 1] = d.s[j];
			}
			++d.len;
		}
		d.s[1] = s[i];
		//cerr << i << ' ' << d << ' ' << b << endl;
		while ((j = d.Compare(b)) >= 0) {
			d = d - b;
			if (j == 0) break;
		}
		//cerr << i << endl;
	}
	//cerr << "d " << d << endl;
	return d;
}

HP gcd(HP a, HP b) {
	//cerr << a << ' ' << b << endl;
	return b.Compare(HP(0)) == 0 ? a : gcd(b, a % b);
}
class Factor {
	public:
		HP x, y;
		Factor() {}
		Factor(int x, int y) : x(HP(x)), y(HP(y)) {
			HP g = gcd(this->x, this->y);
			this->x = this->x / g;
			this->y = this->y / g;
		}
		Factor(HP x, HP y) : x(x), y(y) {
			HP g = gcd(this->x, this->y);
			this->x = this->x / g;
			this->y = this->y / g;
		}
} ;

ostream &operator << (ostream &out, const Factor &a) { out << a.x << '/' << a.y; return out; }

Factor operator + (Factor a, Factor b) {
	HP x = a.x * b.y + a.y * b.x;
	HP y = a.y * b.y;
	cerr << x << ' ' << y << ' ' << gcd(x, y) << endl;
	return Factor(x, y);
}

Factor operator - (Factor a, Factor b) {
	HP x = a.x * b.y - a.y * b.x;
	HP y = a.y * b.y;
	return Factor(x, y);
}

Factor operator * (Factor a, Factor b) {
	HP x = a.x * b.x;
	HP y = a.y * b.y;
	return Factor(x, y);
}

Factor operator / (Factor a, Factor b) {
	HP x = a.x * b.y;
	HP y = a.y * b.x;
	return Factor(x, y);
}

int run() {
	//cerr << gcd(HP(125), HP(144)) << endl; return 0;
	int n, m, k, c, l;
	while (cin >> n >> m >> k >> c >> l) {
		vector<string> wheel(n);
		for (int i = 0; i < n; ++i) {
			cin >> wheel[i];
		}
		vector<string> combination(c);
		vector<int> value(c);
		for (int i = 0; i < c; ++i) {
			cin >> combination[i] >> value[i];
		}
		for (int i = 0; i < l; ++i) {
			for (int j = 0, x; j < n; ++j) cin >> x;
		}
		Factor answer(0, 1);
		for (int i = 0; i < c; ++i) {
			Factor temp(value[i], 1);
			for (int j = 0; j < n; ++j) {
				if (combination[i][j] == '*') continue;
				int cnt = 0;
				for (int k = 0; k < m; ++k) {
					if (combination[i][j] == wheel[j][k]) ++cnt;
				}
				temp = temp * Factor(cnt, m);
			}
			cerr << temp << endl;
			answer = answer + temp;
			cerr << answer << endl;
		}
		//cerr << answer << endl;
		if (answer.x.Compare(answer.y) > 0) {
			answer = answer - Factor(1, 1);
			cout << answer << endl;
			cout << 1 << endl << 1 << endl;
		} else {
			cout << "0/1" << endl << 0 << endl;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("casino.in", "r", stdin);
	freopen("casino.out", "w", stdout);
	return run();
}
