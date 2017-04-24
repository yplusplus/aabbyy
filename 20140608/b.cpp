#include <bits/stdc++.h>
using namespace std;

typedef vector<int> Array;
typedef vector<string> Code;
typedef double DB;

void convert(Array &bar) {
	int maxWidth = *max_element(bar.begin(), bar.end());
	int minWidth = *min_element(bar.begin(), bar.end());
	int midWidth = maxWidth + minWidth >> 1;
	for (int i = 0; i < bar.size(); ++i) {
		bar[i] = (bar[i] > midWidth);
	}
}

const int UPBOUND = 200;
const int K = 100;
const DB EPS = 1e-8;
bool check(const Array &bar) {
	for (int narrow = 1; narrow <= UPBOUND * K; ++narrow) {
		int wide = narrow << 1;
		int a, b, c, d;
		a = ceil(narrow * 0.95 / K - EPS);
		b = floor(narrow * 1.05 / K + EPS);
		c = ceil(wide * 0.95 / K - EPS);
		d = floor(wide * 1.05 / K + EPS);
		bool ok = 1;
		for (int i = 0; i < bar.size(); ++i) {
			if (a <= bar[i] && bar[i] <= b || c <= bar[i] && bar[i] <= d) continue;
			ok = 0;
			break;
		}
		if (ok) {
			//cout << narrow << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;
			return 1;
		}
	}
	return 0;
}

map<string, char> toChar;
map<char, string> toCode;
const string START = "00110";
const string RSTART = "01100";
const string BADCODE = "bad code";
const string BADC = "bad C";
const string BADK = "bad K";

void preRun() {
	toCode.clear();
	toChar.clear();
	toCode['0'] = "00001";
	toCode['1'] = "10001";
	toCode['2'] = "01001";
	toCode['3'] = "11000";
	toCode['4'] = "00101";
	toCode['5'] = "10100";
	toCode['6'] = "01100";
	toCode['7'] = "00011";
	toCode['8'] = "10010";
	toCode['9'] = "10000";
	toCode['-'] = "00100";
	for (auto it = toCode.begin(); it != toCode.end(); ++it) {
		toChar[it->second] = it->first;
	}
}

inline int toID(char c) { return c == '-' ? 10 : c - '0'; }
inline bool isValid(const char c) { return toCode.find(c) != toCode.end(); }
inline bool isValid(const string &s) { return toChar.find(s) != toChar.end(); }

string getCode(const Array &bar, int &index) {
	string code(5, '0');
	for (int i = 0; i < 5; ++i) {
		if (index + i >= bar.size()) {
			return "";
		}
		code[i] |= bar[index + i];
	}
	index += 6;
	return code;
}

bool convert(const Array &bar, Code &code) {
	int ptr = 0;
	string temp;
	if (getCode(bar, ptr) != START) {
		return 0;
	}
	while (1) {
		temp = getCode(bar, ptr);
		//cout << temp << endl;
		if (temp == START) {
			break;
		}
		if (!isValid(temp)) return 0;
		if (bar[ptr - 1]) return 0;
		code.push_back(temp);
	}
	return ptr == bar.size() + 1;
}

inline bool isReverse(const Array &bar) { int ptr = 0; return getCode(bar, ptr) == RSTART; }

int getID(Code &code) {
	//cout << "convert " << code[code.size() - 1] << ' ' << code.size() << ' ' << isValid(code[code.size() - 1]) << endl;
	if (code.size() > 0 && isValid(code[code.size() - 1])) {
		int id = toID(toChar[code[code.size() - 1]]);
		code.pop_back();
		return id;
	}
	return -1;
}

string convert(const Code &code) {
	string result;
	for (int i = 0; i < code.size(); ++i) {
		result += toChar[code[i]];
	}
	return result;
}

int calculate(const string &s) {
	int sum = 0;
	for (int i = 0; i < s.length(); ++i) {
		sum += ((s.length() - i - 1) % 10 + 1) * toID(s[i]);
		sum %= 11;
	}
	return sum;
}

int calculate(const string &s, int C) {
	int sum = 0;
	for (int i = 0; i < s.length(); ++i) {
		sum += ((s.length() - i) % 9 + 1) * toID(s[i]);
		sum %= 11;
	}
	sum += (0 % 9 + 1) * C;
	sum %= 11;
	return sum;
}

string getMessage(Array &bar) {
	if (!check(bar)) return BADCODE;
	if (bar.size() < 29) return BADCODE;
	if ((bar.size() + 1) % 6) return BADCODE;
	convert(bar);
	if (isReverse(bar)) {
		reverse(bar.begin(), bar.end());
	}
	Code code;
	if (!convert(bar, code)) {
		return BADCODE;
	}
	//cout << convert(code) << endl;
	//for (int i = 0; i < code.size(); ++i) { cout << code[i] << endl; }
	int C, K, tC, tK;
	K = getID(code);
	C = getID(code);
	//cout << C << ' ' << K << endl;
	string answer = convert(code);
	tC = calculate(answer);
	tK = calculate(answer, tC);
	if (C == tC && K == tK) {
		return answer;
	} else if (C != tC) {
		return BADC;
	} else {
		return BADK;
	}
}

int run() {
	preRun();
	int n, cas = 0;
	while (cin >> n && n) {
		Array bar(n);
		for (int i = 0; i < n; ++i) {
			cin >> bar[i];
		}
		cout << "Case " << ++cas << ": " << getMessage(bar) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_b", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
