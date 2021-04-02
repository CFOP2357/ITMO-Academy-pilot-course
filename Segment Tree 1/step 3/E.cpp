#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

struct Tree {
	typedef ull T;
	static constexpr T unit =  0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie();

    int n, m; cin>>n>>m;

    Tree st(n+1);
    while(m--){
        int t; cin>>t;

        if(t==1){
            ull l, r, v; cin>>l>>r>>v;
            st.update(l, st.query(l, l+1) + v);
            st.update(r, st.query(r, r+1) - v);
        }
        else{
            int i; cin>>i;
            cout<<st.query(0, i+1)<<"\n";
        }

    }

    return 0;
}
