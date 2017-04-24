#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, int> Term;
typedef vector<Term> Terms;
const int T = 1111;

Term getTerm(const string &term) {
	//cout << term << endl;
	LL a;
	int b, p = 1;
	while (isdigit(term[p])) {
		++p;
	}
	string s1 = term.substr(0, p);
	//cout << "s1 " << s1 << endl;
	if (p == 1) {
		if (s1[0] == '+') {
			a = 1;
		} else {
			a = -1;
		}
	} else {
		stringstream in(s1);
		in >> a;
	}
	if (p >= term.length()) {
		return Term(a, 0);
	}
	while (p < term.length() && term[p] != '^') {
		++p;
	}
	++p;
	string s2 = (p < term.length() ? term.substr(p, term.length() - p) : "");
	//cout << "s2 " << s2 << endl;
	if (s2 == "") {
		b = 1;
	} else {
		stringstream in(s2);
		in >> b;
	}
	return Term(a, b);
}

void convert(const string &expression, Terms &terms) {
	int last = 0, end;
	while (end < expression.length()) {
		end = last + 1;
		while (end < expression.length() && (expression[end] != '+' && expression[end] != '-')) {
			++end;
		}
		terms.push_back(getTerm(expression.substr(last, end - last)));
		//cout << terms[terms.size() - 1].first << ' ' << terms[terms.size() - 1].second << endl;
		last = end;
	}
}

LL calTerm(const LL &x, const Term &term, const LL &mod) {
	LL result = (term.first % mod + mod) % mod;
	for (int i = 0; i < term.second; ++i) {
		result *= x;
		result %= mod;
	}
	return result % mod;
}

bool check(const Terms &term, const LL &mod) {
	for (int i = 0; i < T; ++i) {
		LL x = abs(rand()), sum = 0;
		for (int j = 0; j < term.size(); ++j) {
			sum += calTerm(x, term[j], mod);
			if (sum >= mod) {
				sum -= mod;
			}
		}
		if (sum) {
			return 0;
		}
	}
	return 1;
}

int run() {
	string expression;
	int cas = 0;
	srand(time(0));
	while (cin >> expression) {
		if (expression == ".") {
			break;
		}
		int i = expression.length() - 1;
		while (expression[i] != '/') {
			--i;
		}
		++i;
		stringstream in(expression.substr(i, expression.length() - i));
		LL mod;
		in >> mod;
		string temp = expression.substr(1, i - 3);
		if (temp[0] != '-') {
			temp = '+' + temp;
		}
		//cout << mod << ' ' << temp << endl;
		Terms terms;
		convert(temp, terms);
		cout << "Case " << ++cas << ": " << (check(terms, mod) ? "Always an integer" : "Not always an integer") << endl;
	}
	return 0;
}

int main() {
	//freopen("in_b", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
