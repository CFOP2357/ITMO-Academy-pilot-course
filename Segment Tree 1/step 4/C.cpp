#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

struct Tree {
	typedef ull T;
	static constexpr T unit = 0;
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

    int n, q; cin>>n>>q;

    vector<Tree> higherThan(41, Tree(n+1));
    vector<Tree> equalTo(41, Tree(n+1));
    Tree inv(n+1);

    for(int i=1; i<=n; i++){

        int v; cin>>v;
        equalTo[v].update(i, 1);

        for(int j=v-1; j>=1; j--)
            higherThan[j].update(i, 1);

        inv.update(i, higherThan[v].query(0, i));

    }

    cout<<inv.query(0, n+1)<<"$\n";

    while(q--){

        int t; cin>>t;
        int x, y; cin>>x>>y;

        if(t==1){

            ull ans = 0;
            ans += inv.query(x, y+1);

            for(int i=1; i<=40; i++){
                ans -= equalTo[i].query(x, y+1) * higherThan[i].query(0, x);
            }

            cout<<ans<<"\n";

        }
        else {
            for(int i=1; i<=40; i++){
                equalTo[i].update(x, 0);
                higherThan[i].update(x, 0);
            }

            equalTo[y].update(x, 1);

            for(int i=y-1; i>=1; i--)
                higherThan[i].update(x, 1);

            inv.update(x, higherThan[y].query(0, x));

        }

    }

    return 0;
}
/*
7 6
1 8 3 6 5 4 19
1 1 3
1 2 5
1 2 4
2 2 8
1 1 6
1 1 3
*/
