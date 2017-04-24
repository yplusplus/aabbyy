#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
struct MFS {
	int fa[N];
	void init(int n) { for (int i = 0; i < n; ++i) fa[i] = i; }
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	void merge(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (fx == fy) return ;
		if (fx < fy) fa[fy] = fx;
		else fa[fx] = fy;
	}
	int getLength(int x) {
		int fx = find(x);
		return x - fx + 1;
	}
} mfs;

inline bool isLeft(char a) { return a == '(' || a == '['; }
inline bool isMatch(char a, char b) { return a == '(' && b == ')' || a == '[' && b == ']'; }

int run() {
	string s;
	while (cin >> s) {
		int len = s.length(), head, tail;
		head = 0;
		tail = -1;
		mfs.init(len);
		for (int i = 1; i < len; ++i) {
			if (isLeft(s[i])) continue;
			int l = mfs.getLength(i - 1);
			if (l == 1) {
				if (isMatch(s[i - 1], s[i])) {
					mfs.merge(i - 1, i);
					if (i - 2 >= 0 && mfs.getLength(i - 2) > 1) {
						mfs.merge(i - 1, i - 2);
					}
				}
			} else {
				assert(~l & 1);
				int p = i - l - 1;
				if (p >= 0) {
					if (isMatch(s[p], s[i])) {
						mfs.merge(p, p + 1);
						mfs.merge(i, i - 1);
					}
					if (p - 1 >= 0 && mfs.getLength(p - 1) > 1) {
						mfs.merge(p, p - 1);

					}
				}
			}
			if (mfs.getLength(i) > 1 && tail - head + 1 < mfs.getLength(i)) {
				head = mfs.find(i);
				tail = i;
			}
		}
		//cout << head << ' ' << tail << endl;
		cout << s.substr(head, tail - head + 1) << endl << endl;
	}
	return 0;
}

int main() {
	//cout << int('(') << ' ' << int(')') << endl;
	//cout << int('[') << ' ' << int(']') << endl;
	ios::sync_with_stdio(0);
	return run();
}
