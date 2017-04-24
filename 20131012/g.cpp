#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 33;
int cnt[N];

int encode(int *a) {
	int ret = 0;
	for (int i = 2; i >= 0; i--) ret = ret * 3 + a[i];
	return ret;
}

void decode(int v, int *a) { for (int i = 0; i < 3; i++) a[i] = v % 3, v /= 3;}

typedef long long LL;

int dot(int *a, int *b) {
	int ret = 0;
	for (int i = 0; i < 3; i++) ret += a[i] * b[i];
	return ret;
}

int tmp[3];
void cross(int *a, int *b) {
	for (int i = 0; i < 3; i++) tmp[i] = a[(i + 1) % 3] * b[(i + 2) % 3];
	for (int i = 0; i < 3; i++) tmp[i] -= a[(i + 2) % 3] * b[(i + 1) % 3];
}

LL cal(int a, int b, int c) {
	int t[3];
	t[0] = a, t[1] = b, t[2] = c;
	sort(t, t + 3);
	a = t[0], b = t[1], c = t[2];
	if (a == b && b == c) return (LL) cnt[a] * (cnt[a] - 1) * (cnt[a] - 2);
	if (a == b || b == c) {
		if (a == b) return (LL) cnt[a] * (cnt[a] - 1) * cnt[c];
		else return (LL) cnt[a] * cnt[b] * (cnt[b] - 1);
	}
	return (LL) cnt[a] * cnt[b] * cnt[c];
}

LL cal() {
	int x[3], y[3], z[3];
	LL ans = 0;
	for (int i = 0; i < 27; i++) {
		decode(i, x);
		for (int j = 0; j < 27; j++) {
			decode(j, y);
			cross(x, y);
			for (int k = 0; k < 27; k++) {
				decode(k, z);
				//if (i == 4 && j == 13 && k == 22) cout << "??" << dot(tmp, z) % 3 << endl;
				if (dot(tmp, z) % 3) continue;
				ans += cal(i, j, k);
			}
		}
	}
	//decode(4, x);
	//decode(13, y);
	//decode(22, z);
	//cross(x, y);
	//cout << dot(tmp, z) << endl;
	return ans;
}


int main() {
	//freopen("in", "r", stdin);
	int _, n;
	ios::sync_with_stdio(0);
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> n;
		int x[3];
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) cin >> x[j];
			for (int j = 0; j < 3; j++) x[j] %= 3;
			cnt[encode(x)]++;
		}
		//for (int i = 0; i < 27; i++) cout << i << ' ' << cnt[i] << endl;
		cout << "Case #" << cas << ": " << cal() << endl;
	}
	return 0;
}

