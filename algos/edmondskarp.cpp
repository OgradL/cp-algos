#include <iostream>
#include <vector>
#include <queue>
using namespace std;

long long edmonds_karp(int N, int M, int source, int sink, vector<vector<int>>& adj, vector<vector<long long>>& capacity){
	
	vector<int> parent(N, -1);

	auto reachable = [&](){
		fill(parent.begin(), parent.end(), -1);
		queue<int> q;
		q.push(source);
		while (!q.empty()){
			int node = q.front();
			q.pop();
			for (int x : adj[node]){
				long long w = capacity[node][x];
				if (w <= 0 || parent[x] != -1) continue;
				q.push(x);
				parent[x] = node;
			}
		}
		return parent[sink] != -1;
	};

	long long flow = 0, curr_flow = 0;
	
	while (reachable()){
		curr_flow = 1e18;

		int node = sink;
		while (node != source){
			curr_flow = min(curr_flow, capacity[parent[node]][node]);
			node = parent[node];
		}
		node = sink;
		while (node != source){
			capacity[parent[node]][node] -= curr_flow;
			capacity[node][parent[node]] += curr_flow;

			node = parent[node];
		}
		flow += curr_flow;
	}

	return flow;
}


int main(){

	int N, M;
	cin >> N >> M;

	vector<vector<int>> adj(N);
	vector<vector<long long>> capacity(N, vector<long long>(N, 0));
	int a, b, c;
	for (int i = 0; i < M; i++){
		cin >> a >> b >> c;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		capacity[a][b] += c;
	}

	cout << edmonds_karp(N, M, 0, N-1, adj, capacity) << "\n";

	return 0;
}
