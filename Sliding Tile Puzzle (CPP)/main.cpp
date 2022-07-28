#include "bits/stdc++.h"
using namespace std;

#define N 4
vector <vector <int> > v;
int c = 0;
// l0 r1 u2 d3

void display(){
	cout << "---";
	for (int i = 0; i < N; i++)
		cout << "----";
	cout << "\n";
	for (int i = 0; i < N; i++){
		cout << "| ";
		for (int j = 0; j < N; j++){
			if (v[i][j] == 0)
				{cout << "  " << "  ";; continue;}
			if (v[i][j] < 10)
				cout << " ";
			cout << v[i][j] << "  ";
		}
		cout << "| \n";
	}
	cout << "---";
	for (int i = 0; i < N; i++)
		cout << "----";
	cout << "\n";
}

void init(){
	v.resize(N);
	for (int i = 0; i < N; i++){
		v[i].resize(N);
		for (int j = 0; j < N; j++)
			v[i][j] = i*N + j + 1;
	}
	v[N-1][N-1] = 0;
}


pair<int, int> find_index(){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (v[i][j] == 0) return make_pair(i,j);
	return make_pair(-1,-1);
}

void generate_puzzle(int prevoperation){
	
	if (c == 500)
		return;

	pair<int, int> pos = find_index();
	vector<int> possibilities;
	
	if (pos.second > 0)
		possibilities.push_back(0);
	if (pos.second < N-1)
		possibilities.push_back(1);
	if (pos.first > 0)
		possibilities.push_back(2);
	if (pos.first < N-1)
		possibilities.push_back(3);
	// cout <<possibilities.size() << "\n";
	int ch = rand()%(possibilities.size());
	if (possibilities[ch] == 0 and prevoperation != 1)
		swap(v[pos.first][pos.second], v[pos.first][pos.second-1]);
	else if (possibilities[ch] == 1 and prevoperation != 0)
		swap(v[pos.first][pos.second], v[pos.first][pos.second+1]);
	else if (possibilities[ch] == 2 and prevoperation != 3)
		swap(v[pos.first][pos.second], v[pos.first-1][pos.second]);
	else if (possibilities[ch] == 3 and prevoperation != 2)
		swap(v[pos.first][pos.second], v[pos.first+1][pos.second]);
	c++;
	generate_puzzle(possibilities[ch]);

}

int main(){
	
	srand(time(0));
	system("clear");
	init();
	display();

	generate_puzzle(-1);
	display();

	return 0;
}