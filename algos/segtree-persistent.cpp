#include <iostream>
#include <vector>
using namespace std;

struct Node{
	long long sum = 0;
	Node *left = NULL, *right = NULL;
	Node(){
		sum = 0;
		left = NULL;
		right = NULL;
	}
	Node(Node* l, Node* r){
		left = l;
		right = r;
		sum = left->sum + right->sum;
	}
	Node(long long s, Node *left_ = NULL, Node *right_ = NULL){
		sum = s;
		left = left_;
		right = right_;
	}
	void merge(Node* a, Node* b){
		sum = a->sum + b->sum;
	}
};


vector<Node> preAlloc(12500000);
int lastNode = 0;
inline Node* get_new_node() {
	lastNode++;
	return &preAlloc[lastNode - 1];
}

vector<Node*> nodes;
void init(Node* node, int l, int r, vector<long long>& V){
	if (r - l == 1){
		node->sum = V[l];
		return;
	}

	node->left = get_new_node();
	node->right = get_new_node();

	init(node->left, l, (l+r)/2, V);
	init(node->right, (r+l)/2, r, V);

	node->merge(node->left, node->right);
}

Node* update(Node *node, int l, int r, int k, long long x){
	if (r - l == 1){
		return new Node(x);
	}
	if ((l+r)/2 <= k){
		return new Node(node->left, update(node->right, (l+r)/2, r, k, x));
	} else {
		return new Node(update(node->left, l, (l+r)/2, k, x), node->right);
	}
}

void make_copy(int k){
	Node *new_node = new Node(nodes[k]->sum, nodes[k]->left, nodes[k]->right);
	nodes.push_back(new_node);
}

long long get_sum(Node* node, int l, int r, int x, int y){
	if (r <= x || y <= l) return 0;
	if (x <= l && r <= y) return node->sum;
	return get_sum(node->left, l, (l+r)/2, x, y) + 
		   get_sum(node->right, (l+r)/2, r, x, y);
}



int main(){

	int N, Q;
	cin >> N >> Q;

	vector<long long> V(N);
	for (long long &n : V) cin >> n;

	nodes.push_back(get_new_node());
	init(nodes[0], 0, N, V);

	long long op, a, b, x, k;
	while (Q--){
		cin >> op;
		if (op == 1){
			cin >> k >> a >> x;
			nodes[k-1] = update(nodes[k-1], 0, N, a-1, x);
		}
		if (op == 2){
			cin >> k >> a >> b;
			cout << get_sum(nodes[k-1], 0, N, a-1, b) << "\n";
		}
		if (op == 3){
			cin >> k;
			make_copy(k-1);
		}
	}


	return 0;
}