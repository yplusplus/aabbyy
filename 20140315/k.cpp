#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string line;
	getline(cin, line);
	int pre = -1;
	int ans = 0;
	bool found = false;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == '(') {
			if (pre != -1) ans++;
			pre = i;
			found = false;
		} else if (line[i] == ')') {
			if (found) ans += 1 + (pre != -1);
			else if (pre == -1) ans++;
			pre = -1;
			found = false;
		} else if (isalpha(line[i]) || line[i] == ' ') {
			continue;
		} else {
			found = true;
		}
	}
	if (pre != -1) ans++;
	cout << ans << endl;
	return 0;
}
