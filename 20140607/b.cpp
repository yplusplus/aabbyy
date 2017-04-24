#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef vector<DB> Polynomial;
const DB PI = acos(-1.0);
const DB EPS = 1e-5;
const int MAXTIMES = 8;
const int T = 1 << 7;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Polynomial operator * (const Polynomial &a, const Polynomial &b) {
	int la = a.size();
	int lb = b.size();
	Polynomial s(la + lb - 1, 0);
	for (int i = 0; i < la; ++i) {
		for (int j = 0; j < lb; ++j) {
			s[i + j] += a[i] * b[j];
		}
	}
	return s;
}

Polynomial operator * (const Polynomial &a, const DB &p) {
	Polynomial s(a.size());
	for (int i = 0; i < a.size(); ++i) {
		s[i] = a[i] * p;
	}
	return s;
}

Polynomial convert(const Polynomial &a) {
	Polynomial s = a * a * PI;
	s.resize(s.size() + 1);
	for (int i = s.size() - 1; i > 0; --i) {
		s[i] = s[i - 1] / i;
	}
	s[0] = 0;
	return s;
}

DB calculate(const Polynomial &p, const DB &x) {
	DB sum = 0;
	for (int i = p.size() - 1; i >= 0; --i) {
		sum *= x;
		sum += p[i];
	}
	return sum;
}

DB find(const Polynomial &p, DB l, DB r, const DB &d) {
	DB m, mk = l;
	for (int i = 0; i < T; ++i) {
		m = (l + r) / 2;
		if (calculate(p, m) - calculate(p, mk) > d) {
			r = m;
		} else {
			l = m;
		}
	}
	return m;
}

void gao(const Polynomial &p, const DB &l, const DB &r, const DB &mx, const DB &d) {
	//cout << calculate(p, 0.51) - calculate(p, l) << endl; cout << calculate(p, 0.52) - calculate(p, l) << endl;
	for (int i = 1; i <= MAXTIMES; ++i) {
		if (sgn(mx - d * i) < 0) {
			break;
		}
		if (i > 1) cout.put(' ');
		cout << find(p, l, r, d * i) - l;
	}
	cout << endl;
}

int run() {
	int n, cas = 0;
	while (cin >> n) {
		Polynomial polynomial(n + 1);
		for (int i = 0; i <= n; ++i) {
			cin >> polynomial[i];
		}
		DB l, r, d;
		cin >> l >> r >> d;
		Polynomial newPolynomial = convert(polynomial);
		//for (int i = 0; i < newPolynomial.size(); ++i) { cout << newPolynomial[i] << ' '; } cout << endl;
		DB maxVolume = calculate(newPolynomial, r) - calculate(newPolynomial, l);
		cout << "Case " << ++cas << ": " << maxVolume << endl;
		if (sgn(maxVolume - d) >= 0) gao(newPolynomial, l, r, maxVolume, d);
		else cout << "insufficient volume" << endl;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	return run();
}
