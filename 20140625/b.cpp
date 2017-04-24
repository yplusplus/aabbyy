#include <bits/stdc++.h>
using namespace std;
 
namespace solveContinuous {
        typedef double DB;
        typedef pair<DB, DB> Dish;
        typedef vector<Dish> Dishes;
        typedef vector<DB> Array;
        const DB EPS = 1e-10;
        const DB FINF = 1e20;
        const int T = 1 << 7;
        Dishes dish;
        Array answer;
        inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
        void initialize(const Dishes &temp) {
                dish = temp;
        }
        void binarySearch(const DB &volume, DB &value) {
                DB l = -FINF, r = max_element(dish.begin(), dish.end())->first, m;
                for (int i = 0; i < T; ++i) {
                        m = (l + r) / 2;
                        DB sum = 0;
                        for (unsigned j = 0; j < dish.size(); ++j) {
                                if (m > dish[j].first) {
                                        continue;
                                }
                                if (sgn(dish[j].second)) {
                                        sum += (dish[j].first - m) / dish[j].second;
                                } else {
                                        sum = volume;
                                        break;
                                }
                        }
                        //cout << m << ' ' << sum << endl;
                        if (sum >= volume) {
                                l = m;
                        } else {
                                r = m;
                        }
                }
                bool flag = 0;
                for (unsigned i = 0; i < dish.size(); ++i) {
                        if (m <= dish[i].first && sgn(dish[i].second) == 0) {
                                flag = 1;
                                break;
                        }
                }
                value = 0;
                if (flag) {
                        DB remain = volume, mark = 0;
                        for (unsigned i = 0; i < dish.size(); ++i) {
                                if (m > dish[i].first) {
                                        continue;
                                }
                                if (sgn(dish[i].second)) {
                                        DB x = (dish[i].first - m) / dish[i].second;
                                        value += dish[i].first * x - dish[i].second * x * x / 2;
                                        remain -= x;
                                } else {
                                        mark = max(dish[i].first, mark);
                                }
                        }
                        value += mark * remain;
                } else {
                        for (unsigned i = 0; i < dish.size(); ++i) {
                                if (m > dish[i].first) {
                                        continue;
                                }
                                DB x = (dish[i].first - m) / dish[i].second;
                                value += dish[i].first * x - dish[i].second * x * x / 2;
                        }
                }
        }
        void solve() {
                answer.clear();
                answer.resize(10001, -FINF);
                answer[0] = 0;
                if (dish.size() == 0) {
                        return ;
                }
                for (int i = 1; i <= 10000; ++i) {
                        binarySearch(i, answer[i]);
                }
        }
        int test() {
                int n;
                while (cin >> n) {
                        dish.resize(n);
                        for (int i = 0; i < n; ++i) {
                                cin >> dish[i].first >> dish[i].second;
                        }
                        solve();
                        for (unsigned i = 0; i < answer.size(); ++i) {
                                cout << "Volume " << i << ": " << answer[i] << endl;
                        }
                }
                return 0;
        }
        void read() {
                DB x, y;
                scanf("%lf%lf", &x, &y);
                dish.push_back(Dish(x, y));
        }
} ;
 
const int N = 10010;
long long dp[N],f[N],ff[N],V;
int q[N];
 
long long cost(int x,int y,long long det_t,long long t)
{
    return (y - x) * t - (y - x) * (y - x - 1) / 2 * det_t;
}
 
long long cost1(int j,int k,long long det_t,long long t)
{
    return -f[j] + f[k] + (j * j + j) / 2 * det_t - (k * k + k) / 2 * det_t + j * t - k * t;
}
 
void update()
{
    int w,t,det_t;
    scanf("%d%d%d",&w,&t,&det_t);
    if(!det_t) {
        for(int i = w; i <= V; i ++)
            dp[i] = max(dp[i],dp[i - w] + t);
        return;
    }
    for(int i = 0; i < w; i ++) {
        int n = 0;
        for(int j = i; j <= V; j += w) {
            f[j / w] = dp[j];
            ff[j / w] = f[j / w];
            n ++;
        }
        int top = 0,tail = 1;
        q[0] = 0;
        for(int j = 1; j < n; j ++) {
            while(top + 1 < tail && f[q[top]] + cost(q[top],j,det_t,t) <= f[q[top + 1]] + cost(q[top + 1],j,det_t,t)) top ++;
            ff[j] = max(ff[j],f[q[top]] + cost(q[top],j,det_t,t));
            while(top + 1 < tail) {
                int x = q[tail - 1],y = q[tail - 2];
                if(cost1(j,x,det_t,t) * (x - y) <= cost1(x,y,det_t,t) * (j - x)) tail --;
                else break;
            }
            q[tail ++] = j;
        }
        for(int j = i; j <= V; j += w) {
            dp[j] = ff[j / w];
            if(dp[j] < (-1LL << 50)) dp[j] = -1LL << 51;
        }
    }
}
 
vector<double> continuous;
const double FINF = 1e20;
 
inline double get_value(unsigned a) {
        if (a >= continuous.size()) {
                return -FINF;
        }
        return continuous[a];
}
 
int main()
{
    for(int i = 1; i < N; i ++) dp[i] = -1LL << 51;
        dp[0] = 0;
    int n;
    cin >> n >> V;
    char cd[15];
    while(n --) {
        cin >> cd;
        if(cd[0] == 'D') {
            update();
        } else {
                        solveContinuous::read();
                }
    }
        solveContinuous::solve();
        continuous = solveContinuous::answer;
        //cout << continuous.size() << endl;
    double ans = -1LL << 60;
    for(int i = 0; i <= V; i ++) {
                //cout << i << ' ' << dp[i] << ' ' << get_value(V - i) << endl;
        if(dp[i] < (-1LL << 50)) continue;
        else ans = max(ans,dp[i] + get_value(V - i));
        }
    if(ans < (-1LL << 51)) printf("impossible\n");
    else printf("%.10lf\n",ans);
    return 0;
}

