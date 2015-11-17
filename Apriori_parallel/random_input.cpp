#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	int r;
	cout << "Enter number of transactions : ";
	cin >> t;
	cout << "Enter number of candidate items of size 1 : ";
	cin >> r;
	int s;
	cout << "Enter minimum support count : ";
	cin >> s;
	freopen("input.txt","w",stdout);
	cout << s << "\n";
	vector<int> v;
	for(int i=0;i<r;i++) v.push_back(i+1);
	for(int i=0;i<t;i++){
		random_shuffle(v.begin(),v.end());
		vector<int> u;
		int k = rand() % r + 1;
		for(int j=0;j<k;j++) cout << v[j] << ((j!=(k-1))?' ':'\n');
	}
	return 0;
}