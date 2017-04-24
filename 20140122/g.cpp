#include <bits/stdc++.h>
using namespace std;

int bit[1 << 20];

int main()
{
	memset(bit,0,sizeof(bit));
	int t,n,cd,x;
	int state[25];
	for(int i = 1; i < (1 << 20); i ++)
		bit[i] = bit[i >> 1] + (i & 1);
	cin >> t;
	while(t --) {
		cin >> n;
		memset(state,0,sizeof(state));
		for(int i = 0; i < n; i ++) {
			scanf("%d",&cd);
			while(cd --) {
				scanf("%d",&x);
				x --;
				state[i] |= (1 << x);
			}
			state[i] |= (1 << i);
		}
		int ans = n;
		for(int i = 1; i < (1 << n); i ++) {
			if(bit[i] >= ans) continue;
			bool flag = true;
			for(int j = 0; j < n; j ++)
				if(i & state[j]) continue;
				else {
					flag = false;
					break;
				}
			if(flag) ans = min(ans,bit[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
