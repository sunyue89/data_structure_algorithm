#include <iostream>
#include <vector>

using std::vector;
using std::max;

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  int n = a.size();
  int m = b.size();
  vector<vector<int>> score(n+1,vector<int> (m+1,0));
  for (int i=1;i<=n;++i){
  	for(int j=1;j<=m;++j){
		if(a[i-1] == b[j-1]){ 
			score[i][j] = score[i-1][j-1] + 1;
		}
		else{
			score[i][j] = std::max(score[i-1][j],score[i][j-1]);
		}
	}
  }
  return score[n][m];
}

int max_6d(int a, int b, int c, int d, int e, int f){
	return max(max(max(max(max(a,b),c),d),e),f);
}

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here - old method
  //int score1 = std::min(std::min(lcs2(a,b),lcs2(a,c)), lcs2(b,c));
  //write your code here
  //  return score1;

  int n = a.size();
  int m = b.size();
  int l = c.size();
  vector<vector<vector<int>>> score(n+1, vector<vector<int>>(m+1,vector<int>(l+1)));
  for (int i=1;i<=n;++i){
  	for(int j=1;j<=m;++j){
		for(int k=1;k<=l;++k){
			if( a[i-1] == b[j-1] && a[i-1]==c[k-1] && b[j-1]==c[k-1]){ 
				score[i][j][k] = score[i-1][j-1][k-1] + 1;
			}
			else{
				score[i][j][k] = max_6d(score[i-1][j][k-1],score[i][j-1][k-1],score[i][j][k-1],score[i-1][j][k],score[i][j-1][k],score[i-1][j-1][k]);
			}
		}
	}
  }
  return score[n][m][l];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
