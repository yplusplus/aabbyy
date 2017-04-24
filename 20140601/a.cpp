#include <cstdio>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;
typedef pair<LL, int> Node;
#define x first
#define y second

const int N = 123456;
const LL INF = 100000000000000000LL;
#define head(a) (a[N - 2])
#define tail(a) (a[N - 1])
LL temp[2][N], len[2], answer[2][N];
Node array[N << 1];

int run() {
	LL Length;
	while (cin >> Length) {
		int total = 0;
		for (int i = 0; i < 2; ++i) {
			head(temp[i]) = 0;
			cin >> tail(temp[i]);
			len[i] = tail(temp[i]);
			for (int j = 0; j < tail(temp[i]); ++j) {
				cin >> temp[i][j];
				array[total].x = temp[i][j];
				array[total].y = j << 1 | i;
				++total;
			}
			sort(temp[i], temp[i] + len[i]);
			--tail(temp[i]);
		}
		sort(array, array + total);
		//for (int i = 0; i < total; ++i) { cout << array[i].y << ' '; } cout << endl;
		LL *toRight = temp[0];
		LL *toLeft = temp[1];
		int h = 0, t = total - 1;
		LL currentTime = 0, offset = 0;
		//cout << "total " << total << endl;
		//const int T = 50000;
		for (int i = 0; i < total; ++i) {
			LL timeLeft = INF;
			//if (i < T) cout << toLeft[head(toLeft)] << ' ' << toRight[head(toRight)] << ' ' << offset << endl;
			if (head(toLeft) <= tail(toLeft)) timeLeft = toLeft[head(toLeft)] - offset;
			LL timeRight = INF;
			if (head(toRight) <= tail(toRight)) timeRight = Length - (toRight[tail(toRight)] + offset);
			currentTime += min(timeLeft, timeRight);
			//if (i < T) cout << "time " << currentTime << ' ' << offset << ' ' << timeLeft << ' ' << timeRight << endl;
			offset += min(timeLeft, timeRight);
			if (timeRight == timeLeft) {
				int a = array[h].y;
				int b = array[t].y;
				answer[a & 1][a >> 1] = currentTime;
				answer[b & 1][b >> 1] = currentTime;
				++head(toLeft);
				--tail(toRight);
				++h, --t;
				++i;
			} else if (timeLeft < timeRight) {
				int a = array[h].y;
				answer[a & 1][a >> 1] = currentTime;
				++head(toLeft);
				++h;
				offset = -offset;
				swap(toLeft, toRight);
			} else {
				int a = array[t].y;
				answer[a & 1][a >> 1] = currentTime;
				--tail(toRight);
				--t;
				offset = -offset;
				swap(toLeft, toRight);
			}
		}
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < len[i]; ++j) {
				if (j) cout.put(' '); cout << answer[i][j];
				//cout << answer[i][j] << ' ';
			}
			if (len[i]) cout << endl;
		}
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
