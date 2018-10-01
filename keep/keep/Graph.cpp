#include<vector>
#include <unordered_map>
#include <string>
using namespace std;
class Graph
{
public:
	Graph(int V) {
		this->V = V;
		this->E = 0;
	}

	Graph(vector<pair<int,int>> vs) {
		int E = vs.size();
		for (int i = 0; i < E; i++) {
			int v = vs[i].first;
			int w = vs[i].second;
			addEdge(v, w);
		}
	}

	void addEdge(int v, int w) {
		this->adj[v].push_back(w);
		this->adj[v].push_back(v);
		this->E++;
	}

	int V() {
		return this->V;
	}

	int E() {
		return this->E;
	}

	vector<int> adj(int v) {
		return this->adj[v];
	}

	string toString() {
		string s = ""+this->V + " vertices, " + this->E + " edges\n";
		for (int v = 0; v < this->V; v++) {
			s += v + ": ";
			for (int w : this->adj[v]) {
				s += w + " ";
			}
			s += "\n";
		}
		return s;
	}

private:
	const int V;
	int E;
	unordered_map<int, vector<int>> adj;
};

int degree(Graph G, int v) {
	return G.adj[v].size();
}

int maxDegree(Graph G) {
	int res = 0;
	for (int v = 0; v < G.V();v++) {
		if (res < degree(G, v)) {
			res = degree(G, v);
		}
	}
	return res;
}

double avgDegree(Graph G) {
	return 2.0*G.E() / G.V();
}

int numOfSelfLoops(Graph G) {
	int count = 0;
	for (int v = 0; v < G.V(); v++) {
		for (auto w : G.adj[v]) {
			if (v == w)
				count++;
		}
	}
	return count / 2;
}

