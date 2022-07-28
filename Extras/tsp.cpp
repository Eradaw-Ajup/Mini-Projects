#include "bits/stdc++.h"
#define int long long
using namespace std;

int n;
vector <vector <int> > adjMatrix;

// dynamic programming
/**
 * 
 * jana padega
 * 
 *   0 1 2 3 4 5
 * 0 0 price ---->
 * 1
 * 2
 * 3
 * 4
 * 5
 * 
 * */

int cost(vector<bool> &visited, int cur_cost, int node){
    bool done = true;
    for (int i = 0; i < n; i++)
        if (visited[i] == false)
            {done = false; break;}
    if (done)
        return cur_cost + adjMatrix[node][0];

    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (visited[i] == false){
            visited[i] = true;
            ans.push_back(cost(visited,cur_cost + adjMatrix[node][i], i) );
            visited[i] = false;
        }
    int t = ans[0], i = 0;
    for (int i = 1; i < ans.size(); i++)
        if (t > ans[i])
            t = ans[i];
    return t;
}


signed main(){
    cout << "Enter number of Nodes : ";
    cin >> n;
    adjMatrix.resize(n);
    for (int i = 0; i < n; i++)
        adjMatrix[i].resize(n);
    cout << "Fill the adjacency matrix : \n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> adjMatrix[i][j];
    vector <bool> visited(n,false);
    visited[0] = 0;
    cout << cost(visited, 0, 0) << " ";

    return 0;
}