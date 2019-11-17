#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    /*naive solution
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }*/
    std::deque <int> win_max(w);

    for (size_t i = 0; i < A.size(); ++i) {
	
	if (i<w){
    		while (win_max.size() >0 && A[i] > A[win_max.back()]){
			win_max.pop_back();
		}
		win_max.push_back(i);
		if(i==w-1) cout << A[win_max.front()] <<" ";
	}else{
		while (win_max.size() >0 && win_max.front() <= i - w){
			win_max.pop_front();
		}
		while (win_max.size() >0 && A[i] > A[win_max.back()]){
			win_max.pop_back();
		}
		win_max.push_back(i);
		cout << A[win_max.front()] <<" ";
	}	
    
    }

    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
