#include <iostream>
#include <vector>
using namespace std;

const int N_NODES = 2e7;

struct Node{
	int l = -1;
	int r = -1;
	long long lazyAdd = 0;
	long long sum = 0;
};

vector<Node> nodes;
int nodes_idx = 0;

int new_node(){
	return nodes_idx++;
}

int copy_node(const Node& node){
	int idx = nodes_idx++;
	nodes[idx].l = node.l;
	nodes[idx].r = node.r;
	nodes[idx].sum = node.sum;
	nodes[idx].lazyAdd = node.lazyAdd;
	return idx;
}


void apply(Node& node, int l, int r, long long x){
	node.lazyAdd += x;
	node.sum += x * (r - l);
}

void fix_lazy(Node& node, int l, int r){
	if (node.lazyAdd == 0) return;
	if (node.l != -1){
		node.l = copy_node(nodes[node.l]);
		apply(nodes[node.l], l, (l+r)/2, node.lazyAdd);
	}
	if (node.r != -1){
		node.r = copy_node(nodes[node.r]);
		apply(nodes[node.r], (l+r)/2, r, node.lazyAdd);
	}
	node.lazyAdd = 0;
}

int init(int l, int r, vector<int>& A){
	int node = new_node();
	if (r - l == 1){
		nodes[node].sum = A[l];
	} else {
		nodes[node].l = init(l, (l+r)/2, A);
		nodes[node].r = init((l+r)/2, r, A);
		nodes[node].sum = nodes[nodes[node].l].sum + nodes[nodes[node].r].sum;
	}
	return node;
}

long long get_sum(int node, int l, int r, int x, int y){
	fix_lazy(nodes[node], l, r);
	if (x <= l && r <= y) return nodes[node].sum;
	if (y <= l || r <= x) return 0;
	return get_sum(nodes[node].l, l, (l+r)/2, x, y) + 
	       get_sum(nodes[node].r, (l+r)/2, r, x, y);
}

int range_add(int node, int l, int r, int x, int y, long long val){
	fix_lazy(nodes[node], l, r);
	int n = copy_node(nodes[node]);
	if (x <= l && r <= y){
		apply(nodes[n], l, r, val);
		return n;
	}
	if (y <= l || r <= x) return node;
	nodes[n].l = range_add(nodes[n].l, l, (l+r)/2, x, y, val);
	nodes[n].r = range_add(nodes[n].r, (l+r)/2, r, x, y, val);
	nodes[n].sum = nodes[nodes[n].l].sum + nodes[nodes[n].r].sum;
	return n;
}

int range_reset(int node, int copy, int l, int r, int x, int y){
	fix_lazy(nodes[node], l, r);
	fix_lazy(nodes[copy], l, r);
	if (x <= l && r <= y) return copy_node(nodes[copy]);
	if (y <= l || r <= x) return copy_node(nodes[node]);
	int n = new_node();
	nodes[n].l = range_reset(nodes[node].l, nodes[copy].l, l, (l+r)/2, x, y);
	nodes[n].r = range_reset(nodes[node].r, nodes[copy].r, (l+r)/2, r, x, y);
	nodes[n].sum = nodes[nodes[n].l].sum + nodes[nodes[n].r].sum;
	return n;
}

vector<int> roots;
int n;

void inizia(int N, vector<int> A){
	nodes.resize(N_NODES);
	n = 1;
	while (n < N)
		n *= 2;
	A.resize(n);
	roots.push_back(init(0, n, A));
}

void incrementa(int l, int r, int x){
	int new_root = range_add(roots.back(), 0, n, l, r, x);
	roots.push_back(new_root);
}

void resetta(int l, int r, int v){
	int new_root = range_reset(roots.back(), roots[v], 0, n, l, r);
	roots.push_back(new_root);
}

long long somma(int l, int r){
	return get_sum(roots.back(), 0, n, l, r);
}

