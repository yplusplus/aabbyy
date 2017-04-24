#include <bits/stdc++.h>
using namespace std;

int king_dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int king_dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int knight_dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int knight_dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

	long long n;
bool check(long long x, long long y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

int main() {
	long long x, y;
	cin >> n >> x >> y;
	long long king = 0, knight = 0, bishop = 0, rook = 0, queen = 0;
	for (int i = 0; i < 8; i++) {
		long long nx = x + king_dx[i], ny = y + king_dy[i];
		king += check(nx, ny);
	}
	for (int i = 0; i < 8; i++) {
		long long nx = x + knight_dx[i], ny = y + knight_dy[i];
		knight += check(nx, ny);
	}
	bishop = min(x - 1, y - 1) + min(n - x, y - 1) + min(x - 1, n - y) + min(n - x, n - y);
	rook = 2 * (n - 1);
	queen = bishop + rook;
	printf("King: %lld\n", king);
	printf("Knight: %lld\n", knight);
	printf("Bishop: %lld\n", bishop);
	printf("Rook: %lld\n", rook);
	printf("Queen: %lld\n", queen);
	return 0;
}
