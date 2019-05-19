#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

string str[24] = {"5--", "2-", "1-", "4-", "3-", "6-", "5-", "7-", "1", "2", "3", "4", "5", "6", "1+", "7", "3+", "2+", "5+", "4+", "1++", "6+", "3++", "7+"};

int main()
{
	int n;
	while (cin >> n) {
		string c;
		for (int i = 0; i < n; i++) {
			cin >> c;
			if (c == "0") {
				putchar('X');
				continue;
			}
			int j = 0;
			for (;j < 24; j++) {
				if (c == str[j]) {
					break;
				}
			}
			if (j & 1) putchar('I');
			else putchar('E');
		}
		puts("");
	}
	return 0;
}

