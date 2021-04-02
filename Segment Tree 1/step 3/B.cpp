
#include <bits/stdc++.h>
using namespace std;

template<typename T> struct ST{
    int l, r;
    T acum;

    ST *left, *right;

    T none = 0;

    T operation(T a, T b){
        return  a+b;
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

    int find(int x){
        if(l == r)
            return l;
        if(right->acum >= x)
            return right->find(x);
        return left->find(x - right->acum);
    }

};

int main(){
    int n; cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++)
        cin>>a[i];

    reverse(a.begin(), a.end());

    vector<int> ans;

    vector<int> initST(n, 1);
    ST<int> st(0, n-1, initST);

    for(int k : a){
        ans.push_back(st.find(k+1));
        st.update(ans.back(), 0);
    }

    reverse(ans.begin(), ans.end());

    for(int k : ans)
        cout<<k+1<<" ";
    cout<<"\n";

    return 0;
}
