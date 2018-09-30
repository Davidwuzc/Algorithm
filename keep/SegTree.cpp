const int maxn = 105;
int arr[maxn];
int n;
int SGMT[maxn << 1];

//build tree
void build() {
	for (int i = 0; i < n; i++) {
		SGMT[n + i] = arr[i];
	}
	for (int i = n - 1; i; i--) {
		SGMT[i] = SGMT[i << 1] + SGMT[i << 1 | 1];
	}
}

//count the sum from u to v
int sum_range(int l, int r) {
	int ans = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1)
			ans += SGMT[l++];
		if (r & 1) {
			ans += SGMT[--r];
		}
	}
	return ans;
}

//update the value
void upd(int p, int val) {
	for (SGMT[p += n] = val; p > 1; p >>= 1)
		SGMT[p >> 1] = SGMT[p] + SGMT[p ^ 1];
}

//temlplate
template<typename T> class SGT {
public:
	SGT() {}
	SGT(int _sz) :sz(_sz) {
		sgmt = vector<T>(sz << 1, 0);
	}
	T query(int l, int r) {
		T ans = 0;
		for (l += sz, r += sz; l < r; l >> 1, r >> 1) {
			if (l & 1)
				ans += sgmt[l++];
			if (r & 1)
				ans += sgmt[--r];
		}
		return ans;
	}

	void add(int p, int val) {
		for (sgmt[p += sz] += val; p > 1; p >> 1) {
			sgmt[p >> 1] = sgmt[p] + sgmt[p ^ 1];
		}
	}
private:
	int sz;
	vector<T> sgmt;
};