#include "bits/stdc++.h"
#define int long long
using namespace std;

// fly me to the moon and let me play among the stars
// let me see what spring is like on Jupiter and Mars



// no duplicates
// vertex edge from previous vertex 
// last vertex edge to first one


int n, m;
vector<vector<int>> v;

void back_tracking(int index, vector<int> visited){
    // base condition


    bool f = false , f1 = false;
    for (int i = 0; i < v[index].size(); i++){
        if (visited[v[index][i]] == -1){
            visited[index] = v[index][i];
            back_tracking(v[index][i],visited);
            visited[index] = -1;
            f = true;
        }
        if (v[index][i] == 0)
            f1 = true;
    }
    if (!f){
        bool f2 = false;
        visited[index] = 0;
        for (int i = 0; i < n; i++)
            if (visited[i] == -1){f2 = true;break;}
        if (!f2 and f1){
            
            for (int i = 0; i < n; i++)
                cout << visited[i]+1 << " ";
            cout << "\n";
        }

    }
}


signed main(){
#ifndef  ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m;
    v.clear();v.resize(n);
    for (int i = 0; i < m; i++){
        int j, k; cin >> j >> k;
        j--;k--;
        v[j].push_back(k);
        v[k].push_back(j);
    }
    vector <int> visited(n,-1);
    back_tracking(0, visited);
    return 0;
}

