#include <bits/stdc++.h>
using namespace std;

typedef int ull;

template<typename T> struct ST{
    int l, r;
    T acum;

    ST *left, *right;

    T none = 0;

    T operation(T a, T b){
        return a + b;
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

    T get(int k){
        if(acum < k)
            return none;
        //cout<<this->l<<" "<<this->r<<" "<<this->acum<<"\n";
        if(l==r)
            return l+1;
        auto d  = left->get(l);
        if(d == none)
            return d;
        return right->get(l-left->acum);
    }

    T update(int i){
        if(i > r || i < l)
            return acum;

        if(i>=l && i<=r){
            if(l==r)
                return acum = !acum;
            acum = operation(left->update(i), right->update(i));
        }
        return acum;
    }

    int find(int k){
        if(l==r)
            return l;
        if(left->acum >= k)
            return left->find(k);
        return right->find(k-left->acum);
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
            int i; cin>>i;
            st.update(i);
        }
        else {
            int l; cin>>l;
            cout<<st.find(l+1)<<"\n";
        }
    }

    return 0;
}
