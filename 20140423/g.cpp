#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> Point;
typedef pair<Point, int> Square;
typedef pair<Point, Point> Rectangle;
typedef pair<int, Rectangle> Figure;
#define x first
#define y second
const int N = 1 << 9;
Square sqr[N];

void print(const pair<Figure, int> &a) { cout << a.x.x << ' ' << a.x.y.x.x << ' ' << a.x.y.x.y << ' ' << a.x.y.y.x << ' ' << a.x.y.y.y << ' ' << a.y << endl; }

Figure convert(const Square &a, const Square &b) {
	Figure temp(a.y, Rectangle(Point(0, 0), Point(0, 0)));
	Point a1(0, 0), b1(b.x.x - a.x.x, b.x.y - a.x.y);
	Point a2(a1.x + a.y, a1.y + a.y);
	Point b2(b1.x + b.y, b1.y + b.y);
	Point c1(max(a1.x, b1.x), max(a1.y, b1.y));
	Point c2(min(a2.x, b2.x), min(a2.y, b2.y));
	if (c1.x >= c2.x || c1.y >= c2.y) return temp;
	if (c1.x == 0 && c1.y == 0 && c2.x == a.y && c2.y == a.y) {
		temp.x = 0;
		return temp;
	}
	if (c1.x == 0 && c2.x == a.y) {
		if (c1.y == 0) {
		} else if (c2.y == a.y) {
			c2.y -= c1.y;
			c1.y = 0;
		}
	}
	if (c1.y == 0 && c2.y == a.y) {
		if (c1.x == 0) {
		} else if (c2.x == a.y) {
			c2.x -= c1.x;
			c1.x = 0;
		}
	}
	//cout << a.x.x << ' ' << a.x.y << ' ' << b.x.x << ' ' << b.x.y << endl;
	temp.y = Rectangle(c1, c2);
	//print(pair<Figure, int>(temp, 0));
	return temp;
}

map<Figure, int> countFigure, countLeft[N], countRight[N];
Figure figure[N][N];

LL bruteForce(int n) {
	LL answer = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			for (int k = 0; k < n; ++k) {
				if (k == i || k == j) continue;
				for (int l = 0; l < n; ++l) {
					if (l == i || l == j || l == k) continue;
					answer += figure[i][j] == figure[k][l];
				}
			}
		}
	}
	return answer;
}

int run() {
	int n;
	//srand(time(0));
	//while (n = rand() % 200 + 1) {
	while (cin >> n) {
		for (int i = 0; i < n; ++i) cin >> sqr[i].x.x >> sqr[i].x.y >> sqr[i].y;
		//for (int i = 0; i < n; ++i) sqr[i].x.x = rand() % 100, sqr[i].x.y = rand() % 100, sqr[i].y = rand() % 100;
		//for (int i = 0; i < n; ++i) sqr[i].x.x = sqr[i].x.y = sqr[i].y = 1;
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) figure[i][j] = convert(sqr[i], sqr[j]);
		countFigure.clear();
		for (int i = 0; i < n; ++i) countLeft[i].clear(), countRight[i].clear();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				++countLeft[i][figure[i][j]];
				++countRight[j][figure[i][j]];
				++countFigure[figure[i][j]];
			}
		}
		//for_each(countFigure.begin(), countFigure.end(), print);
		LL answer = 0;
		for (map<Figure, int>::iterator mi = countFigure.begin(); mi != countFigure.end(); ++mi) {
			answer += (LL) mi->y * (mi->y - 1);
			//print(*mi);
		}
		//cout << "Debug " << answer << endl;
		for (int i = 0; i < n; ++i) {
			//cout << i << endl;
			//cout << "Left" << endl;
			for (map<Figure, int>::iterator mi = countLeft[i].begin(); mi != countLeft[i].end(); ++mi) {
				answer -= (LL) mi->y * (mi->y - 1);
				if (countRight[i].find(mi->x) != countRight[i].end()) answer -= (LL) mi->y * countRight[i][mi->x];
				//print(*mi);
			}
			//cout << "Right" << endl;
			for (map<Figure, int>::iterator mi = countRight[i].begin(); mi != countRight[i].end(); ++mi) {
				answer -= (LL) mi->y * (mi->y - 1);
				if (countLeft[i].find(mi->x) != countLeft[i].end()) answer -= (LL) mi->y * countLeft[i][mi->x];
				//print(*mi);
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				if (figure[i][j] == figure[j][i]) ++answer;
			}
		}
		cout << answer << endl;
		//LL bf = bruteForce(n);
		//if (bf != answer) {
		//	cout << bf << ' ' << answer << ' ' << n << endl;
		//	break;
		//} else cout << "Pass " << n << endl;
		//cout << bf << endl;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	freopen("squares.in", "r", stdin);
	freopen("squares.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}