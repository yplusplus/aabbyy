#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
struct Fraction {
	long long a, b;
	Fraction() : a(0), b(1) {}
	Fraction(long long a, long long b) : a(a), b(b) {}
	void fix() {
		long long d = __gcd(a, b);
		a /= d;
		b /= d;
	}
};

typedef set<string>::iterator ssit;
typedef map<string, Fraction>::iterator msdit;
bool operator >=(const Fraction &x, const Fraction &y) {
	return x.a * y.b >= x.b * y.a;
}

Fraction operator+ (Fraction x, Fraction y) {
	Fraction res(x.a * y.b + x.b * y.a, x.b * y.b);
	res.fix();
	return res;
}

Fraction operator* (Fraction x, Fraction y) {
	Fraction res(x.a * y.a, x.b * y.b);
	res.fix();
	return res;
}

Fraction operator/ (Fraction x, Fraction y) {
	Fraction res(x.a * y.b, x.b * y.a);
	res.fix();
	return res;
}

map<string, Fraction> spam_word;
map<string, Fraction> good_word;
set<string> spam[N], good[N];
int s, g, n, t;

bool ismark(char ch) {
	return ch == '-' || ch == ',' || ch == '.' || ch == '!' || ch == '?';
}

void fix(string &message) {
	for (int i = 0; i < message.length(); i++) {
		if (isalpha(message[i])) {
			message[i] = tolower(message[i]);
		} else if (isdigit(message[i]) || ismark(message[i])) {
			message[i] = ' ';
		}
	}
}

void handle(string message, set<string> &words, map<string, Fraction> &counter) {
	fix(message);
	//cout << message << endl;
	stringstream input(message);
	string word;
	while (input >> word) {
		//cout << word << " ";
		if (words.count(word) == 0) {
			words.insert(word);
			counter[word] = counter[word] + Fraction(1, 1);
		}
	}
	//cout << endl;
}

void pre_calc() {
	for (msdit it = spam_word.begin(); it != spam_word.end(); it++) {
		it->second = it->second / Fraction(s, 1);
	}
	for (msdit it = good_word.begin(); it != good_word.end(); it++) {
		it->second = it->second / Fraction(g, 1);
	}
}

bool check(string line) {
	fix(line);
	Fraction ps(s, s + g);
	Fraction pg(g, s + g);
	string word;
	stringstream input(line);
	set<string> visit;
	int cnt = 0;
	int sum = 0;
	while (input >> word) {
		if (visit.count(word)) continue;
		sum++;
		visit.insert(word);
		Fraction res;
		Fraction t;
		if (spam_word.count(word) == 0 && good_word.count(word) == 0) continue;
		if (spam_word.count(word) == 0) continue;
		if (spam_word.count(word)) {
			t = spam_word[word] * ps;
			res = res + t;
		}
		if (good_word.count(word)) {
			res = res + (good_word[word] * pg);
		}
		if ((t / res) >= Fraction(1, 2)) cnt++;
	}
	return cnt * 100 >= t * sum;
}

int main() {
	freopen("spam.in", "r", stdin);
	freopen("spam.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> s >> g >> n >> t;
	//cout << s << " " << g << " " << n << " " << t << endl;
	string line;
	getline(cin, line);
	for (int i = 0; i < s; i++) {
		getline(cin, line);
		//cout << line << endl;
		handle(line, spam[i], spam_word);
	}
	for (int i = 0; i < g; i++) {
		getline(cin, line);
		//cout << line << endl;
		handle(line, good[i], good_word);
	}
	pre_calc();
	for (int i = 0; i < n; i++) {
		getline(cin, line);
		//cout << line << endl;
		if (check(line)) cout << "spam" << endl;
		else cout << "good" << endl;
	}
	return 0;
}
