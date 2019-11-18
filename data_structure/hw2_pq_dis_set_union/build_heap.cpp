#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  /*a heap based recursive swap*/
  void swap_rc (vector<int> &data, int i){
  	int largest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	if (left < data.size() && data[left] < data[largest]) largest = left; //swap index of i and left
	if (right < data.size() && data[right] < data[largest]) largest = right; //swap index of largest(i,left) and right
	if (largest != i){ //need to swap value of array per index
		swap(data[i], data[largest]);
		swaps_.push_back(make_pair(i,largest)); //record it to class element
		swap_rc(data,largest); // recursively swap all indices to create min heap 
	}
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    /*
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
    */
    for(int i = (data_.size()-1)/2; i>=0; i--) swap_rc(data_,i);
    
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
