#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const double EPS = 1e-6;
const int N = 55555;
inline int sgn(double x) { return (x > EPS) - (x < -EPS);}
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator + (Point a) { return Point(x + a.x, y + a.y);}
	Point operator - (Point a) { return Point(x - a.x, y - a.y);}
	Point operator * (double p) { return Point(x * p, y * p);}
	Point operator / (double p) { return Point(x / p, y / p);}
} X[N], Y[N];

inline double cross(Point a, Point b) { return a.x * b.y - a.y * b.x;}
inline double dot(Point a, Point b) { return a.x * b.x + a.y * b.y;}

struct Line {
	Point s, t;
	Line() {}
	Line(Point s, Point t) : s(s), t(t) {}
	Point vec() { return t - s;}
	Point point(double p) { return s + vec() * p;}
} ;

inline Point llint(Line a, Line b) { return a.point(cross(b.vec(), a.s - b.s) / cross(a.vec(), b.vec()));}
typedef pair<double, int> PDI;
typedef pair<int, int> PII;
inline int lowbit(int x) { return x & (-x);}

struct BIT {
	int s[N];
	void init() { memset(s, 0, sizeof(s));}
	void add(int x, int d) { for (x; x < N; x += lowbit(x)) s[x] += d;}
	int sum(int x) { int ret = 0; for (x; x > 0; x -= lowbit(x)) ret += s[x]; return ret;}
} bit;

typedef pair<double, double> PDD;
PDI onl[N], onr[N];
PDD a[N];
PII idl[N], idr[N];
double YY[N];

int main() {
	//freopen("in", "r", stdin);
	int n;
	double L, R;
	while (~scanf("%d%lf%lf", &n, &L, &R)) {
		Line l1 = Line(Point(L, 0), Point(L, 1));
		Line l2 = Line(Point(R, 0), Point(R, 1));
		int para = 0, cnt = 0;
		double ax, ay, bx, by;
		int c = 0,cc = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lf%lf%lf%lf", &ax, &ay, &bx, &by);
			if (sgn(ax - bx) == 0) {
				if (sgn(L - ax) < 0 && sgn(ax - R) < 0) para++;
			} else {
				X[cnt] = Point(ax, ay);
				Y[cnt] = Point(bx, by);
				Point ipl = llint(Line(X[cnt], Y[cnt]), l1);
				onl[cnt] = PDI(ipl.y, cnt);
				Point ipr = llint(Line(X[cnt], Y[cnt]), l2);
				onr[cnt] = PDI(ipr.y, cnt);
				cnt++;
				YY[++ c] = ipr.y;
				a[++ cc] = PDD(ipl.y,ipr.y);
			}
		}
		sort(YY + 1,YY + c + 1);
		sort(a + 1,a + cc + 1);
		int tot = 1;
		for(int i = 2; i <= c; i ++)
			if(fabs(YY[i] - YY[tot]) > EPS) YY[++ tot] = YY[i];
		bit.init();
		int ans = 0;
		//for(int i = 1;i <= tot; i ++) cout << YY[i] << " ";
		//cout << endl;
		for(int i = 1; i <= cc; i ++) {
			int lt = 1,rt = tot,mid,id = -1;
			//cout << a[i].second << endl;
			while(lt <= rt) {
				mid = (lt + rt) / 2;
				//cout << lt << ' ' << rt << endl;
				if(fabs(a[i].second - YY[mid]) <= EPS) {
					id = mid;
					break;
				}
				else if(a[i].second > YY[mid]) lt = mid + 1;
				else rt = mid - 1;
			}
			//cout << id << endl;
			ans += bit.sum(N - 1) - bit.sum(id);
			bit.add(id,1);
	//		cout << id << endl;
		}
		printf("%d\n",ans + para * cnt);
	}
	return 0;
}