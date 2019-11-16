#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using std::vector;

const int INF = 4294967295/2;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> true_optimal_sequence(int n, int *number){
  vector<vector<int>> sequence(n+1);
  sequence[0] = {0};
  sequence[1] = {1};
/*
  sequence[2] = sequence[1];
	for(auto seq : sequence[2]) cout<<seq<<endl;*/
  
  vector<int> MinNumOp(n+1);
  MinNumOp[0] = 0;
  MinNumOp[1] = 0;
  int NumOp = 0;
  int i = 2;
  int seq_tmp = 1;

    while (i <= n){
    	MinNumOp[i] = INF;

	if(i>1){
		NumOp = MinNumOp[i-1] + 1;
		if (NumOp < MinNumOp[i]){
			MinNumOp[i] = NumOp;
			seq_tmp = i-1;
		}
	}
	if(i%2==0){
		NumOp = MinNumOp[i/2] + 1;
		if (NumOp < MinNumOp[i]){
			MinNumOp[i] = NumOp;
			seq_tmp = i/2;
		}
	}
	if(i%3==0){
		NumOp = MinNumOp[i/3] + 1;
		if (NumOp < MinNumOp[i]){
			MinNumOp[i] = NumOp;
			seq_tmp = i/3;
		}
	}
	sequence[i] = sequence[seq_tmp];
	sequence[i].push_back(i);
	/*
	for(auto seq : sequence[i]) cout<<seq<<' ';
	cout<<endl;
	cout<<i<<endl;
	cout<<seq_tmp<<endl;
	//cout<<MinNumOp[i]<<endl;*/
    	i++;
    }
    *number = MinNumOp[n];
    return sequence[n];
}

int main() {
  int n,m;
  std::cin >> n;  

/*Test  
  vector<vector<int>> sequence(n);

  sequence[0] = {0};
  sequence[1] = {1};

  sequence[2] = sequence[1];
	for(auto seq : sequence[2]) std::cout<<seq<<endl;*/

	
  vector<int> sequence = true_optimal_sequence(n,&m);
  std::cout << sequence.size() - 1 << std::endl;
 // std::cout << m << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
