#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int sg[110][110][110];

int dfs(int x,int y,int z)
{
	if(!x && !y && !z) return sg[x][y][z] = 1;
	if(!y && !z && x == 1) return sg[x][y][z] = 0;
	if(sg[x][y][z] != -1) return sg[x][y][z];
	sg[x][y][z] = 0;
	for(int i = 0; i < z; i ++)
		if(!dfs(x,y,i)) {
			//if(x == 3 && y == 1 && z == 0) {
			//	cout << "omg 1 " << i << endl;
			//}
			return sg[x][y][z] = 1;
		}
	for(int i = 0; i < y; i ++)
		if(!dfs(x,i,min(i,z))) {
			//if(x == 3 && y == 1 && z == 0) {
			//	cout << "omg 2 " << i << endl;
			//}
			return sg[x][y][z] = 1;
		}
	for(int i = 0; i < x; i ++)
		if(!dfs(i,min(i,y),min(i,z))) {
			//if(x == 3 && y == 1 && z == 0) {
			//	cout << "omg 3 " << i << endl;
			//}
			return sg[x][y][z] = 1;
		}
	return sg[x][y][z];
}

int main()
{
	memset(sg,-1,sizeof(sg));
	int t,id,p,q,r;
	cin >> t;
	dfs(100,100,100);
	while(t --) {
		cin >> id >> p >> q >> r;
		//int ans = dfs(p,q,r);
		cout << id << " ";
		if(sg[p][q][r] == 0 || p == 0) printf("L\n");
		else {
			cout << "W ";
			bool flag = false;
			for(int i = 0; i < p && !flag; i ++) {
				if(!dfs(i,min(i,q),min(i,r))) {
					cout << i + 1 << " " << 1 << endl;
					flag = true;
					break;
				}
			}
			for(int i = 0; i < q && !flag; i ++) {
				if(!dfs(p,i,min(r,i))) {
					cout << i + 1 << " " << 2 << endl;
					flag = true;
					break;
				}
			}
			for(int i = 0; i < r && !flag; i ++) {
				if(!dfs(p,q,i)) {
					flag = true;
					cout << i + 1 << " " << 3 << endl;
					break;
				}
			}
			//			cout << "why " << flag << endl;
		}
	}
	return 0;
}
