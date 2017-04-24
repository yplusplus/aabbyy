#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int N = 55555;
vector<pii> vec[N];
char number[N][13];
int n;
int dist[N];
int cost[15];
bool visit[N];
int pre[N];
int calc_lcp(int a, int b) {
	int res = 0;
	for (int i = 0; i < 10; i++) {
		if (number[a][i] == number[b][i]) res++;
		else break;
	}
	return res;
}

void spfa() {
	memset(dist, -1, sizeof(dist));
	memset(pre, -1, sizeof(pre));
	queue<int> que;
	que.push(1);
	dist[1] = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first, w = vec[u][i].second;
			if (dist[v] == -1 || dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pre[v] = u;
				if (!visit[v]) {
					que.push(v);
					visit[v] = true;
				}
			}
		}
	}
}

long long get_hash(char *str) {
	long long res = 0;
	for (int i = 0; i < 10; i++) {
		res *= 10;
		res += str[i] - '0';
	}
	return res;
}

void init() {
	char str[13];
	map<long long, int> mp;
	for (int i = 1; i <= n; i++) {
		mp[get_hash(number[i])] = i;
	}
	for (int i = 1; i <= n; i++) {
		strcpy(str, number[i]);
		//change a number
		for (int j = 0; j < 10; j++) {
			for (char k = '0'; k <= '9'; k++) {
				if (str[j] != k) {
					char t = str[j];
					str[j] = k;
					long long ret = get_hash(str);
					if (mp.count(ret)) {
						vec[i].push_back(make_pair(mp[ret], cost[calc_lcp(i, mp[ret])]));
					}
					str[j] = t;
				}
			}
		}
		//swap two number
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < j; k++) {
				swap(str[j], str[k]);
				long long ret = get_hash(str);
				if (mp.count(ret)) {
					vec[i].push_back(make_pair(mp[ret], cost[calc_lcp(i, mp[ret])]));
				}
				swap(str[j], str[k]);
			}
		}
	}
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < 10; i++) {
			scanf("%d", &cost[i]);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%s", number[i]);
			vec[i].clear();
		}
		init();
		spfa();
		if (dist[n] == -1) {
			puts("-1");
		} else {
			printf("%d\n", dist[n]);
			vector<int> path;
			int t = n;
			while (t != -1) {
				path.push_back(t);
				t = pre[t];
			}
			printf("%d\n", (int) path.size());
			for (int i = path.size() - 1; i >= 0; i--) {
				printf("%d%c", path[i], i == 0 ? '\n' : ' ');
			}
		}

	}
	return 0;
}
