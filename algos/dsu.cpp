#include <iostream>
#include <vector>
using namespace std;

struct DSU{
	vector<long long> parent, sizes;
	DSU(int N){
		parent.assign(N+1, -1);
		sizes.assign(N+1, -1);
	}
	void make_set(int v){
		if (parent[v] != -1) return;
		parent[v] = v;
		sizes[v] = 1;
	}
	int find_parent(int v){
		if (parent[v] == -1) return -1;
		if (parent[v] == v) return v;
		return parent[v] = find_parent(parent[v]);
	}
	int union_set(int a, int b){
		a = find_parent(a);
		b = find_parent(b);
		if (a != b){
			if (sizes[a] < sizes[b])
				swap(a, b);
			parent[b] = a;
			sizes[a] += sizes[b];
			return 1;
		}
		return 0;
	}
};