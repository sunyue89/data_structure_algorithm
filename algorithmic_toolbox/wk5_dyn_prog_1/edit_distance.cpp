#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
  //write your code here
  int n = str1.length(); //rows
  int m = str2.length(); //columns
  vector<vector<int>> Dis(n+1, vector<int> (m+1));
  for (int i=0; i<=n; ++i) Dis[i][0] = i;
  for (int j=0; j<=m; ++j) Dis[0][j] = j;
  /*debugging
  for (int i = 0; i<=n; ++i){
  	for(int j = 0; j<=m; ++j){
		cout<<Dis[i][j]<<" ";
  	}
	cout<<endl;
  }*/

  for (int j = 1; j<=m; ++j){
  	for(int i = 1; i<=n; ++i){
		int D_ist = Dis[i][j-1] + 1;
		int D_del = Dis[i-1][j] + 1;
		int D_mat = Dis[i-1][j-1];
		int D_mmat = Dis[i-1][j-1] + 1;
		if (str1.at(i-1) == str2.at(j-1)){ 
			Dis[i][j] = D_mat;
		}else{
			Dis[i][j] = std::min(std::min(D_ist, D_del), D_mmat);
		}
	}

  }
  /*debugging
  for (int i = 0; i<=n; ++i){
  	for(int j = 0; j<=m; ++j){
		cout<<Dis[i][j]<<" ";
  	}
	cout<<endl;
  }*/

  return Dis[n][m];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
