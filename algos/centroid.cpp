#include <iostream>
#include <vector>
using namespace std;

const long long maxn = 2 * 1e5 + 42;

int n;
vector<int> G[maxn];
int subtree_size[maxn];

int get_subtree_size(int u, int v = -1) {
	int res = 1;
	for (int i : G[u]) {
		if (i == v) continue;
		res += get_subtree_size(i, u);
	}
	return subtree_size[u] = res;
}

int centroid(int u, int v = -1) {
	for (int i : G[u]) {
		if (i == v) continue;
		if (subtree_size[i] * 2 > n)
			return centroid(i, u);
	}
	return u;
}