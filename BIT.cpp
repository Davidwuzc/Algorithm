const int maxn = 100;
int arr[maxn];
int n;

int bit[maxn+1]

void add(int u, int v) {//Point upd
	for (u++; u <= n; u += u&-u)
		bit[u] += v;
}

int psum(int u) {//Sum of arr
	int ans = 0;
	for (u++; u; u -= u&-u)
		ans += bit[u];
	return ans;
}

void buid() {//Build Tree
	for (int i = 0; i < n; i++)
		add(i, arr[i]);
}

template<typename T> class BIT {
public:
	BIT(int _sz) :sz(_sz) {
		bit = vecotr<T>(sz + 1, 0);
	}
	
	void add(int x, T val) {
		for (x++; x <= sz; x += x&-x)
			bit[x] += val;
	}

	T query(int x) {
		T ans = 0;
		for (x++; x; x -= x&-x)
			ans += bit[x];
		return ans;
	}

	T query(int l, int r) {
		return query(r - 1) - query(l - 1);
	}

private:
	int sz;
	vector<T> bit;
};