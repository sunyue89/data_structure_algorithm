#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;

const long long INF = 10000000000000;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

long long get_maximum_value(const string &exp) {
  //write your code here
  int n = (exp.length()-1)/2+1;
  //debug
  //std::cout<<n<<std::endl;
  vector<vector<long long>> m(n,vector<long long>(n,0));
  vector<vector<long long>> M(n,vector<long long>(n,0));
  for(int i=0;i<n;++i){
  	m[i][i] = exp.at(2*i) - '0';
	M[i][i] = exp.at(2*i) - '0';
  }
  /*debug
  for(int i=0;i<n;++i){
	  for(int j =0; j<n; ++j){
		  std::cout<<M[i][j]<<' ';
	  }
	  std::cout<<std::endl;
  }*/
  //m[n-1][n-1]
  for(int s=1;s<=n-1;++s){
  	for(int i=0;i<=n-s-1;++i){
		int j = i+s;
		long long mino = INF;
		long long maxo = -INF;
		for(int k=i;k<j;++k){
			long long a = eval(M[i][k], M[k+1][j], exp.at(2*k+1));
			//std::cout<<a<<std::endl;
			long long b = eval(M[i][k], m[k+1][j], exp.at(2*k+1));
			//std::cout<<b<<std::endl;
			long long c = eval(m[i][k], M[k+1][j], exp.at(2*k+1));
			//std::cout<<c<<std::endl;
			long long d = eval(m[i][k], m[k+1][j], exp.at(2*k+1));
			//std::cout<<d<<std::endl;
			
			mino = min(min(min(min(mino,a),b),c),d);
			maxo = max(max(max(max(maxo,a),b),c),d);
		}

		m[i][j] = mino;
		M[i][j] = maxo;
	}
  }
  /*debug
    for(int i=0;i<n;++i){
	  for(int j =0; j<n; ++j){
		  std::cout<<M[i][j]<<' ';
	  }
	  std::cout<<std::endl;
    }
    for(int i=0;i<n;++i){
	  for(int j =0; j<n; ++j){
		  std::cout<<m[i][j]<<' ';
	  }
	  std::cout<<std::endl;
    }*/
  
  return M[0][n-1];
}

int main() {
  string s;
  std::cin >> s;
  long long a = get_maximum_value(s);
  std::cout << a << '\n';
}
