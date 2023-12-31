#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template<typename T = long long>
struct mat{
	int x, y;
	T **entries;
	mat(int sx, int sy, T** values = NULL){
		x = sx;
		y = sy;
		entries = (T**) malloc(x * sizeof(T*));
		for (int i = 0; i < x; i++){
			entries[i] = (T*) malloc(y * sizeof(T));
		}
		if (values != NULL){
			for (int i = 0; i < x; i++){
				for (int j = 0; j < y; j++){
					entries[i][j] = values[i][j];
				}
			}
		}
	}
	mat(int sx, int sy, initializer_list<vector<long long>> values){
		x = sx;
		y = sy;
		entries = (T**) malloc(x * sizeof(T*));
		vector<vector<long long>> tmp;
		tmp.insert(tmp.begin(), values);
		for (int i = 0; i < x; i++){
			entries[i] = (T*) malloc(y * sizeof(T));
		}
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				entries[i][j] = tmp[i][j];
			}
		}
	}
	T* operator [] (int idx){
		return entries[idx];
	}
	mat operator %(long long mod){
		mat ans = mat<T>(x, y, entries);
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				ans[i][j] %= mod;
			}
		}
		return ans;
	}
	mat operator *(mat<T>& a){
		assert(x == a.y);
		mat ans = mat<T>(a.x, y);
		for (int i = 0; i < y; i++){
			for (int j = 0; j < a.x; j++){
				ans[j][i] = 0;
				for (int k = 0; k < x; k++){
					ans[j][i] += entries[k][i] * a[j][k];
				}
			}
		}
		return ans;
	}
	void set(T v){
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				entries[i][j] = v;
			}
		}
	}
};


template<typename T>
T POW(T b, long long e, long long m){
	if (e == 1) return b;
	T v = POW(b, e/2, m);
	v = (v * v) % m;
	if (e&1){
		v = (v * b) % m;
	}
	return v;
}

const long long MOD = 1e9 + 7;

int main(){

	long long N;
	cin >> N;

	mat X = mat<long long>(6, 6, {{0, 1, 0, 0, 0, 0},
								  {0, 0, 1, 0, 0, 0},
								  {0, 0, 0, 1, 0, 0},
								  {0, 0, 0, 0, 1, 0},
								  {0, 0, 0, 0, 0, 1},
								  {1, 1, 1, 1, 1, 1}});

	mat<long long> ans = POW<mat<long long>>(X, N, MOD);

	cout << ans[5][5] << "\n";

	return 0;
}