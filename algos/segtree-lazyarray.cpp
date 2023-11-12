#include <iostream>
#include <vector>
#include <limits>
using namespace std;

template<typename T = long long>
struct Node{
	const T MAX = numeric_limits<T>::max();
	const T MIN = numeric_limits<T>::min();

	T sum;
	T mi;
	T lazySet;
	T lazyAdd;
	
	Node(){
		sum = 0;
		mi = MAX;
		lazySet = MIN;
		lazyAdd = 0;
	}
	void merge(const Node &l, const Node &r){
		mi = min(l.mi, r.mi);
		sum = l.sum + r.sum;
	}
};

template<typename T = long long>
struct ST{
	
	const T MAX = numeric_limits<T>::max();
	const T MIN = numeric_limits<T>::min();

	int n, real_size;
	vector<Node<T>> nodes;
	
	ST(vector<T> data){
		
		n = data.size();
		
		real_size = 1;
		while (real_size < n)
			real_size *= 2;
		
		nodes.assign(2 * real_size, Node());
		
		build(1, 0, real_size, data);
	}
	
	ST(){
		// cool
	}
	
	void fixLazy(int u, int l, int r){
		
		if (nodes[u].lazyAdd == 0 && nodes[u].lazySet == MIN) return;
		
		if (nodes[u].lazySet != MIN) {
			nodes[u].mi = nodes[u].lazySet;
			nodes[u].sum = nodes[u].lazySet * (r - l);
			
			if (u < real_size){
				nodes[u * 2].lazySet = nodes[u].lazySet;
				nodes[u * 2].lazyAdd = 0;
				
				nodes[u*2+1].lazySet = nodes[u].lazySet;
				nodes[u*2+1].lazyAdd = 0;
			}
			nodes[u].lazySet = MIN;
			nodes[u].lazyAdd = 0;
			return;
		}
		if (nodes[u].lazyAdd != 0){
			nodes[u].mi += nodes[u].lazyAdd;
			nodes[u].sum += nodes[u].lazyAdd * (r - l);
			
			if (u < real_size){
				nodes[u * 2].lazyAdd += nodes[u].lazyAdd;
				
				nodes[u*2+1].lazyAdd += nodes[u].lazyAdd;
			}
			nodes[u].lazyAdd = 0;
		}
	}
	
	void build(int u, int l, int r, vector<T>& data){
		if (r - l == 1){
			if (l < data.size()){
				nodes[u].mi = data[l];
				nodes[u].sum = data[l];
			} else {
				nodes[u].mi = MAX;
				nodes[u].sum = 0;
			}
		} else {
			build(2*u, l, (l+r)/2, data);
			build(2*u+1, (l+r)/2, r, data);
			nodes[u].merge(nodes[2*u], nodes[2*u+1]);
		}
	}
	
	void update(int pos, T x){
		
		int u = real_size + pos;
		nodes[u].mi = x;
		nodes[u].sum = x;
		
		while(u > 1){
			
			u /= 2;
			nodes[u].merge(nodes[2*u], nodes[2*u+1]);
			
		}
	}
		
	Node<T> at(int pos){
		int u = real_size + pos;
		return nodes[u];
	}


	T getmin(int u, int l, int r, int x, int y){
		fixLazy(u, l, r);
		if (r <= x || l >= y) return MAX;
		if (x <= l && r <= y) return nodes[u].mi;
		return min(
			getmin(2*u, l, (l+r)/2, x, y),
			getmin(2*u+1, (l+r)/2, r, x, y)
		);
	}
	
	T getmin(int x, int y){
		return getmin(1, 0, real_size, x, y);
	}
	

	T getsum(int u, int l, int r, int x, int y){
		fixLazy(u, l, r);
		if (r <= x || l >= y) return 0;
		if (x <= l && r <= y) return nodes[u].sum;
		
		return getsum(2*u, l, (l+r)/2, x, y) + getsum(2*u+1, (l+r)/2, r, x, y);
	}
	
	T getsum(int x, int y){
		return getsum(1, 0, real_size, x, y);
	}
	
	
	void setrange(int u, int l, int r, int x, int y, T num){
		fixLazy(u, l, r);
		if (x >= r || y <= l) return;
		if (l >= x && r <= y) {
			nodes[u].lazySet = num;
			nodes[u].lazyAdd = 0;
			fixLazy(u, l, r);
			return;
		}
		setrange(2*u, l, (l+r)/2, x, y, num);
		setrange(2*u+1, (l+r)/2, r, x, y, num);
		nodes[u].merge(nodes[2*u], nodes[2*u+1]);
	}
	
	void setrange(int x, int y, T num){
		setrange(1, 0, real_size, x, y, num);
	}
	
	
	void addrange(int u, int l, int r, int x, int y, T num){
		fixLazy(u, l, r);
		if (x >= r || y <= l) return;
		if (l >= x && r <= y) {
			nodes[u].lazyAdd += num;
			fixLazy(u, l, r);
			return;
		}
		addrange(2*u, l, (l+r)/2, x, y, num);
		addrange(2*u+1, (l+r)/2, r, x, y, num);
		nodes[u].merge(nodes[2*u], nodes[2*u+1]);
	}
	
	void addrange(int x, int y, T num){
		addrange(1, 0, real_size, x, y, num);
	}
	
	
	int lowerbound(int u, int l, int r, int x, int y, T num){
		fixLazy(u, l, r);
		if (y <= l || x >= r || nodes[u].mi > num) return -1;
		if (r - l <= 1){
			return l;
		}
		
		int le = lowerbound(u*2, l, (l+r)/2, x, y, num);
		if (le != -1) return le;
		
		int ri = lowerbound(u*2+1, (l+r)/2, r, x, y, num);
		return ri;
	}
	
	int lowerbound(int x, int y, T num){
		return lowerbound(1, 0, real_size, x, y, num);
	}
	
	
	void print(){
		cout << "tree: \n";
		int ji = 1;
		int l = 2;
		for (int i = 1; i < nodes.size(); i++){
			cout << nodes[i].mi << " ";
			ji++;
			if (ji == l){
				l *= 2;
				cout << "\n";
			}
		}
	}
	
};
