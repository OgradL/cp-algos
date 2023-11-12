#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_map>
using namespace std;

#define _ << " " <<
#define nl << "\n"
#define fast_io std::cin.tie(0);std::cin.sync_with_stdio(false);std::cout.tie(0);std::cout.sync_with_stdio(false);
#define read_from_file(file) freopen((file)?file:"input.txt", "r", stdin);
#define write_to_file(file) freopen((file)?file:"output.txt", "w", stdout);
#define init_rand srand(time(NULL));
#define read_vector(V) for (auto &v : V) cin >> v;
#define all(v) v.begin(), v.end()
#define ll long long
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(v) ((int)(v.size()))
#define pairi pair<int, int>
#define yes(b) ((b)?("yes"):("no"))
#define no(b) yes(!(b))
#define stop(ans) (cout << ans << "\n", return;)

void dbg_out() { cout << "\n" << flush; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){
	cout << " " << H; dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) (cout << "#" << __LINE__ << ": (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__))
#else
#define dbg(...)
#endif

template<class T>
void operator>>(istream& a, vector<T>& v){
	for (auto &x : v) cin >> x;
}

template<class T1, class T2>
void operator>>(istream& a, pair<T1, T2>& v){
	cin >> v.first >> v.second;
}

template<class T>
void operator<<(ostream& a, vector<T>& v){
	for (auto &x : v) { cout << x; cout << ' '; }
	cout << "\n";
}

template<class T1, class T2>
void operator<<(ostream& a, pair<T1, T2>& v){
	cout << "{" << v.first << " " << v.second << "}";
}

long long fast_pow(long long b, long long e, long long m){
	if (e == 0) return 1;
	long long v = fast_pow(b, e/2, m);
	return (((v * v) % m) * ((e%2) ? b : 1)) % m;
}

long long inv(long long i, long long m) {
	return fast_pow(i%m, m-2, m);
	return i <= 1 ? i : m - (long long)(m / i) * inv(m % i, m) % m;
}

long long bit(long long x, long long b){
	return (x & (1LL << b)) > 0;
}

long long gcd(long long a, long long b){
	return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b){
	return a / gcd(a, b) * b;
}

long long MOD = 1e9 + 7;

void solve(){

	int ans = 42;

	cout << ans nl;
}


int main(){
	init_rand
	fast_io
	int T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}