#include "bits/stdc++.h"
using namespace std;

// printing -> GRAY CODE

int n; 
vector<string> v;

void gray_code(string s){
    if (v.size() == pow(2,n))
        return ;
    for (int i = 0; i < v.size(); i++){
        if (s == v[i])
            return;
    }
    //cout << s << " " ;
    v.push_back(s);

    for (int i = n-1; i >= 0; i--){
        (s[i] == '0') ? s[i] = '1' : s[i] = '0';
        //cout << s << "|";
        gray_code(s);
        (s[i] == '0') ? s[i] = '1' : s[i] = '0';
        //cout << s << "|+";
        //cout << "\n";
    }
    return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cin >> n;

    // gray code
    string s = "";
    for (int i = 0; i < n; i++)
        s += '0';
    
    gray_code(s);

    for (int i = 0 ; i < v.size(); i++){
        cout << v[i] << " \n";
    }
    return 0;
}
