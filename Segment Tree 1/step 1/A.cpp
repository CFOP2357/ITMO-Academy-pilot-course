#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

template<typename T> struct ST{
    int l, r;
    T acum;

    ST *left, *right;

    T none;

    ST(int l, int r, vector<T> &arr): l(l), r(r), none(0){
        if(l >= arr.size())
            acum = none;
        else if(l==r)
            acum = arr[r];
        else {
            int m = (l+r)/2;
            left = new ST(l, m, arr);
            right = new ST(m+1, r, arr);
            acum = left->acum + right->acum;
        }
    }


    T get(int l, int r){
        if(this->l > r || this->r < l)
            return none;
        //cout<<this->l<<" "<<this->r<<" "<<this->acum<<"\n";
        if(this->l >= l && this->r <= r)
            return acum;
        int m = (l+r)/2;
        return left->get(l, r) + right->get(l, r);
    }

    T update(int i, int v){

        if(i > r || i < l)
            return acum;

        if(i>=l && i<=r){
            if(l==r)
                return acum = v;
            acum = left->update(i, v) + right->update(i, v);
        }
        return acum;
    }

};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin>>n>>m;
    vector<ull> a;

    for(int i = 0; i<n; i++){
        ull z; cin>>z;
        a.push_back(z);
    }

    ST<ull> st(0, a.size()-1, a);

    //cout<<"#\n";
    //cout<<st.get(0, 2)<<"\n";

    while(m--){
        int q; cin>>q;
        if(q==1){ //update
            int i, v; cin>>i>>v;
            st.update(i, v);
        }
        else {
            int l, r; cin>>l>>r;
            cout<<st.get(l, r-1)<<"\n";
        }
    }

    return 0;
}
