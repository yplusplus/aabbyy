#include <bits/stdc++.h>
using namespace std;

const long long up = 999999999999999999LL;

int rev[62][41][28][24];

struct point
{
	int x,y,z,r;
	point() {}
	point(int x,int y,int z,int r):x(x),y(y),z(z),r(r) {}
}a[100010];

long long dp[20][100010];
int tot;

void init_dp()
{
	dp[0][0] = 1;
	for(int i = 0; i < 18; i ++)
		for(int j = 0; j < tot; j ++)
			if(dp[i][j])
				for(int k = 1; k < 10; k ++) {
					int x = a[j].x,y = a[j].y,z = a[j].z,r = a[j].r;
					int tmp = k;
					while(tmp % 2 == 0) tmp /= 2,x ++;
					while(tmp % 3 == 0) tmp /= 3,y ++;
					while(tmp % 5 == 0) tmp /= 5,z ++;
					while(tmp % 7 == 0) tmp /= 7,r ++;
					if(x < 62 && y < 41 && z < 28 && r < 24 && rev[x][y][z][r] != -1)
						dp[i + 1][rev[x][y][z][r]] += dp[i][j];
				}
}
	
void add(int num,int &x,int &y,int &z,int &r)
{
	while(num % 2 == 0) num /= 2,x ++;
	while(num % 3 == 0) num /= 3,y ++;
	while(num % 5 == 0) num /= 5,z ++;
	while(num % 7 == 0) num /= 7,r ++;
}

struct bignum
{
	long long a[40];
	bignum() {
		memset(a,0,sizeof(a));
	}
	bignum mult(int x) {
		bignum c;
		for(int i = 0; i < 40; i ++) {
			c.a[i] = a[i] * x;
		}
		for(int i = 0; i < 40; i ++) {
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
			//cout << i << " " << c.a[i] << endl;
		}
		return c;
	}

	bignum mult(bignum p) {
		bignum c;
		for(int i = 0; i < 40; i ++)
			for(int j = 0; i + j < 40; j ++)
				c.a[i + j] += a[i] * p.a[j];
		for(int i = 0; i < 40; i ++)
			if(c.a[i] >= 10) {
				c.a[i + 1] += c.a[i] / 10;
				c.a[i] %= 10;
			}
		return c;
	}

	bignum sub(bignum p) {
		bignum c;
		for(int i = 0; i < 40; i ++)
			c.a[i] = a[i] - p.a[i];
		for(int i = 0; i < 40; i ++)
			if(c.a[i] < 0) {
				c.a[i] += 10;
				c.a[i + 1] --;
			}
		return c;
	}

	bignum add(bignum p) {
		bignum c;
		for(int i = 0; i < 40; i ++)
			c.a[i] = a[i] + p.a[i];
		for(int i = 0; i < 40; i ++)
			if(c.a[i] >= 10) {
				c.a[i] -= 10;
				c.a[i + 1] ++;
			}
		return c;
	}

	void output() {
		int i = 39;
		for(; i >= 0; i --)
			if(a[i]) break;
		if(i == -1) i ++;
		printf("%lld",a[i]);
		for(i = i - 1; i >= 0; i --)
			printf("%lld",a[i]);
		printf("\n");
	}

	void init(long long m) {
		a[0] = m;
		for(int i = 0; i < 40; i ++)
			if(a[i] >= 10) {
				a[i + 1] += a[i] / 10;
				a[i] %= 10;
			}
	}
		
}p10[40];

long long p9[40];
long long c[40][40];
void solve()
{
	int n;
	char s[100];
	scanf("%d%s",&n,s + 1);
	int x = 0,y = 0,z = 0,r = 0;
	int xx = 0,yy = 0,zz = 0,rr = 0;
	int m1 = 0,m2 = 0,zero1 = 0,zero2 = 0;
	for(int i = 1; i <= 2 * n; i ++) {
		if(i <= n) {
			if(s[i] == '?') m1 ++;
			else if(s[i] == '0') zero1 = 1;
			else {
				add(s[i] - '0',x,y,z,r);
			}
		}
		else {
			if(s[i] == '?') m2 ++;
			else if(s[i] == '0') zero2 = 1;
			else {
				add(s[i] - '0',xx,yy,zz,rr);
			}
		}
	}
	if(zero1 && zero2) {
		p10[m1 + m2].output();
		printf("0\n");
	}
	else if(zero1) {
		long long ans = 0;
		for(int i = 1; i <= m2; i ++) {
			ans += c[m2][i] * p9[m2 - i];
		}
		bignum tmp;
		tmp.init(ans);
		for(int i = 1; i <= m1; i ++) tmp = tmp.mult(10);
		tmp.output();
		bignum temp = p10[m1 + m2];
		temp = temp.sub(tmp);
		temp.output();
	}
	else if(zero2) {
		long long ans = 0;
		for(int i = 1; i <= m1; i ++) {
			ans += c[m1][i] * p9[m1 - i];
		}
		bignum tmp,temp;
		tmp.init(ans);
		for(int i = 1; i <= m2; i ++) tmp = tmp.mult(10);
		tmp.output();
		temp = p10[m1 + m2];
		temp = temp.sub(tmp);
		temp.output();
	}
	else {
		bignum ans;
		for(int i = 1; i <= m1; i ++) {
			for(int j = 1; j <= m2; j ++) {
				bignum t1,t2,tt,ttt;
				t1.init(c[m1][i]);
				t2.init(c[m2][j]);
				tt.init(p9[m1 - i]);
				t1 = t1.mult(t2);
				t1 = t1.mult(tt);
				ttt.init(p9[m2 - j]);
				t1 = t1.mult(ttt);
				ans = ans.add(t1);
			}
		}
		for(int i = 0; i < tot; i ++) {
			if(a[i].x >= max(x,xx) && a[i].y >= max(y,yy) && a[i].z >= max(z,zz) && a[i].r >= max(r,rr)) {
				bignum t1,t2;
				int id1 = rev[a[i].x - x][a[i].y - y][a[i].z - z][a[i].r - r];
				int id2 = rev[a[i].x - xx][a[i].y - yy][a[i].z - zz][a[i].r - rr];
				if(id1 == -1 || id2 == -1) continue;
				t1.init(dp[m1][id1]);
				t2.init(dp[m2][id2]);
				t1 = t1.mult(t2);
				ans = ans.add(t1);
			}
		}
		ans.output();
		bignum tmp = p10[m1 + m2];
		tmp = tmp.sub(ans);
		tmp.output();
	}
}

int main()
{
	
	
	for(int i = 0; i < 40; i ++) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	memset(rev,-1,sizeof(rev));
	for(long long ii = 0,i = 1; i <= up; ii ++,i *= 2) {
		for(long long jj = 0,j = 1; i * j <= up; jj ++,j *= 3) {
			for(long long kk = 0,k = 1; i * j * k <= up; kk ++,k *= 5) {
				for(long long rr = 0,r = 1; i * j * k * r <= up; rr ++,r *= 7) {
					rev[ii][jj][kk][rr] = tot ++;
					a[tot - 1] = point(ii,jj,kk,rr);
				}
			}
		}
	}
	init_dp();
	p10[0].a[0] = 1;
	p9[0] = 1;
	for(int i = 1; i < 38; i ++) {
		p9[i] = p9[i - 1] * 9;
		p10[i] = p10[i - 1].mult(10);
		//cout << i << " ";
		//p10[i].output();
	}
	bool flag = false;
	int t;
	scanf("%d",&t);
	while(t --) {
		if(flag) printf("\n");
		flag = true;
		solve();
	}
	return 0;
}
