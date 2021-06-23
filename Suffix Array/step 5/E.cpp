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

int main(){
    ll n, m; cin>>n>>m;
    string s;
    for(int i=0; i<n; i++){
        int z; cin>>z;
        s.push_back((char)(z+'a'));
    }

    SuffixArray suffix_array(s);

    vector<ll> sa = suffix_array.sa;
    vector<ll> LCP = suffix_array.lcp;

    /*for(auto k:sa)
        cout<<k<<" ";
    cout<<"\n";
    for(auto k:LCP)
        cout<<k<<" ";
    cout<<"\n";*/

    stack<pii> last; //lcp, frecuency
    stack<ll> position;
    last.push({-1, 0}); position.push(0);
    ll max_product = 0;
    ll length = 0;
    ll ans_position = 0;

    for(int i=0; i<n+1; i++){
        ll lcp = LCP[i];
        ll frecuency = 0;
        ll last_position = 0;
        while(last.size() and lcp <= last.top().first){
            ll product = (last.top().second+frecuency)*last.top().first;
            if(product > max_product){
                max_product = product;
                length = last.top().first;
                ans_position = position.top();
            }
            frecuency += last.top().second;
            last_position = position.top();
            last.pop();
            position.pop();
        }
        if(frecuency){
            last.push({lcp, frecuency});
            position.push(last_position);
        }
        last.push({n-sa[i],1});
        position.push(sa[i]);
    }

    {
        ll frecuency = 0;
        while(last.size()){
            ll product = (last.top().second+frecuency)*last.top().first;
            if(product > max_product){
                max_product = product;
                length = last.top().first;
                ans_position = position.top();
            }
            frecuency += last.top().second;
            last.pop();
            position.pop();
        }
    }

    cout<<max_product<<"\n";
    cout<<length<<"\n";

    for(int i=0; i<length; i++){
        cout<<(int)(s[i+ans_position]-'a')<<" ";
    }
    cout<<"\n";

    return 0;
}
