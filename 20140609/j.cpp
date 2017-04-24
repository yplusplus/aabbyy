#include <bits/stdc++.h>
using namespace std;

struct Good {
	int base, cnt, type;
	Good() {}
	Good(int base, int cnt, char type) : base(base), cnt(cnt), type(type) {}
	bool operator<(const Good &x) const {
		if (cnt == x.cnt) return type > x.type;
		return cnt < x.cnt;
	}
	bool operator==(const Good &x) const {
		return cnt == x.cnt && type == x.type && base == x.base;
	}
};

const int M = 1111111;
int m;

void update(int &a, int b) {
	if (a == -1 || a > b) a = b;
}

vector<Good> goods;
vector<Good> vec;
int maps[M];
int Sum[555];
void init(int m) {
	//h
	int sum = 0;
	for (int i = 1; ; i++) {
		sum += i * i;
		if (sum > m) break;
		if (i >= 2) vec.push_back(Good(i, sum, 0));
	}
	//l
	sum = 0;
	for (int i = 1; ; i++) {
		int x = (i << 1) - 1;
		sum += x * x;
		if (sum > m) break;
		if (i >= 2) vec.push_back(Good(x, sum, 1));
	}
	sum = 0;
	for (int i = 1; ; i++) {
		int x = (i << 1);
		sum += x * x;
		if (sum > m) break;
		if (i >= 2) vec.push_back(Good(x, sum, 1));
	}
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
    memset(maps,-1,sizeof(maps));
    for (int i = 0; i < vec.size(); i++) {
		maps[vec[i].cnt] = i;
	}
    for(int i = vec.size() - 1; i >= 0; i --)
        Sum[i] = Sum[i + 1] + vec[i].cnt;
}
bool dfs(int i, int cnt, int need, int sum, int target) {
	if(Sum[i] + sum < target) return false;
    if(vec[i].cnt * (need - cnt) + sum < target) return false;
	if (sum == target) {
		return true;
	}
    if (cnt >= need) return false;
    int delta = target - sum;
	if (maps[delta] >= i) {
	    goods.push_back(vec[maps[delta]]);
	    return true;
    }
	if (i == vec.size()) {
		return false;
	}
	if (sum + vec[i].cnt <= target) {
		goods.push_back(vec[i]);
		if (dfs(i + 1, cnt + 1, need, sum + vec[i].cnt, target)) return true;
		goods.pop_back();
	}
	if (dfs(i + 1, cnt, need, sum, target)) return true;
	return false;
}

void solve(int m) {
	
	goods.clear();
    bool flag = false;
	for(int need = 1; need <= 6; need ++) {
        if(m > 2000 && need > 4) break;
        if(dfs(0,0,need,0,m)) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        puts(" impossible");
        return;
    }
	for (int i = 0; i < goods.size(); i++) {
		printf(" %d%c", goods[i].base, goods[i].type == 0 ? 'H' : 'L');
	}
	puts("");
}

int main() {
	int Case = 1;
	init(1000000);
	int m;
	while (~scanf("%d", &m), m) {
		printf("Case %d:", Case++);
		solve(m);
	}
	return 0;
}

