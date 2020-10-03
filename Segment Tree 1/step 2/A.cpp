#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

struct seg{
    ull pre, suf, sum, max_s;
    seg(ull pre, ull suf, ull max_s, ull sum) : pre(pre), suf(suf), sum(sum), max_s(max_s){
        this->pre = max(this->pre, (ull)0);
        this->suf = max(this->suf, (ull)0);
        this->max_s = max(this->max_s, (ull)0);
    }
    seg() : pre(0), suf(0), sum(0), max_s(0){}
};

template<typename T = seg> struct ST{
    int l, r;
    T acum;

    ST *left, *right;

    T none = seg();

    T operation(T a, T b){
        seg ans;
        ans.pre = max(max(a.pre, max(a.sum+b.pre, a.sum)), (ull)0);
        ans.suf = max(max(b.suf, max(b.sum+a.suf, b.sum)), (ull)0);
        ans.max_s = max(max(a.suf + b.pre, max(a.max_s, b.max_s)), (ull)0);
        ans.sum = a.sum + b.sum;

        return ans;
    }

    ST(int l, int r, vector<T> &arr): l(l), r(r){
        if(l >= arr.size())
            acum = none;
        else if(l==r)
            acum = arr[r];
        else {
            int m = (l+r)/2;
            left = new ST(l, m, arr);
            right = new ST(m+1, r, arr);
            acum = operation(left->acum,  right->acum);
        }
    }

    T get(int l, int r){
        if(this->l > r || this->r < l)
            return none;
        //cout<<this->l<<" "<<this->r<<" "<<this->acum<<"\n";
        if(this->l >= l && this->r <= r)
            return acum;
        int m = (l+r)/2;
        return operation(left->get(l, r), right->get(l, r));
    }

    T update(int i, T v){
        if(i > r || i < l)
            return acum;

        if(i>=l && i<=r){
            if(l==r)
                return acum = v;
            acum = operation(left->update(i, v), right->update(i, v));
        }
        return acum;
    }

};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin>>n>>m;
    vector<seg> a;

    for(int i = 0; i<n; i++){
        ull z; cin>>z;
        a.push_back(seg(z, z, z, z));
    }

    ST<seg> st(0, a.size()-1, a);

    //cout<<"#\n";
    //cout<<st.get(0, 2)<<"\n";

    cout<<st.get(0, a.size()-1).max_s<<"\n";
    while(m--){
            int i, v; cin>>i>>v;
            st.update(i, seg(v, v, v, v));
            cout<<st.get(0, a.size()-1).max_s<<"\n";
    }

    return 0;
}

