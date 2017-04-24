#include <bits/stdc++.h>
using namespace std;

const int DG = 1;
const int MOD = pow(10.0, (double) DG);
typedef vector<int> Array;
struct BigNumber {
	Array a;
	BigNumber() { a.resize(1, 0); }
	BigNumber(int x) {
		if (x == 0) {
			a.push_back(0);
			return ;
		}
		while (x > 0) {
			a.push_back(x % MOD);
			x /= MOD;
		}
	}
	void fix() {
		while (a.size() > 1 && a[a.size() - 1] == 0) {
			a.pop_back();
		}
	}
	int size() const { return a.size(); }
	void setSize(int x) { a.resize(x, 0); }
} ;
ostream &operator << (ostream &out, const BigNumber &a) {
	for (int i = a.size() - 1; i >= 0; --i) {
		out << a.a[i];
	}
	return out;
}

BigNumber operator * (const BigNumber &a, const BigNumber &b) {
	BigNumber c;
	int sl = a.size() + b.size();
	c.setSize(sl);
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			c.a[i + j] += a.a[i] * b.a[j];
		}
	}
	for (int i = 0; i < sl - 1; ++i) {
		c.a[i + 1] += c.a[i] / MOD;
		c.a[i] %= MOD;
	}
	c.fix();
	return c;
}

BigNumber operator + (const BigNumber &a, const BigNumber &b) {
	BigNumber c;
	int sl = max(a.size(), b.size()) + 1;
	c.setSize(sl);
	for (int i = 0; i < a.size(); ++i) {
		c.a[i] += a.a[i];
	}
	for (int i = 0; i < b.size(); ++i) {
		c.a[i] += b.a[i];
	}
	for (int i = 0; i < sl - 1; ++i) {
		if (c.a[i] >= MOD) {
			++c.a[i + 1];
			c.a[i] -= MOD;
		}
	}
	c.fix();
	return c;
}

BigNumber operator - (const BigNumber &a, const BigNumber &b) {
	BigNumber c;
	int sl = max(a.size(), b.size());
	c.setSize(sl);
	for (int i = 0; i < a.size(); ++i) {
		c.a[i] += a.a[i];
	}
	for (int i = 0; i < b.size(); ++i) {
		c.a[i] -= b.a[i];
	}
	for (int i = 0; i < sl - 1; ++i) {
		if (c.a[i] < 0) {
			--c.a[i + 1];
			c.a[i] += MOD;
		}
	}
	c.fix();
	return c;
}

bool operator <= (const BigNumber &a, const BigNumber &b) {
	if (a.size() > b.size()) return 0;
	if (a.size() < b.size()) return 1;
	for (int i = a.size() - 1; i >= 0; --i) {
		if (a.a[i] > b.a[i]) {
			return 0;
		}
		if (a.a[i] != b.a[i]) {
			break;
		}
	}
	return 1;
}

const int N = 111;
bool visit[N];
Array temp;

bool dfs(const Array &a, const int p, const bool flag, const bool equal) {
	if (p >= a.size()) {
		return 1;
	}
	if (flag) {
		for (int i = (equal ? a[p] : a.size()); i > 0; --i) {
			if (visit[i]) {
				continue;
			}
			visit[i] = 1;
			temp[p] = i;
			if (dfs(a, p + 1, flag, equal && i == a[p])) {
				return 1;
			}
			visit[i] = 0;
		}
	} else {
		for (int i = (equal ? a[p] : 1); i <= a.size(); ++i) {
			if (visit[i]) {
				continue;
			}
			visit[i] = 1;
			temp[p] = i;
			if (dfs(a, p + 1, flag, equal && i == a[p])) {
				return 1;
			}
			visit[i] = 0;
		}
	}
	return 0;
}

ostream &operator << (ostream &out, const Array &a) {
	for (int i = 0; i < a.size(); ++i) {
		out << a[i] << ' ';
	}
	out << endl;
	return out;
}

BigNumber cantor(const Array &a) {
	BigNumber result, multi(1), temp;
	for (int i = a.size() - 1; i >= 0; --i) {
		int cnt = 0;
		for (int j = i; j < a.size(); ++j) {
			cnt += a[i] > a[j];
		}
		temp = multi * BigNumber(cnt);
		//cout << "cantor " << multi << ' ' << BigNumber(cnt) << endl;
		result = result + temp;
		multi = multi * BigNumber(a.size() - i);
	}
	return result;
}

BigNumber convert(Array &a, const bool flag) { // 0: larger-equal  1: less-equal
	if (flag) {
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] == i + 1) {
				continue;
			}
			if (a[i] <= i) {
				return BigNumber();
			}
			break;
		}
	} else {
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] == a.size() - i) {
				continue;
			}
			if (a[i] > a.size() - i) {
				BigNumber result(1);
				for (int j = 1; j <= a.size(); ++j) {
					result = result * BigNumber(j);
				}
				result = result + BigNumber(1);
				return result;
			}
			break;
		}
	}
	temp.resize(a.size());
	memset(visit, 0, sizeof visit);
	assert(dfs(a, 0, flag, 1));
	return cantor(temp) + BigNumber(1);
}

int run() {
	int n;
	while (cin >> n) {
		Array a[2];
		for (int i = 0; i < 2; ++i) {
			a[i].resize(n);
			for (int j = 0; j < n; ++j) {
				cin >> a[i][j];
			}
		}
		BigNumber c[2];
		for (int i = 0; i < 2; ++i) {
			c[i] = convert(a[i], i);
		}
		//cout << c[0] << ' ' << c[1] << endl;
		cerr << c[0] << ' ' << c[1] << ' ' << (c[0] <= c[1]) << endl;
		if (c[0] <= c[1]) {
			cout << (c[1] - c[0] + BigNumber(1)) << endl;
		} else {
			cout << 0 << endl;
		}
	}
	return 0;
}

int main() {
	freopen("permutations.in", "r", stdin);
	freopen("permutations.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
