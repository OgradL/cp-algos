

template<long long mod = 998244353>
struct modint{
	long long v;
	explicit operator int() const { return v; }
 
	// constructors
	modint():v(0) {}
	template <typename T> modint(T _v) :v((int)(_v % mod)) { v = (v + mod) % mod; }

	void exgcd(int a, int b, int& x, int& y) {
		if(1ll * a * b == 0) { x = 1, y = 0; return; }
		exgcd(b, a % b, x, y); int tmp = y; y = x - a / b * y; x = tmp; 
	}
 
	template <typename T> modint& operator=(T a) { v = (a + mod) % mod; return *this; }
	modint operator-() { return modint((-v + mod) % mod); } 
	modint& operator+=(modint o) { v = (v + o.v) % mod; return *this; }
	modint& operator-=(modint o) { v = (v - o.v + mod) % mod; return *this; }
	modint inv() { int x, y; exgcd(v, mod, x, y); return modint((x + mod) % mod); }
	modint& operator*=(modint o) { v = (long long)v * o.v % mod; return *this; }
	modint& operator/=(modint o) { v = (long long)v * o.inv().v % mod; return *this; }
 
	modint operator+(modint o) { return modint((v + o.v) % mod); } 
	modint operator-(modint o) { return modint((v - o.v + mod) % mod); } 
	modint operator*(modint o) { return modint((long long)v * o.v % mod); } 
	modint operator/(modint o) { return modint((long long)v * o.inv().v % mod); }
 
	template <typename T> modint& operator+=(T o) { v = (v + o) % mod; return *this; }
	template <typename T> modint& operator-=(T o) { v = (v - o + mod) % mod; return *this; }
	template <typename T> modint& operator*=(T o) { v = (long long)v * o % mod; return *this; }
	template <typename T> modint& operator/=(T o) { v = (long long)v * modint(o).inv().v % mod; return *this; }
 
	template <typename T> modint operator+(T o) { return modint((v + o) % mod); } 
	template <typename T> modint operator-(T o) { return modint((v - o + mod) % mod); } 
	template <typename T> modint operator*(T o) { return modint((long long)v * o % mod); } 
	template <typename T> modint operator/(T o) { return modint((long long)v * modint(o).inv().v % mod); }
 
	modint& operator++() { v = (v + 1) % mod; return *this; }
	modint& operator--() { v = (v - 1 + mod) % mod; return *this; }
 
	modint operator++(int) { modint old = *this; operator++(); return old; }
	modint operator--(int) { modint old = *this; operator--(); return old; }
 
	bool operator==(modint o) { return v == o.v; }
	bool operator!=(modint o) { return v != o.v; }
 
	template <typename T> bool operator==(T o) { return v == o; }
	template <typename T> bool operator!=(T o) { return v != o; }
	
	template <typename T> friend modint operator+(T o, modint x) { return x + o; }
	template <typename T> friend modint operator-(T o, modint x) { return x * (-1) + o; }
	template <typename T> friend modint operator*(T o, modint x) { return x * o; }
	template <typename T> friend modint operator/(T o, modint x) { return x.inv() * o; }
 
	template <typename T> modint& operator%=(T o) { v %= o; return *this; }
	template <typename T> friend T operator%(T o, modint x) { return o % x.v; }
	template <typename T> friend modint operator%(modint x, T o) { return modint(x.v % o); }
	
	friend std::ostream& operator<<(std::ostream& os, modint const& a) { return os << a.v; }
	friend istream& operator>>(istream& is, modint& a) { int x; is >> x; a = modint(x); return is; }
};

const long long MOD = 998244353;

using mint = modint<MOD>;
