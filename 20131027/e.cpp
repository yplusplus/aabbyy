#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> Point;
#define x first
#define y second
bool get(Point &a) { return cin >> a.x >> a.y; }

Point A, B, C, D;
bool input() {
	if (!get(A)) return 0;
	if (!get(B)) return 0;
	if (!get(C)) return 0;
	if (!get(D)) return 0;
	return 1;
}

bool check() {
	bool a = (B.x - A.x > 0) ^ (B.y - A.y > 0);
	bool b = (D.x - C.x > 0) ^ (D.y - C.y > 0);
	return a ^ b;
}

LL work(bool k) {
	if (A.x > B.x) swap(A.x, B.x);
	if (A.y > B.y) swap(A.y, B.y);
	if (C.x > D.x) swap(C.x, D.x);
	if (C.y > D.y) swap(C.y, D.y);
	if (B.x < C.x || B.y < C.y) return 0;
	if (D.x < A.x || D.y < A.y) return 0;
	Point MA, MB;
	MA.x = max(A.x, C.x);
	MA.y = max(A.y, C.y);
	MB.x = min(B.x, D.x);
	MB.y = min(B.y, D.y);
	if (k) return max(abs(MA.x - MB.x), abs(MA.y - MB.y));
	return abs(MA.x - MB.x) + abs(MA.y - MB.y);
}

int main() {
	while (input()) cout << work(check()) << endl;
	return 0;
}

