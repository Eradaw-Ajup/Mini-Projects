#include "bits/stdc++.h"
using namespace std;
#define int long long int

int n, m, min_colors; 
vector <vector<int>> v;

// my graph coloring algorithm
// first i am finding the minimum number of colors required to color the graph


// algorithm to give graphs a color ;
// backtracking  -- start for loop and call the function ;
// condition color not equal to previous color node ;

// function : graph and color and caller

// function which prints all the possible coloring given the number of colors avialble
void back_tracking(int index, vector<int> color, int nc){
    if (index == n){
        for (int i = 0; i < n; i++)
            cout << color[i] << " ";
        cout << "\n";
        return;
    }

    vector<int> hash(nc);
    for (int i = 0; i < v[index].size(); i++){
        if (color[v[index][i]] != -1)
            hash[color[v[index][i]]] = 1;
    }
    bool f = 0;
    for (int i = 0; i < nc; i++)
        if (hash[i] == 0){
            color[index] = i;
            f = 1;
            back_tracking(index+1, color, nc);
        }
}


bool back_tracking_2(int index, vector<int> color, int nc){
    if (index == n)
        return true;
    vector <int> hash(nc);
    for (int i = 0; i < v[index].size(); i++)
        if (color[v[index][i]] != -1)
            hash[color[v[index][i]]] = 1;
    bool flag = 0;
    for (int i = 0; i < nc; i++)
        if (hash[i] == 0){
            color[index] = i;
            flag = flag or back_tracking_2(index+1, color, nc);
        }
    return flag;
}


void bfs_approach(){
    vector <int> color(n, 0);
    vector <bool> visited(n,0);
    queue <int> q;
    q.push(0);
    visited[0] = 1;

    while (!q.empty()){
        int cur = q.front();
        q.pop();
        for (int i = 0; i < v[cur].size(); i++){
            if (color[v[cur][i]] == color[cur])
                color[v[cur][i]]++;
            if (visited[v[cur][i]] == 0)
                visited[v[cur][i]] = 1, q.push(v[cur][i]);
        }
    }
    for (int i = 0; i < n; i++)
        cout << color[i] << " ";
}

signed main(){
#ifndef  ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> n >> m;
    v.clear();
    v.resize(n);
    for (int i = 0; i < m; i++){
        int j,k; cin >> j >> k;
        j--;k--;
        v[j].push_back(k);
        v[k].push_back(j);
    }
    vector<int> color;
    color.clear();
    color.resize(n,-1);


    back_tracking(0, color, 2);

    color.clear();
    color.resize(n,-1);

    int l = 1, r = n; 

    while (l < r){
        int m = l + (r-l) / 2;
        if (back_tracking_2(0,color, m))
            r = m ;
        else
            l = m + 1;
    }
    cout << l << "\n";
    bfs_approach();

    return 0;
}