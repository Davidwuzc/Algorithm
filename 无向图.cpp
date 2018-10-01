#include <string>
#include <iostream>
#include<vector>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;
//无向图的数据结构
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
//深度优先
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
//广度优先
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