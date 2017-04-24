#include <bits/stdc++.h>
using namespace std;

bool leap(int y)
{
	return y % 11 == 0;
}

int year[2][13];

long long cal(int x,int y)
{
	if(x > y) return 0;
	int len = (y - x) / 132;
	long long sum = 0;
	for(int i = 0; i < 132; i ++) {
		int m = (x + i) % 12 + 1;
		if(leap(x + i)) sum ++;
		for(int j = 1; j <= m; j ++) {
			sum += year[0][j];
		}
	}
	sum *= len;
	for(int i = x + 132 * len; i <= y; i ++) {
		int m = i % 12 + 1;
		for(int j = 1; j <= m; j ++) sum += year[0][j];
		sum += leap(i);
	}
	return sum;
}

int main()
{
	for(int i = 1; i <= 12; i ++) {
		year[0][i] = i * i * i;
		year[1][i] = i * i * i;
		if(i == 1) year[1][i] ++;
	}
	int m1,y1,d1,m2,y2,d2;
	char s[25];
	while(scanf("%s",s) != EOF) {
		m1 = 0,d1 = 0,y1 = 0;
		int pos = 0;
		for(pos; s[pos] != '-'; pos ++) {
			m1 = 10 * m1 + (s[pos]  - '0');
		}
		pos ++;
		for(pos; s[pos] != '-'; pos ++) {
			d1 = 10 * d1 + (s[pos] - '0');
		}
		pos ++;
		for(pos; s[pos]; pos ++)
			y1 = 10 * y1 + (s[pos] - '0');
		pos = 0;
		scanf("%s",s);
	//	cout << s << endl;
		m2 = 0,d2 = 0,y2 = 0;
		for(pos; s[pos] != '-'; pos ++) {
			m2 = 10 * m2 + (s[pos] - '0');
		}
		pos ++;
		for(pos; s[pos] != '-'; pos ++) {
			d2 = 10 * d2 + (s[pos] - '0');
		}
		pos ++;
		for(pos; s[pos]; pos ++)
			y2 = 10 * y2 + (s[pos] - '0');

		if (y2 < y1 || (y2 == y1 && m2 < m1) || (y2 == y1 && m2 == m1 && d2 < d1)) {
			swap(y1, y2);
			swap(m1, m2);
			swap(d1, d2);
		}
		assert(m1 && m2 && d1 && d2);
		if(y1 == y2) {
			long long ans = 0;
			if(m1 == m2) ans += d2 - d1 + 1;
			else {
				for(int i = m1 + 1; i < m2; i ++) ans += year[leap(y1)][i];
				ans += year[leap(y1)][m1] - d1 + 1;
				ans += d2;
			}
			printf("%lld\n",ans);
		}
		else {
			long long ans = cal(y1 + 1,y2 - 1);
			for(int i = m1 + 1; i <= y1 % 12 + 1; i ++)
				ans += year[leap(y1)][i];
			ans += year[leap(y1)][m1] - d1 + 1;
			ans += d2;
			for(int i = 1; i < m2; i ++)
				ans += year[leap(y2)][i];
			printf("%lld\n",ans);
		}
	}
	return 0;
}
