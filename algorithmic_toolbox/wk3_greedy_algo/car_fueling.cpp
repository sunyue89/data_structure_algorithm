#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {

    int i=0;
    int cnt = 0;
    int n = stops.size();
    stops.insert(stops.begin(),0); // insert a 0 at the beginnning of vector
    stops.push_back(dist);

    while( i<= n ){
	int tmp = i ;
    	while ( (i <=n) && ( (stops[i+1] - stops[tmp]) <= tank) ){
	    i++;
	}
	if (tmp == i) return -1; //failed to progress
	if (i<=n) cnt++;
    }
    return cnt;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";
    //for (auto x:stops)
    	//cout << x << " ";

    return 0;
}
