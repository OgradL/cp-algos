#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
	vector<int> fen;
	int n;

	FenwickTree(int N) {
		n = N;
		fen.assign(N, 0);
	}

	FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
		for (int i = 0; i < a.size(); i++)
			add(i, a[i]);
	}

	int sum(int r) {
		int ret = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1){
			ret += fen[r];
			ret = ret;
		}
		return ret;
	}

	int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	void add(int idx, int delta) {
		for (; idx < n; idx = idx | (idx + 1)){
			fen[idx] += delta;
			fen[idx] = fen[idx];
		}
	}

	void clear(){
		fen.assign(n, 0);
	}
};