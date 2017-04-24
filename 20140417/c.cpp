#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef long long LL;
map<string, int> ID;
inline int getID(const string &s) {
	if (ID.find(s) == ID.end()) ID[s] = ID.size() - 1;
	return ID[s];
}

const int N = 1 << 8;
const int M = 1 << 20;
const int K = 4;
const string ENTER = "Map";
// 0-up 1-down 2-left 3-right

struct Square {
	VI side[K], subIndex;
	LL block, maxID, length; // 0-unknow
	bool is01(const string &s) { return s == "0" || s == "1"; }
	void initialize(string str) {
		length = block = 0;
		subIndex.resize(K);
		for (int i = 0; i < K; ++i) side[i].clear();
		for (int i = 0; str[i]; ++i) if (str[i] == ',') str[i] = ' ';
		stringstream strin(str);
		string temp;
		bool isUnit = 0;
		for (int i = 0; i < K; ++i) {
			strin >> temp;
			if (is01(temp)) subIndex[i] = temp[0] - '0', isUnit = 1;
			else subIndex[i] = getID(temp);
		}
		if (isUnit) {
			length = 2;
			for (int i = 0; i < K; ++i) block |= subIndex[i];
			if (subIndex[0] == 1 && subIndex[1] == 0 && subIndex[2] == 0 && subIndex[3] == 1) ++block;
			if (subIndex[0] == 0 && subIndex[1] == 1 && subIndex[2] == 1 && subIndex[3] == 0) ++block;
			maxID = block;
			for (int i = 0; i < K; ++i) side[i >> 1].push_back(subIndex[i]);
			for (int i = 0; i < K; ++i) side[(i & 1) + 2].push_back(subIndex[i]);
			if (block == 2) {
				if (subIndex[0] == 1) side[1][1] = side[3][1] = 2;
				else side[1][0] = side[2][1] = 2;
			}
		}
	}
	void show() {
		cout << "Length " << length << "   Block " << block << "   maxID " << maxID << endl;
		for (int i = 0; i < K; ++i) cout << subIndex[i] << ' '; cout << endl;
		for (int i = 0; i < K; ++i) {
			cout << "Side " << i << ":";
			for (int j = 0, size = side[i].size(); j < size; ++j) cout << ' ' << side[i][j];
			cout << endl;
		}
	}
} square[N];
int mask[N], newID[M];

struct MFS {
	int fa[M];
	void initialize(int n) { for (int i = 1; i <= n; ++i) fa[i] = i; }
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (fx == fy) return 0;
		fa[fx] = fy;
		return 1;
	}
} mfs;

inline int cmp(int a, int b) { return square[a].length < square[b].length; }
void merge(const Square &a, const Square &b, const Square &c, const Square &d, Square &s) {
	assert(a.length == b.length && b.length == c.length && c.length == d.length);
	s.block = a.block + b.block + c.block + d.block;
	s.length = a.length << 1;
	for (int i = 0; i < K; ++i) s.side[i].resize(s.length);
	s.maxID = a.maxID + b.maxID + c.maxID + d.maxID;
	mfs.initialize(s.maxID);
	int la = 0, lb = la + a.maxID, lc = lb + b.maxID, ld = lc + c.maxID;
	for (int i = 0; i < a.length; ++i) {
		if (a.side[3][i] && b.side[2][i]) s.block -= mfs.merge(a.side[3][i] + la, b.side[2][i] + lb);
		if (a.side[1][i] && c.side[0][i]) s.block -= mfs.merge(a.side[1][i] + la, c.side[0][i] + lc);
		if (b.side[1][i] && d.side[0][i]) s.block -= mfs.merge(b.side[1][i] + lb, d.side[0][i] + ld);
		if (c.side[3][i] && d.side[2][i]) s.block -= mfs.merge(c.side[3][i] + lc, d.side[2][i] + ld);
	}
	// reID
	int current = 0;
	for (int i = 0; i <= s.maxID; ++i) newID[i] = 0;
	for (int i = 0, id; i < a.length; ++i) {
		if (a.side[0][i] == 0) continue;
		id = mfs.find(a.side[0][i] + la);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < a.length; ++i) {
		if (a.side[2][i] == 0) continue;
		id = mfs.find(a.side[2][i] + la);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < b.length; ++i) {
		if (b.side[0][i] == 0) continue;
		id = mfs.find(b.side[0][i] + lb);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < b.length; ++i) {
		if (b.side[3][i] == 0) continue;
		id = mfs.find(b.side[3][i] + lb);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < c.length; ++i) {
		if (c.side[1][i] == 0) continue;
		id = mfs.find(c.side[1][i] + lc);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < c.length; ++i) {
		if (c.side[2][i] == 0) continue;
		id = mfs.find(c.side[2][i] + lc);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < d.length; ++i) {
		if (d.side[1][i] == 0) continue;
		id = mfs.find(d.side[1][i] + ld);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < d.length; ++i) {
		if (d.side[3][i] == 0) continue;
		id = mfs.find(d.side[3][i] + ld);
		if (newID[id]) continue;
		newID[id] = ++current;
	}
	for (int i = 0, id; i < a.length; ++i) {
		if (a.side[0][i] == 0) s.side[0][i] = 0;
		else {
			id = mfs.fa[a.side[0][i] + la];
			s.side[0][i] = newID[id];
		}
	}
	for (int i = 0, id; i < a.length; ++i) {
		if (a.side[2][i] == 0) s.side[2][i] = 0;
		else {
			id = mfs.fa[a.side[2][i] + la];
			s.side[2][i] = newID[id];
		}
	}
	for (int i = 0, id; i < b.length; ++i) {
		if (b.side[0][i] == 0) s.side[0][i + b.length] = 0;
		else {
			id = mfs.fa[b.side[0][i] + lb];
			s.side[0][i + b.length] = newID[id];
		}
	}
	for (int i = 0, id; i < b.length; ++i) {
		if (b.side[3][i] == 0) s.side[3][i] = 0;
		else {
			id = mfs.fa[b.side[3][i] + lb];
			s.side[3][i] = newID[id];
		}
	}
	for (int i = 0, id; i < c.length; ++i) {
		if (c.side[1][i] == 0) s.side[1][i] = 0;
		else {
			id = mfs.fa[c.side[1][i] + lc];
			s.side[1][i] = newID[id];
		}
	}
	for (int i = 0, id; i < c.length; ++i) {
		if (c.side[2][i] == 0) s.side[2][i + c.length] = 0;
		else {
			id = mfs.fa[c.side[2][i] + lc];
			s.side[2][i + c.length] = newID[id];
		}
	}
	for (int i = 0, id; i < d.length; ++i) {
		if (d.side[1][i] == 0) s.side[1][i + d.length] = 0;
		else {
			id = mfs.fa[d.side[1][i] + ld];
			s.side[1][i + d.length] = newID[id];
		}
	}
	for (int i = 0, id; i < d.length; ++i) {
		if (d.side[3][i] == 0) s.side[3][i + d.length] = 0;
		else {
			id = mfs.fa[d.side[3][i] + ld];
			s.side[3][i + d.length] = newID[id];
		}
	}
	s.maxID = current;
}

int dfs(int x) {
	Square &sqr = square[x];
	if (sqr.length == 0) for (int i = 0; i < K; ++i) sqr.length = dfs(sqr.subIndex[i]) << 1;
	return sqr.length;
}

int run() {
	string buffer;
	while (cin >> buffer) {
		int p = 0;
		while (buffer[p] != '=') ++p;
		square[getID(buffer.substr(0, p))].initialize(buffer.substr(p + 1, buffer.length() - p));
	}
	dfs(getID(ENTER));
	int size = ID.size();
	for (int i = 0; i < size; ++i) mask[i] = i;
	sort(mask, mask + size, cmp);
	for (int i = 0, a[K]; i < size; ++i) {
		if (square[mask[i]].length <= 2) continue;
		for (int j = 0; j < K; ++j) a[j] = square[mask[i]].subIndex[j];
		merge(square[a[0]], square[a[1]], square[a[2]], square[a[3]], square[mask[i]]);
	}
	//for (map<string, int>::iterator mi = ID.begin(); mi != ID.end(); ++mi) cout << mi->first << ' ' << mi->second << endl;
	//for (int i = 0; i < size; ++i) square[i].show();
	//for (int i = 0; i < size; ++i) cout << mask[i] << ' '; cout << endl;
	cout << square[getID(ENTER)].block << endl;
	return 0;
}

int main() {
	freopen("map.in", "r", stdin);
	freopen("map.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
