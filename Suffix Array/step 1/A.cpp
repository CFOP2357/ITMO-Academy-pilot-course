#include <bits/stdc++.h>
using namespace std;

int main(){

    string s; cin>>s;
    s += '$';


    int n = s.size();
    vector<int> C(n);
    vector<int> P;

    {
        vector<pair<char, int>> v;

        for(int i=0; i<s.size(); i++){
            v.push_back({s[i], i});
        }
        sort(v.begin(), v.end());

        for(auto p : v)
            P.push_back(p.second);

        C[P[0]] = 1;
        for(int i=1; i<s.size(); i++){

            if(s[P[i]]==s[P[i-1]])
                C[P[i]]=C[P[i-1]];
            else
                C[P[i]]=C[P[i-1]]+1;

        }

    }

    /*for(int i=0; i<n; i++)
        cout<<s[i]<<" ";
    cout<<"\n";
    for(int i=0; i<n; i++)
        cout<<C[i]<<" ";
    cout<<"\n\n";*/

    for(long k = 1; (1<<k)<n*2; k++){

        vector<pair<pair<int, int>, int>> v;

        for(int i=0; i<n; i++){
            v.push_back({{C[i], C[(i + (1<<(k-1)))%n]}, i});
        }
        sort(v.begin(), v.end());

        P.clear();
        for(auto p : v)
            P.push_back(p.second);

        C[P[0]]=0;
        for(int i=1; i<n; i++){

            if(v[i].first == v[i-1].first)
                C[P[i]] = C[P[i-1]];
            else
                C[P[i]]=C[P[i-1]]+1;

        }

    }

    for(int p : P)
        cout<<p<<" ";
    cout<<"\n";

    return 0;
}
