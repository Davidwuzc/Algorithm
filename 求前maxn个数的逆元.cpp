#include <algorithm>
#define ll long long
using namespace std;

const int maxn = 1000005;
const ll MOD = 1000000007;

ll qpw(ll a, ll b) {
	ll res = 1;
	if (b & 1)
		res = res * a % MOD;
	a *= a;
	b >> 1;
}

ll inv[maxn+1]
void pre_process() {
	inv[1] = 1;
	for (int i = 2; i <= maxn; i++) {
		inv[i] = (MOD - MOD / i)*inv[MOD%i] % MOD;
	}
}
