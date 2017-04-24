#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
int a[25];
int bit[1 << 15];
int n,m;
int mask[1 << 15];
int nxt[1 << 15];
int cost[1 << 15];
int solve1()
{
	for(int i = 0; i < (1 << m); i ++) {
		int tstate = 0,sum = 0,state = 0;
		for(int j = 0; j < m; j ++) {
			if(i & (1 << j)) {
				sum ++;
				tstate ^= (1 << j);
				if((j + 1) < m) tstate ^= (1 << (j + 1));
				if((j - 1) >= 0) tstate ^= (1 << (j - 1));
				state ^= (1 << j);
			}
		}
		cost[i] = sum;
		mask[i] = tstate;
		nxt[i] = state;
	}
	int mx = oo;
	for(int i = 0; i < (1 << m); i ++) {
		int sum = bit[i];
		int state = i,pre = a[1];
		for(int j = 0; j < m; j ++) {
			if(i & (1 << j)) {
				pre ^= (1 << j);
				if((j - 1) >= 0) pre ^= (1 << (j - 1));
				if((j + 1) < m) pre ^= (1 << (j + 1));
			}
		}
		for(int k = 2; k <= n; k ++) {
			sum += cost[pre];
			int tmp = a[k];
			tmp ^= state;
			tmp ^= mask[pre];
			state = nxt[pre];
			pre = tmp;
		}
		if(pre) continue;
		mx = min(mx,sum);
	}
	return mx;
}

int solve2()
{
    int b[25];
	for(int i = 0; i < 25; i ++) b[i] = a[i];
    for(int i = 0; i < 25; i ++) a[i] = 0;
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j < m; j ++) {
            if(b[i] & (1 << j)) a[i] ^= (1 << (m - j - 1));
        }
    }
    for(int i = 0; i < (1 << m); i ++) {
        int x = i,tstate = 0,state = 0,sum = 0;
        for(int j = 0; j < m; j ++) {
            if(x & (1 << j)) {
                x ^= (1 << j);
                if(j + 1 < m) x ^= (1 << (j + 1));
                tstate ^= (1 << j);
                if(j) tstate ^= (1 << (j - 1));
                if(j + 1 < m) tstate ^= (1 << (j + 1));
                if(j + 1 < m) state ^= (1 << (j + 1));
                sum ++;
            }
        }
        mask[i] = tstate;
        nxt[i] = state;
        cost[i] = sum;
    }
	int mx = oo;
	for(int i = 0; i < (1 << m); i ++) {
		int pre = a[1];
		int state = 0;
		int sum = bit[i];
		for(int j = 0; j < m; j ++) {
			if(i & (1 << j)) {
				pre ^= (1 << j);
				if((j - 1) >= 0) {
					pre ^= (1 << (j - 1));
				}
				if((j + 1) < m) {
                    pre ^= (1 << (j + 1));
                    state ^= (1 << (j + 1));
                }
			}
		}
		for(int i = 2; i <= n; i ++) {
			int tmp = a[i];
			tmp ^= state;
			tmp ^= mask[pre];
			if(mask[pre] == -1) {
				sum = oo;
				break;
			}
			sum += cost[pre];
			state = nxt[pre];
			pre = tmp;
		}
		if(pre == 0) mx = min(mx,sum);
	}
    for(int i = 0; i < 25; i ++) a[i] = b[i];
	return mx;
}

int solve3()
{
	for(int i = 0; i < (1 << m); i ++) {
		int tstate = 0,state = 0;
		int x = i;
		int sum = 0;
		for(int j = 0; j < m; j ++) {
			if(x & (1 << j)) {
				sum ++;
				tstate ^= (1 << j);
				state ^= (1 << j);
				if(j) tstate ^= (1 << (j - 1));
				if(j + 1 < m) tstate ^= (1 << (j + 1));
				x ^= (1 << j);
				if(j + 1 < m) x ^= (1 << (j + 1));
			}
		}
        
		cost[i] = sum;
		mask[i] = tstate;
		nxt[i] = state;
	}
	int mx = oo;
	for(int i = 0; i < (1 << m); i ++) {
		int sum = bit[i];
		int pre = a[1],state = 0;
		for(int j = 0; j < m; j ++) {
			if(i & (1 << j)) {
				pre ^= (1 << j);
				state ^= (1 << j);
				if(j) pre ^= (1 << (j - 1));
				if(j + 1 < m) pre ^= (1 << (j + 1));
			}
		}
		for(int k = 2; k <= n; k ++) {
			int tmp = a[k];
			tmp ^= state;
			tmp ^= mask[pre];
			sum += cost[pre];
			state = nxt[pre];
			pre = tmp;
		}
		if(!pre) mx = min(mx,sum);
	}
	return mx;
}

int solve4()
{
	for(int i = 0; i < (1 << m); i ++) {
		int tstate = 0,state = 0;
		int x = i;
		int sum = 0;
		for(int j = 0; j < m; j ++) {
			if(x & (1 << j)) {
				sum ++;
				x ^= (1 << j);
				if(j + 1 < m) x ^= (1 << (j + 1));
				state ^= (1 << j);
				if(j + 1 < m) state ^= (1 << (j + 1));
				if(j) tstate ^= (1 << (j - 1));
				tstate ^= (1 << j);
			}
		}
		cost[i] = sum;
		mask[i] = tstate;
		nxt[i] = state;
	}
	int mx = oo;
	for(int i = 0; i < (1 << m); i ++) {
		int pre = a[1],state = 0,sum = bit[i];
		for(int j = 0; j < m; j ++) {
			if(i & (1 << j)) {
				pre ^= (1 << j);
				if(j) pre ^= (1 << (j - 1));
				state ^= (1 << j);
				if(j + 1 < m) state ^= (1 << (j + 1));
			}
		}
		for(int i = 2; i <= n; i ++) {
			int tmp = a[i];
			tmp ^= state;
			tmp ^= mask[pre];
			sum += cost[pre];
			state = nxt[pre];
			pre = tmp;
		}
		if(!pre) mx = min(mx,sum);
	}
	return mx;
}
int main()
{
	for(int i = 1; i < (1 << 15); i ++)
		bit[i] = bit[i >> 1] + (i & 1);
	char s[35];
	while(scanf("%d%d",&n,&m) != EOF) {
		memset(a,0,sizeof(a));
		if(!n && !m) break;
		for(int i = 1; i <= n; i ++) {
			scanf("%s",s);
			for(int j = m - 1; j >= 0; j --) {
				if(s[j] == '1') a[i] = 2 * a[i] + 1;
				else a[i] = 2 * a[i];
			}
		}
		int t1,t2,t3,t4;
		int ansx = min(t1 = solve1(),t2 = solve2());
		int ansy = min(t3 = solve3(),t4 = solve4());
		if(min(ansx,ansy) == oo) printf("Impossible\n");
		else {
			ansx = min(ansx,ansy);
			if(ansx == t1) printf("1 %d\n",ansx);
			else if(ansx == t2) printf("2 %d\n",ansx);
			else if(ansx == t3) printf("3 %d\n",ansx);
			else printf("4 %d\n",ansx);
		}
	}
	return 0;
}


