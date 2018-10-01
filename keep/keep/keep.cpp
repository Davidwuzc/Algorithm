// keep.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include<vector>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;
class Graph
{
public:
	Graph(int V) {
		this->V = V;
		this->E = 0;
	}

	Graph(vector<pair<int, int>> vs) {
		int E = vs.size();
		for (int i = 0; i < E; i++) {
			int v = vs[i].first;
			int w = vs[i].second;
			addEdge(v, w);
		}
	}

	void addEdge(int v, int w) {
		adj[v].push_back(w);
		adj[w].push_back(v);
		E++;
	}

	int Vv() {
		return this->V;
	}

	int Ee() {
		return this->E;
	}

	vector<int> adjv(int v) {
		return this->adj[v];
	}

	string toString() {
		string s = "" + to_string(V) + " vertices, " + to_string(E) + " edges\n";
		for (int v = 0; v < (this->V); v++) {
			s += to_string(v) + ": ";
			for (int w : this->adj[v]) {
				s += to_string(w) + " ";
			}
			s += "\n";
		}
		return s;
	}

private:
	int V;
	int E;
	unordered_map<int, vector<int>> adj;
};

int degree(Graph G, int v) {
	return G.adjv(v).size();
}

int maxDegree(Graph G) {
	int res = 0;
	for (int v = 0; v < G.Vv(); v++) {
		if (res < degree(G, v)) {
			res = degree(G, v);
		}
	}
	return res;
}

double avgDegree(Graph G) {
	return 2.0*G.Ee() / G.Vv();
}

int numOfSelfLoops(Graph G) {
	int count = 0;
	for (int v = 0; v < G.Vv(); v++) {
		for (auto w : G.adjv(v)) {
			if (v == w)
				count++;
		}
	}
	return count / 2;
}

class DepthFS {
private:
	bool* mark;
	int count;

public:
	DepthFS(Graph G, int s) {
		mark = new bool[G.Vv()];
		dfs(G, s);
	}

	void dfs(Graph G, int v) {
		mark[v] = true;
		count++;
		for (auto w : G.adjv[v]) {
			if (!mark[w])
				dfs(G, w);
		}
	}

	bool marked(int w) {
		return mark[w];
	}

	int cnt() {
		return count;
	}
};

class Path {
private:
	bool* mark;
	int*  edgeTo;
	int s;
public:
	Path(Graph G, int s) {
		mark = new bool[G.Vv()];
		s = s;
		edgeTo = new int[G.Ee()];
		dfs(G, s);
	}

	void dfs(Graph G, int v) {
		mark[v] = true;
		for (auto w : G.adjv[v]) {
			if (!mark[w]) {
				edgeTo[w] = v;
				dfs(G, w);
			}
		}
	}

	bool hasPath(int v) {
		return mark[v];
	}

	stack<int> pathto(int v) {
		stack<int> res;
		if (!hasPath(v))
			return res;
		for (int x = v; x != s; x = edgeTo[v]) {
			res.push(x);
		}
		res.push(s);
		return res;
	}
};

class BreadFs {
private:
	bool* mark;
	int* edgeTo;
	int s;
public:
	BreadFs(Graph G, int s) {
		mark = new bool[G.Vv()];
		edgeTo = new int[G.Ee()];
		s = s;
		bfs(G, s);
	}

	void bfs(Graph G, int v) {
		queue<int> q;
		mark[v] = true;
		q.push(v);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int w : G.adjv[v]) {
				if (!mark[w]) {
					edgeTo[w]=v;
					mark[w] = true;
					q.push(w);
				}
			}
		}
	}

	bool hasPath(int v) {
		return mark[v];
	}

	stack<int> path(int v) {
		stack<int> res;
		if (!hasPath(v))
			return res;
		for (int x = v; x != s; x = edgeTo[v]) {
			res.push(x);
		}
		res.push(s);
		return res;
	}
};

//连通分量
class CC {
private:
	bool* mark;
	int* id;
	int count;

	void dfs(Graph G, int v) {
		mark[v] = true;
		id[v] = count;
		for (int w : G.adjv[v]) {
			if (!mark[w])
				dfs(G, w);
		}
	}

public:
	CC(Graph G) {
		mark = new bool[G.Vv()];
		id = new int[G.Vv()];
		count = 0;
		for (int s = 0; s < G.Vv(); s++) {
			if (!mark[s]) {
				dfs(G, s);
				count++;
			}
		}
	}

	bool connect(int v, int w) {
		return id[v] == id[w];
	}

	int get_id(int v) {
		return id[v];
	}
	int get_cnt() {
		return count;
	}
};

int main() {
	int V, E;
	cin >> V;
	cin >> E;
	Graph G(V);
	int v, w;
	for (int i = 0; i < E; i++) {
		cin >> v >> w;
		G.addEdge(v, w);
	}
	cout << G.toString() << endl;
	return 0;
}

//#include <iostream>
//#include <string>
//using namespace std;
//const int maxn = 50000 + 10;
//int arr[maxn];
//int n;
//int bit[maxn + 1];
//
//void add(int u, int v) {//Point upd
//	for (u++; u <= n; u += u&-u)
//		bit[u] += v;
//}
//
//int psum(int u) {//Sum of arr
//	int ans = 0;
//	for (u++; u >= 1; u -= u&-u)
//		ans += bit[u];
//	return ans;
//}
//
//int main()
//{
//	int t;
//	cin >> t;
//	int id = 1;
//	while (t--) {
//		cin >> n;
//		for (int i = 1; i <= n; i++) {
//			cin >> arr[i];
//			add(i, arr[i]);
//		}
//		cout << "Case " << id << ":" << endl;
//		id++;
//		string s;
//		int a, b;
//		while (true) {
//			cin >> s;
//			if (s == "Add") {
//				cin >> a >> b;
//				add(a, b);
//			}
//			else if (s == "Sub") {
//				cin >> a >> b;
//				add(a, -b);
//			}
//			else if (s == "Query") {
//				cin >> a >> b;
//				cout << psum(b) - psum(a - 1) << endl;;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	return 0;
//}
//#include<bits/stdc++.h>
//#include <string>
//#include <stdlib.h>
//#include <iostream>
//using namespace std;
//const int maxn = 200020;
//const int INF = 100000;
//int n;
//int SGMT[maxn << 1];
//int max(int a, int b)
//{
//	if (a < b)
//		return b;
//	return a;
//}
////build tree
//void build() {
//	for (int i = n - 1; i; i--) {
//		//SGMT[i] = SGMT[i << 1] + SGMT[i << 1 | 1];
//		SGMT[i] = max(SGMT[i << 1], SGMT[i << 1 | 1]);
//	}
//}
//
////count the sum from u to v
//int sum_range(int l, int r) {
//	int ans = -INF;
//	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
//		if (l & 1)
//			ans = max(ans,SGMT[l++]);
//		if (r & 1) {
//			ans = max(SGMT[--r],ans);
//		}
//	}
//	return ans;
//}
//
////update the value
//void upd(int p, int val) {
//	for (SGMT[p += n] = val; p > 1; p >>= 1)
//		SGMT[p >> 1] = max(SGMT[p], SGMT[p ^ 1]);
//}
//int main() {
//	int m;
//	cin >> n >> m;
//	for (int i = 0; i < n; i++)
//		cin >> SGMT[i+n];
//	build();
//	char C;
//	int a, b;
//	for (int i = 0; i < m; i++) {
//		cin >> C >> a >> b;
//		if (C == 'Q') {
//			cout << sum_range(a - 1, b) << endl;
//		}
//		else {
//			upd(a - 1, b);
//		}
//	}
//	return 0;
//}

//int main()
//{
//	int t;
//	scanf("%d", &t);
//	int case1 = 1;
//	while (t--)
//	{
//		scanf("%d", &n);
//		memset(SGMT, 0, sizeof(SGMT));
//		for (int i = 0; i < n; i++)
//			scanf("%d", &arr[i]);
//		build();
//		char ch[10];
//		printf("Case %d:\n", case1++);
//		while (~scanf("%s", ch))
//		{
//			if (ch[0] == 'E')
//				break;
//			else if (ch[0] == 'Q')
//			{
//				int l, r;
//				scanf("%d %d", &l, &r);
//				int sum = sum_range(l-1,r);
//				printf("%d\n", sum);
//			}
//			else if (ch[0] == 'A')
//			{
//				int p, val;
//				scanf("%d %d", &p, &val);
//				upd(p-1, val);
//			}
//			else {
//				int p, val;
//				scanf("%d %d", &p, &val);
//				upd(p-1, -val);
//			}
//		}
//	}
//	return 0;
//}
//const int maxn = 5e4 + 10;
//int a[maxn], bit[maxn];
//int n;
//void add(int u, int v) {//Point upd
//	for (; u <= n; u += u&-u)
//		bit[u] += v;
//}
//
//int psum(int u) {//Sum of arr
//	int ans = 0;
//	for (; u>=1; u -= u&-u)
//		ans += bit[u];
//	return ans;
//}
//int main()
//{
//	int t;
//	scanf("%d", &t);
//	int case1 = 1;
//	while (t--)
//	{
//		scanf("%d", &n);
//		memset(bit, 0, sizeof(bit));
//		for (int i = 1; i <= n; i++)
//			scanf("%d", &a[i]), add(i, a[i]);
//		char ch[10];
//		printf("Case %d:\n", case1++);
//		while (~scanf("%s", ch))
//		{
//			if (ch[0] == 'E')
//				break;
//			else if (ch[0] == 'Q')
//			{
//				int l, r;
//				scanf("%d %d", &l, &r);
//				int sum = psum(r) - psum(l - 1);
//				printf("%d\n", sum);
//			}
//			else if (ch[0] == 'A')
//			{
//				int p, val;
//				scanf("%d %d", &p, &val);
//				add(p, val);
//			}
//			else {
//				int p, val;
//				scanf("%d %d", &p, &val);
//				add(p, -val);
//			}
//		}
//	}
//	return 0;
//}
//#include <iostream>
//#include <string>
//using namespace std;
//const int maxn = 50000+10;
//int arr[maxn];
//int n;
//int bit[maxn + 1];
//
//void add(int u, int v) {//Point upd
//	for (u++; u <= n; u += u&-u)
//		bit[u] += v;
//}
//
//int psum(int u) {//Sum of arr
//	int ans = 0;
//	for (u++; u>=1; u -= u&-u)
//		ans += bit[u];
//	return ans;
//}
//
//int main()
//{
//	int t;
//	cin >> t;
//	int id = 1;
//	while (t--) {
//		cin >> n;
//		for (int i = 1; i <= n; i++) {
//			cin >> arr[i];
//			add(i, arr[i]);
//		}
//		cout << "Case " << id << ":" << endl;
//		id++;
//		string s;
//		int a, b;
//		while (true) {
//			cin >> s;
//			if (s == "Add") {
//				cin >> a >> b;
//				add(a, b);
//			}
//			else if (s == "Sub") {
//				cin >> a >> b;
//				add(a, -b);
//			}
//			else if (s == "Query") {
//				cin >> a >> b;
//				cout << psum(b) - psum(a-1) << endl;;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	return 0;
//}

