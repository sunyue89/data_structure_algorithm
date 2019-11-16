#include <iostream>
#include <vector>

using namespace std;

const int INF = 4294967295/2;

vector <int> Coins = {1,3,4};

int get_change(int m) {
  vector <int> MinNumCoins(m+1);
  MinNumCoins[0] = 0;
  int NumCoins=0;
  for (int i =1; i<=m; i++){
  	MinNumCoins[i] = INF;
	//cout<<MinNumCoins[i]<<endl;
	for (auto coin : Coins){
		if (i>=coin){
			NumCoins = MinNumCoins[i-coin] + 1;
			//cout<<NumCoins<<endl;
			if (NumCoins < MinNumCoins[i]){	
				MinNumCoins[i] = NumCoins;
				//cout<<MinNumCoins[i]<<endl;
			}
		}

	}	  
  }

  return MinNumCoins[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
