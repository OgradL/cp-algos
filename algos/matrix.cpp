#include <iostream>
#include <vector>
#include <array>
#include <assert.h>
using namespace std;

template<typename T = long long, int sx = 2, int sy = 2>
struct mat{
	array<array<T, sy>, sx> entries;
	mat(){
		for (int i = 0; i < sx; i++){
			for (int j = 0; j < sy; j++){
				entries[i][j] = 0;
			}
		}
	}
	mat(array<array<T, sy>, sx>& tmp){
		for (int i = 0; i < sx; i++){
			for (int j = 0; j < sy; j++){
				entries[i][j] = tmp[i][j];
			}
		}
	}
	mat(initializer_list<vector<long long>> values){
		auto it = values.begin();
		for (int i = 0; i < sx; i++){
			auto it2 = it++->begin();
			for (int j = 0; j < sy; j++){
				entries[i][j] = *it2++;
			}
		}
	}
	mat operator=(mat tmp) {
		for (int i = 0; i < sx; i++){
			for (int j = 0; j < sy; j++){
				entries[i][j] = tmp[i][j];
			}
		}
		return *this;
	}
	array<T, sy>& operator [] (int idx){
		return entries[idx];
	}
	mat operator %(long long mod){
		mat<T, sx, sy> ans;
		for (int i = 0; i < sx; i++){
			for (int j = 0; j < sy; j++){
				ans[i][j] = entries[i][j] % mod;
			}
		}
		return ans;
	}
	void operator %=(long long mod){
		for (int i = 0; i < sx; i++){
			for (int j = 0; j < sy; j++){
				entries[i][j] %= mod;
			}
		}
	}
	template<int smx, int smy>
	mat<T, smx, sy> operator *(mat<T, smx, smy>& a) const {
		assert(sx == smy);
		mat<T, smx, sy> ans;
		for (int i = 0; i < sy; i++){
			for (int j = 0; j < smx; j++){
				for (int k = 0; k < sx; k++){
					ans[j][i] += entries[k][i] * a[j][k];
				}
			}
		}
		return ans;
	}
	template<int smx, int smy>
	void operator *=(mat<T, smx, smy>& a) const {
		assert(sx == smy);
		mat<T, smx, sy> ans;
		for (int i = 0; i < sy; i++){
			for (int j = 0; j < smx; j++){
				for (int k = 0; k < sx; k++){
					ans[j][i] += entries[k][i] * a[j][k];
				}
			}
		}
		entries = ans.entries;
	}
	void set(T v){
		for (int i = 0; i < sx; i++){
			for (int j = 0; j < sy; j++){
				entries[i][j] = v;
			}
		}
	}
};

template<typename T>
T POW(T b, long long e, long long m, T identity){
	T ret = identity;
	while (e){
		if (e & 1){
			ret = ret * b;
		}
		b = b * b;
		e /= 2;
	}
	return ret;
}

const long long MOD = 1e9 + 7;

using matrix = mat<long long, 2, 2>;

int main(){

	long long N;
	cin >> N;

	mat X = matrix({{0, 1, 0, 0, 0, 0},
					{0, 0, 1, 0, 0, 0},
					{0, 0, 0, 1, 0, 0},
					{0, 0, 0, 0, 1, 0},
					{0, 0, 0, 0, 0, 1},
					{1, 1, 1, 1, 1, 1}});

	matrix identity = matrix({{1, 0, 0, 0, 0, 0},
							  {0, 1, 0, 0, 0, 0},
							  {0, 0, 1, 0, 0, 0},
							  {0, 0, 0, 1, 0, 0},
							  {0, 0, 0, 0, 1, 0},
							  {0, 0, 0, 0, 0, 1}});

	mat<long long> ans = POW<matrix>(X, N, MOD, identity);

	cout << ans[5][5] << "\n";

	return 0;
}