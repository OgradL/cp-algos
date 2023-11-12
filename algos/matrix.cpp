#include <iostream>
using namespace std;

template<typename T>
struct mat{
	int x, y;
	T **entries;
	mat(int sx, int sy, T **values = NULL){
		x = sx;
		y = sy;
		if (values == NULL){
			entries = (T**) malloc(x * sizeof(T*));
			for (int i = 0; i < x; i++){
				entries[i] = (T*) malloc(y * sizeof(T));
			}
		} else {
			entries = values;
		}
	}
	T* operator [] (int idx){
		return entries[idx];
	}
	mat operator %(long long mod){
		mat ans = mat<T>(2, 2, entries);
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				ans[i][j] %= mod;
			}
		}
		return ans;
	}
	mat operator *(mat<T>& a){
		mat ans = mat<T>(x, a.y);
		for (int i = 0; i < x; i++){
			for (int j = 0; j < a.y; j++){
				ans[i][j] = 0;
				for (int k = 0; k < a.y; k++){
					ans[i][j] += entries[i][k] * a[k][j];
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
T POW(T b, long long e, long long m, T identity){
	if (e == 0) return identity;
	T v = POW(b, e/2, m, identity);
	return (((v * v) % m) * ((e%2)?b:identity)) % m;
}

const long long MOD = 1e9 + 7;

int main(){

	long long N;
	cin >> N;


	mat mat1 = mat<long long>(2, 2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][0] = 1;
	mat1[1][1] = 0;
	mat mat2 = mat<long long>(2, 2);
	mat2[0][0] = 1;
	mat2[0][1] = 1;
	mat2[1][0] = 1;
	mat2[1][1] = 0;
	mat identity = mat<long long>(2, 2);
	identity.set(0);
	identity[0][0] = 1;
	identity[1][1] = 1;

	mat<long long> ans = mat<long long>(2, 2,
		POW<mat<long long>>(mat1, N, MOD, identity).entries
	);

	cout << ans[0][1] << "\n";

	return 0;
}