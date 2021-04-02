#include <bits/stdc++.h>
using namespace std;

struct Tree {
	typedef int T;
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
    int n; cin>>n;

    Tree st(2*n);
    map<int, int> lastPosition;

    vector<int> ans(n);

    vector<int> a;
    for(int i=0; i<2*n; i++){
        int x; cin>>x;
        a.push_back(x);

        if(lastPosition.find(x)==lastPosition.end()){ //left
            lastPosition[x]=i;
            st.update(i, 1);
        }
        else { //right
            st.update(lastPosition[x], 0);
            ans[x-1] += st.query(lastPosition[x], i+1);
        }

    }

    reverse(a.begin(), a.end());
    lastPosition.clear();

    for(int i=0; i<2*n; i++){
        int x = a[i];

        if(lastPosition.find(x)==lastPosition.end()){ //left
            lastPosition[x]=i;
            st.update(i, 1);
        }
        else { //right
            st.update(lastPosition[x], 0);
            ans[x-1] += st.query(lastPosition[x], i+1);
        }
    }

    for(int a : ans)
        cout<<a<<" ";
    cout<<"\n";

    return 0;
}
