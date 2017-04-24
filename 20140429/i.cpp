#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
char a[N], b[N];
char c[N];
char mi[N], ma[N];
int n;

//void get_mi(int n, char a[], char b[]) { }

bool solve() {
	vector<int> pos;
	int first = -1;
	c[n] = 0;
	for (int i = 0; i < n; i++) {
		if (first != -1) {
			c[i] = '0';
			continue;
		}
		if (a[i] == '0') {
			if (b[i] == '1') c[i] = '1';
			else {
				c[i] = '0';
				pos.push_back(i);
				//cout << "change " << i << endl;
			}
		} else {
			if (b[i] == '1') {
				if (pos.empty()) return false;
				first = pos.back();
				//cout << "involed" << endl;
				c[first] = '1';
				for (int i = first + 1; i < n; i++) { c[i] = '0'; }
				//c[i] = '0';
				break;
			} else c[i] = '0';
		}
	}
	if (first != -1) {
		puts(a);
		puts(c);
		return true;
	}
	//cout << "******" << endl;
	//cout << first << " " << (int)pos.size() << endl;
	if (first == -1 && pos.empty()) return false;
	first = pos.back();
	c[first] = '1';
	for (int i = first + 1; i < n; i++) { c[i] = '0'; }
	puts(a);
	puts(c);
	return true;
}

void add_one(char a[]) {
	int c = 1;
	for (int i = n - 1; i >= 0; i--) {
		a[i] += c;	
		if (a[i] == '2') c = 1, a[i] = '0';
		else c = 0;
	}
}

int main() {
	while (cin >> n) {
		cin >> a >> b;
		if (!solve()) {
			add_one(a);
			memset(c, '0', sizeof(c));
			c[n] = 0;
			puts(a);
			puts(c);
		}
	}
	return 0;
}
