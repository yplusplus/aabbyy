#include <iostream>

using namespace std;

int a[3], b[3];
int main() {
	for (int i = 0; i < 3; i++) cin >> a[i] >> b[i];
	cout << b[2] - b[0] << ' ' << a[1] - a[0] << endl;
	return 0;
}
