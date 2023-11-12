#include <iostream>
#include <vector>
using namespace std;

struct Treap{
	int key, pri, size;
	Treap *left, *right;

	Treap() {}
	Treap(int key, Treap *L = NULL, Treap *R = NULL) : Treap(key, rand(), L, R) {}

	Treap(int key, int pri, Treap *L = NULL, Treap *R = NULL) : key(key), pri(pri), left(L), right(R) {
		size = 1;
		if (L) size += L->size;
		if (R) size += R->size;
	}

	void heapify(Treap* root){
		Treap* m = root;
		if (root->left && root->left->pri > m->pri) m = root->left;
		if (root->right && root->right->pri > m->pri) m = root->right;
		if (m == root) return;
		swap(root->pri, m->pri);
		heapify(m);
	}

	void linear_init(Treap* root, int l, int r){
		if (r - l < 1) return;
		int m = (l+r)/2;
		root = new Treap(m);
		linear_init(root->left, l, m);
		linear_init(root->right, m+1, r);
		root->key = m;
		heapify(root);
	}

	Treap* merge(Treap *L, Treap *R){
		if (R == NULL) return L;
		if (L == NULL) return R;
		
		if (L->pri > R->pri){
			return new Treap(L->key, L->pri, L->left, merge(L->right, R));
		} else {
			return new Treap(R->key, R->pri, merge(L, R->left), R->right);
		}
	}

	pair<Treap*, Treap*> split(Treap* T, int key){
		if (T == NULL) return {NULL, NULL};
		if (T->key < key){
			auto [RL, RR] = split(T->right, key);
			Treap* L = new Treap(T->key, T->pri, T->left, RL);
			return {L, RR};
		} else {
			auto [LL, LR] = split(T->left, key);
			Treap* R = new Treap(T->key, T->pri, LR, T->right);
			return {LL, R};
		}
	}

	int count(Treap* T, int key){
		if (T == NULL) return 0;
		if (T->key < key) return count(T->right, key);
		else if (T->key > key) return count(T->left, key);
		else return 1;
	}

	Treap* insert(Treap *T, int key){
		auto [L, R] = split(T, key);
		return merge(L, merge(new Treap(key), R));
	}

	Treap* erase(Treap* T, int key){
		if (T == NULL) return NULL;
		auto [L, R] = split(T, key);
		auto [RL, RR] = split(R, key+1);
		return merge(L, RR);
	}

	int get_size(Treap* T){
		if (T == NULL) return 0;
		return T->size;
	}

	int get(Treap* T, int i){
		if (T == NULL) return -1;
		if (get_size(T->left) == i) return T->key;
		if (get_size(T->left) > i) return get(T->left, i);
		if (get_size(T->left) < i) return get(T->right, i - get_size(T->left) - 1);
	}
};