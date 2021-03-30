#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

template<typename T> struct ST{
    int l, r;
    T acum;

    ST *left, *right;

    T none = INT_MAX;

    T operation(T a, T b){
        return max(a, b);
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

    int find(T x){

        if(acum < x)
            return -1;

        if(l==r)
            return l;

        if(left->acum >= x)
            return left->find(x);
        return right->find(x);
    }

};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    ull n, m; cin>>n>>m;
    vector<ull> init;
    for(int i=0; i<n; i++){
        ull z; cin>>z;
        init.push_back(z);
    }
    ST<ull> st(0, n-1, init);

    while(m--){
        int q; cin>>q;

        if(q==1){
            ull i, v; cin>>i>>v;
            st.update(i, v);
        }
        else {
            ull x; cin>>x;
            cout<<st.find(x)<<"\n";
        }
    }

}
