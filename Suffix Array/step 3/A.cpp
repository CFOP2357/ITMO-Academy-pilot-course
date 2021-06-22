#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

struct SuffixArray {
	vi sa, lcp;
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

bool is_as_substr(vector<ll> &sa, string &s, string &to_compare, int l, int r){ //[l, r)
    if(l+1>=r)
        return s.substr(sa[l], to_compare.size()) == to_compare;

    int m = (l+r)/2;
    string middle_string = s.substr(sa[m], to_compare.size());

    if(middle_string <= to_compare)
        return is_as_substr(sa, s, to_compare, m, r);
    else
        return is_as_substr(sa, s, to_compare, l, m);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    string t; cin>>t;

    SuffixArray sa(t);

    int n; cin>>n;
    while(n--){
        string s; cin>>s;
        if(is_as_substr(sa.sa, t, s, 1, sa.sa.size()))
            cout<<"Yes\n";
        else
            cout<<"No\n";
    }
    return 0;
}
