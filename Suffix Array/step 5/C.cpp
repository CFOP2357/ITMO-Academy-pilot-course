#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(){}
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
	    if(a>=b)
            return LLONG_MAX;
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(){}
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}


};

//////////////////////
RMQ<ll> rmq;
SuffixArray suffix_array;
vector<ll> suffix_array_position;
ull n;
string s;

struct Substring{
    int l;
    int r;

    bool operator <(Substring &to_compare){
        int a = suffix_array_position[l];
        int b = suffix_array_position[to_compare.l];
        if(a>b)
            swap(a, b);
        if(rmq.query(a+1, b+1) < min(r-l+1, to_compare.r-to_compare.l+1))
            return suffix_array_position[l] < suffix_array_position[to_compare.l];
        else if(rmq.query(a+1, b+1) >= min(r-l+1, to_compare.r-to_compare.l+1) && r-l != to_compare.r-to_compare.l)
            return r-l < to_compare.r-to_compare.l;
        return make_pair(l, r) < make_pair(to_compare.l, to_compare.r);
    }
};

int main(){
    cin>>s; n = s.size();
    suffix_array = SuffixArray(s);
    rmq = RMQ<ll>(suffix_array.lcp);

    suffix_array_position.assign(suffix_array.sa.size(), 0);
    for(int i=0; i<suffix_array_position.size(); i++)
        suffix_array_position[suffix_array.sa[i]] = i;

    vector<Substring> substrings;
    int m; cin>>m;
    while(m--){
        int l, r; cin>>l>>r;
        substrings.push_back({l-1, r-1});
    }

    sort(all(substrings));

    for(auto [l, r] : substrings){
        cout<<l+1<<" "<<r+1<<"\n";
    }

}
