#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
char str[111];

LL con(char *s, int l) {
	LL ret = s[0] & 1;
	for (int i = 1; i < l; i++) {
		LL c = (ret & 1) ^ (s[i] & 1);
		ret <<= 1;
		ret |= c;
	}
	return ret;
}

int main() {
	int n;
	while (cin >> n) {
		cin >> str;
		reverse(str, str + n);
		LL a = con(str, n);
		cin >> str;
		reverse(str, str + n);
		LL b = con(str, n);
		//cout << a << ' ' << b << endl;
		cout << abs(a - b) << endl;
	}
	return 0;
}


