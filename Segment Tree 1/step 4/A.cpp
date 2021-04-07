#include <iostream>
#include <vector>
using namespace std;

struct Tree {
	typedef int T;
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

    int n; cin>>n;
    Tree evenPositive(n);
    Tree oddPositive(n);

    for(int i=0; i<n; i++){
        int z; cin>>z;

        if(i%2){
            oddPositive.update(i, z);
            evenPositive.update(i, -z);
        }
        else {
            oddPositive.update(i, -z);
            evenPositive.update(i, z);
        }
    }

    int m; cin>>m;

    while(m--){
        int t; cin>>t;

        if(!t){
            int i, z; cin>>i>>z; i--;

            if(i%2){
                oddPositive.update(i, z);
                evenPositive.update(i, -z);
            }
            else {
                oddPositive.update(i, -z);
                evenPositive.update(i, z);
            }
        }
        else {
            int l, r; cin>>l>>r;
            l--;

            if(l%2)
                cout<<oddPositive.query(l, r)<<"\n";
            else
                cout<<evenPositive.query(l, r)<<"\n";

        }

    }


    return 0;
}
