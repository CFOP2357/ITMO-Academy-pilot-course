#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

ull MOD, n, m;

struct M{
    ull a;
    ull b;
    ull c;
    ull d;
};

template<typename T> struct ST{
    int l, r;
    T acum;

    ST *left, *right;

    T none = {1,1,1,1};

    T operation(T a, T b){
        return { (a.a*b.a)%MOD, (a.b*b.b)%MOD, (a.c*b.c)%MOD, (a.d*b.d)%MOD};
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
        if(this->l >= l && this->r <= r)
            return acum;
        int m = (l+r)/2;
        return operation(left->get(l, r), right->get(l, r));
    }

    T update(int i, T v){

        if(i>=l && i<=r){
            if(l==r)
                return acum = v;
            acum = operation(left->update(i, v), right->update(i, v));
        }
        return acum;
    }

};


int main(){

    cin>>MOD>>n>>m;

    vector<M> init(n, {1,1,1,1});
    ST<M> st(0, n-1, init);

    for(int i=0; i<n; i++){
        int a, b, c, d; cin>>a>>b>>c>>d;
        st.update(i, {a%MOD, b%MOD, c%MOD, d%MOD});
    }

    cout<<"\n$\n";
    M ans = st.get(0, n);
    cout<<ans.a<<" "<<ans.b<<"\n";
    cout<<ans.c<<" "<<ans.d<<"\n";
    cout<<"$\n";

    while(m--){

        int l, r; cin>>l>>r;
        M ans = st.get(l-1, r-1);

        cout<<ans.a<<" "<<ans.b<<"\n";
        cout<<ans.c<<" "<<ans.d<<"\n";
        cout<<"\n";
    }

    return 0;
}
