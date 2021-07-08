#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


char buf[450 << 20] alignas(16);
size_t buf_ind = sizeof buf;

template<class T> struct small {
	typedef T value_type;
	small() {}
	template<class U> small(const U&) {}
	T* allocate(size_t n) {
		buf_ind -= n * sizeof(T);
		buf_ind &= 0 - alignof(T);
		return (T*)(buf + buf_ind);
	}
	void deallocate(T*, size_t) {}
};

const ll inf = LLONG_MAX;
template<typename T> struct ST {
	ST *l = 0, *r = 0;
	T lo, hi, mset = inf, madd = 0, val = 0;

	T add_operation(const T &a, const T &b){
        return max(a, b);
    }
    T query_operation(const T &a, const T &b){
        return max(a, b);
    }

	ST(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	ST(vi& v, int lo, int hi) : lo(lo), hi(hi) { //[lo, ho)
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new ST(v, lo, mid); r = new ST(v, mid, hi);
			val = query_operation(l->val, r->val);
		}
		else val = v[lo];
	}

	T query(int L, int R) { //[L, R)
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return query_operation(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, T x) { //[L,R)
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = query_operation(l->val, r->val);
		}
	}
	void add(int L, int R, T x) { //[L, R)
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset = add_operation(mset, x);
			else madd = add_operation(madd, x);
			val = add_operation(val, x);
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = query_operation(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new ST(lo, mid); r = new ST(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin>>n>>m;
    vector<int> init(n+1, 0);
    ST<ll> st(init, 0, init.size());

    while(m--){
        int t; cin>>t;
        if(t==1){
            ll l, r, v; cin>>l>>r>>v;
            st.set(l, r, v);
        }
        else {
            int i; cin>>i;
            ll ans = st.query(i, i+1);
            cout<<ans<<"\n";
        }
    }
    return 0;
}

