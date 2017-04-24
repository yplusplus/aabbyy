#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

struct Fraction {
    ll a, b;
    Fraction() : a(0), b(1) {}
    Fraction(ll a, ll b) : a(a), b(b) { this->reduction(); }
    Fraction operator + (Fraction x) {
        Fraction res(a * x.b + x.a * b, b * x.b);
        res.reduction();
        return res;
    }
    Fraction operator - (Fraction x) {
        Fraction res(a * x.b - x.a * b, b * x.b);
        res.reduction();
        return res;
    }
    Fraction operator * (Fraction x) {
        Fraction res(a * x.a, b * x.b);
        res.reduction();
        return res;
    }
    Fraction operator / (Fraction x) {
        Fraction res(a * x.b, b * x.a);
        res.reduction();
        return res;
    }
    bool operator >= (const Fraction &x) const {
        return a * x.b >= b * x.a;
    }
    void reduction() {
        ll d = __gcd(a, b);
        a /= d;
        b /= d;
    }
};

int main() {
    ll x, y;
    while (cin >> x >> y) {
        if (x > y) cout << "-1" << endl;
        else {
            ll ans = 0;
            Fraction nowy(1, 1);
            for (int i = 1; i < x; i++) {
                Fraction tmp((y + 1) * i, x);
                Fraction tmp2 = tmp - nowy;
                ll delta = tmp2.a / tmp2.b;
                if (tmp2.a % tmp2.b == 0) delta--;
                ans += delta + 1;
                nowy = nowy + Fraction(delta, 1);
                nowy = nowy + Fraction(nowy.a, nowy.b * i);
            }
            ans += y - nowy.a / nowy.b;
            cout << ans << endl;
        }
    }
    return 0;
}
