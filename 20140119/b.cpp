#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stack>
using namespace std;

const int N = 300;
string str;
int cnt[N];
stack<char> st;
int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		cin >> str;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < str.length(); i++) {
			if (!st.empty()) {
				if (str[i] == st.top()) st.pop();
				else {
					cnt[str[i]]++;
					cnt[st.top()]++;
					st.push(str[i]);
				}
			} else {
				st.push(str[i]);
			}
		}
		printf("Case %d\n", Case++);
		for (char ch = 'A'; ch <= 'Z'; ch++) {
			if (cnt[ch]) {
				printf("%c = %d\n", ch, cnt[ch]);
			}
		}
	}
	return 0;
}

