#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<char, LL> Instruction;
typedef vector<Instruction> Instructions;
typedef vector<int> Array;
#define x first
#define y second

void print(const Instructions &a) {
	for (int i = 0; i < a.size(); ++i) {
		cout << a[i].x << '-' << a[i].y << ' ';
	}
	cout << endl;
}

void update(Instructions &a, const Instructions &b) {
	LL sumA = 0, sumB = 0;
	for (int i = 0; i < a.size(); ++i) {
		sumA += a[i].y;
	}
	for (int i = 0; i < b.size(); ++i) {
		sumB += b[i].y;
	}
	//print(b); cout << sumA << ' ' << sumB << endl;
	if (sumA > sumB) {
		a = b;
	} else if (sumA == sumB) {
		int i = 0;
		while (i < a.size() && i < b.size()) {
			if (a[i] == b[i]) {
				++i;
				continue;
			}
			if (a[i].x > b[i].x) {
				a = b;
			} else if (a[i].x == b[i].x) {
				if (a[i].y != b[i].y) {
					if (a[i].y < b[i].y) {
						if (a[i + 1].x > b[i].x) {
							a = b;
						}
					} else {
						if (a[i].x > b[i + 1].x) {
							a = b;
						}
					}
				}
			}
			break;
		}
	}
}

LL a, m, p, q, r, s;
Instructions best;

void merge(Instructions &a) {
	Instructions temp;
	temp.push_back(a[0]);
	for (int i = 1; i < a.size(); ++i) {
		if (temp[temp.size() - 1].x == a[i].x) {
			temp[temp.size() - 1].y += a[i].y;
		} else {
			temp.push_back(a[i]);
		}
	}
	a = temp;
}

bool gao(int t, Instructions &ins) {
	const int K = 30;
	vector<LL> myExp(K);
	for (int i = myExp[0] = 1; i < K; ++i) {
		myExp[i] = myExp[i - 1] * m;
	}
	LL np = p * myExp[t], nq = q * myExp[t];
	// Add Times Range
	LL L = max((r - np + a - 1) / a, 0LL);
	LL R = (s - nq) / a;
	//cout << t << ": " << np << ' ' << nq << ' ' << L << ' ' << R << endl;
	if (L > R) {
		return 0;
	}
	LL current = 0;
	for (int i = t; i >= 0; --i) {
		LL d = (L - current - 1) / myExp[i];
		current += myExp[i] * d;
		//cout << myExp[i] << ' ' << current << endl;
		if (L <= current && current <= R) {
			if (d) ins.push_back(Instruction('A', d + 1));
			for (int j = i; j > 0; --j) {
				ins.push_back(Instruction('M', 1));
			}
			return 1;
		} else if (current + myExp[i] <= R) {
			if (d + 1) ins.push_back(Instruction('A', d + 1));
			for (int j = i; j > 0; --j) {
				ins.push_back(Instruction('M', 1));
			}
			return 1;
		} else {
			if (d) ins.push_back(Instruction('A', d));
			if (i) ins.push_back(Instruction('M', 1));
		}
	}
	return 1;
}

void solve() {
	if (r <= p && q <= s) {
		cout << "empty" << endl;
		return ;
	}
	if (q - p > s - r) {
		cout << "impossible" << endl;
		return ;
	}
	if (m == 1) {
		LL answer = (r - p + a - 1) / a;
		p += answer * a;
		q += answer * a;
		if (r <= p && q <= s) {
			cout << answer << 'A' << endl;
		} else {
			cout << "impossible" << endl;
		}
		return ;
	}
	LL maxMultiply = 0, d = q - p, tq = q;
	while (1) {
		d *= m;
		tq *= m;
		if (d > s - r || tq > s) {
			break;
		}
		maxMultiply += 1;
	}
	//cout << "Maxium Multiply Times: " << maxMultiply << endl;
	best.clear();
	best.push_back(Instruction('A', 1LL << 50));
	Instructions temp;
	for (int t = 0; t <= maxMultiply; ++t) {
		temp.clear();
		if (gao(t, temp)) {
			//cout << "Temp: "; print(temp);
			merge(temp);
			update(best, temp);
			//cout << "Best: "; print(best);
		}
	}
	if (best[0].y == (1LL << 50)) {
		cout << "impossible" << endl;
	} else {
		for (int i = 0; i < best.size(); ++i) {
			if (i) cout.put(' ');
			cout << best[i].y << best[i].x;
		}
		cout << endl;
	}
}

void test(LL p, LL q, const Instructions &op) {
	for (int i = 0; i < op.size(); ++i) {
		if (op[i].x == 'A') {
			p += op[i].y * a;
			q += op[i].y * a;
		} else {
			for (int j = 0; j < op[i].y; ++j) {
				p *= m;
				q *= m;
			}
		}
		//cout << p << ' ' << q << ' ' << r << ' ' << s << endl;
	}
}

int run() {
	int cas = 0;
	while (cin >> a >> m >> p >> q >> r >> s) {
		if (a + m + p + q + r + s == 0) {
			return 0;
		}
		cout << "Case " << ++cas << ": ";
		solve();
		test(p, q, best);
	}
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
