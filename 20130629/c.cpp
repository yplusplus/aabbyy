#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long mod;

struct matrix
{
	long long a[2][2];
	matrix() {
		memset(a,0,sizeof(a));
	}
	matrix operator * (const matrix &p) {
		matrix c;
		for(int i = 0; i < 2; i ++)
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < 2; k ++)
					c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
		return c;
	}
};

matrix pow(matrix t,int n)
{
	if(n == 1) return t;
	if(n & 1) return pow(t * t,n / 2) * t;
	return pow(t * t,n / 2);
}

int pri[3000010];
bool a[16000010];

void prime()
{
	int tot = 0;
	memset(a,false,sizeof(a));
	for(int i = 2; i < 16000010; i++) { 
		if(i == 4 || !a[i]) {
            pri[tot++] = i;
            for (long long j = 1LL * i * i; j < 16000010; j += i) {
                a[j] = true;
            }
        }
    }
    //cout << tot << endl;
}

int fib(int n)
{
    //n += 2;
    if(n <= 2) return 1;
    matrix a;
    a.a[0][0] = a.a[0][1] = a.a[1][0] = 1;
    a = pow(a,n - 2);
    return (a.a[0][0] + a.a[0][1]) % mod;
}

int main()
{
    prime();
    int t;
    int n,m,r;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d%d",&n,&m,&r);
        for(int i = pri[n]; ; i++) {
            mod = m;
            if(fib(i) == 0) {
                mod = r * m;
                printf("%d\n",fib(i) / m);
                break;
            }
        }
    }
    return 0;
}

