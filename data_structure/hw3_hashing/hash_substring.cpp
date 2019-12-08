#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using std::string;
typedef unsigned long long ull;

const size_t P = 1000000009;
const size_t mul = 1;

long long hash_func(const string &s, const int size){

    long long hash =0;
    int length = std::min(static_cast<int> (s.size()-1), size-1);
    for(int i = length; i >=0; --i)
	    hash = ((hash*mul + s[i])%P + P)%P;
    return hash; 
}


long long hash_func(const string &s){

    long long hash =0;
    int length = static_cast<int> (s.size()-1);
    for(int i = length; i >=0; --i)
	    hash = ((hash*mul + s[i])%P + P)%P;
    return hash; 
}

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    /*
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    */
#if 0
    //this solutions works using a reverse rolling hasing
    long long h_p = hash_func(s);
    long long h_t = hash_func(t.substr(t.size()-s.size(),s.size()));
    long long h_mul = 1;

    for(int i =0; i<s.size(); ++i)
    	h_mul = (h_mul*mul) % P;

    for (size_t i = t.size()-s.size(); i >=0 ; --i){
        if ( h_p == h_t ){
		/*
	    size_t j =0;
	    for(j=0; j<s.size(); ++j){
	    	if(t.at(i+j) != s.at(j)) break;
	    }
	    if(j >= s.size())
            	ans.push_back(i);*/
	    if (t.substr(i, s.size()) == s) ans.push_back(i);
	}
	//rolling hashing
	if (i< t.size()-s.size())
	    h_t =(( mul*h_t + t[i] - h_mul*t[i+s.size()] )%P + P)%P;
    }
#endif

    //this solution works using a positive rolling hasing
    long long h_p = hash_func(s,s.size());
    long long h_t = hash_func(t,s.size());
    long long h_mul = 1;

    for(int i =0; i<s.size()-1; ++i)
    	h_mul = (h_mul*mul) % P;

    for (size_t i = 0; i + s.size() <= t.size(); ++i){
        if ( h_p == h_t ){
		/*
	    size_t j =0;
	    for(j=0; j<s.size(); ++j){
	    	if(t.at(i+j) != s.at(j)) break;
	    }
	    if(j >= s.size())
            	ans.push_back(i);*/
	    if (t.substr(i, s.size()) == s) ans.push_back(i);
	}
	//rolling hashing
	if ( i < t.size() - s.size()){
	    h_t =(( mul*(h_t - t[i]*h_mul) + t[i+s.size()] )%P + P)%P;
	}
    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
