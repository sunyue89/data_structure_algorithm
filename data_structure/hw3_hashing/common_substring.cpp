#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;



struct Answer {
	size_t i, j, len;
};

class kCheck {

public:
	size_t P1 = 1000000007;
	size_t P2 = 1000004249;
	size_t mul = 5;
	size_t mul_2 = 9;
	long long h_roll = 0;
	unsigned long long h_mul = 1;
	size_t k;
	unordered_map <long long, size_t> s1_map;
	unordered_map <long long, size_t> s2_map;
	set <pair<size_t,size_t>> Com_Idx;

      	kCheck(size_t x) : k(x) {}
      	~kCheck(){}

#if 0 
//None Rolling Index Solution didn't meet time performance
bool k_com_str(const string &s, const string &t, size_t k, Answer &idx){

    unordered_map <string, size_t> s_map;

    for (size_t i =0; i + k <= s.size(); ++i){
    	s_map[s.substr(i,k)] = i;
    }    
    for (size_t i =0; i + k <= t.size(); ++i){
	unordered_map <string, size_t> :: iterator itr = s_map.find(t.substr(i,k));

    	if( itr != s_map.end()){
	       idx = {itr->second,i,k};	
	       return true;
	}
    }
    return false;
}
#endif

	unsigned long long mulmod(int a, int b, int c){
		long long x =1, y = a%c;
		while(b>0){
			if(b%2==1){
			       	x = (x*y)%c;
			}
			y=(y*y)%c;
			b /= 2;
		}
		return x;
	}
	

     bool k_com_str(const string &s, const string &t, Answer &idx){
   	// Function 1 Mapping
    	h_mul = mulmod(mul,k,P1);

    	//initiliaze the hash
    	h_roll = 0;

    	for (size_t i = 0; i < s.size(); ++i){
		h_roll = (( mul*h_roll + s[i] )%P1 + P1)%P1;
	
		//rolling hashing
		if ( i >= k){
		    h_roll = (h_roll - (h_mul*s[i-k])%P1 + P1)%P1;

		}
		if (i+1 >= k){
		    s1_map[h_roll] = i+1-k;
		}
    	}
    
    	h_roll = 0;

    	for (size_t i =0; i < t.size(); ++i){

		h_roll = (( mul*h_roll + t[i] )%P1 + P1)%P1;

		if ( i >= k){
	    		h_roll =(h_roll - (h_mul*t[i-k])%P1 + P1)%P1;

		}
		if (i+1 >=k){
			unordered_map <long long, size_t> :: iterator itr = s1_map.find(h_roll);

	   		if( itr != s1_map.end()){
				Com_Idx.insert(make_pair(itr->second,i+1-k)); //map first idx to sec idx
	    		}
		}
	
    	}
	if (k==0) return true;
    	if (Com_Idx.size() == 0) return false;
	
	// Function 2 Mapping
    	h_mul = mulmod(mul_2,k,P2);

    	//initiliaze the hash
    	h_roll = 0;

    	for (size_t i = 0; i < s.size(); ++i){
		h_roll = (( mul_2*h_roll + s[i] )%P2 + P2)%P2;
	
		//rolling hashing
		if ( i >= k){
		    h_roll = (h_roll - (h_mul*s[i-k])%P2 + P2)%P2;

		}
		if (i+1 >= k){
		    s2_map[h_roll] = i+1-k;
		}
    	}
    
    	h_roll = 0;

    	for (size_t i =0; i < t.size(); ++i){

		h_roll = (( mul_2*h_roll + t[i] )%P2 + P2)%P2;

		if ( i >= k){
	    		h_roll =(h_roll - (h_mul*t[i-k])%P2 + P2)%P2;

		}
		if (i+1 >=k){
			unordered_map <long long, size_t> :: iterator itr = s2_map.find(h_roll);

	   		if( itr != s2_map.end()){
				//cout<<itr->second<<" "<<i+1-k<<endl;
				set <pair<size_t,size_t>> :: iterator itr2 = Com_Idx.find(make_pair(itr->second,i+1-k)); //find the pair's match
				if (itr2 != Com_Idx.end()){
					idx = {itr->second,i+1-k,k};//since there is a match between two hashes, this must be a valid answer
					return true;//record the answer and return true
				}
	    		}
		}
	
    	}
	
	return false;
    }

};


Answer solve(const string &s, const string &t) {
	
	Answer ans = {0, 0, 0};
	
	size_t low = 0;
	size_t high = std::min(s.size(),t.size());
	while (low <= high){
		size_t k = (low + high)/2;
		//cout<<low<<" "<<high<<" "<<k<<endl;
		kCheck check1(k);
		if(check1.k_com_str(s,t,ans) ){
			low = k+1;
		}else{
			high = std::max (int (k)-1,0);
		}
	}
	/* Default DP Solution
	for (size_t i = 0; i < s.size(); i++)
		for (size_t j = 0; j < t.size(); j++)
			for (size_t len = 0; i + len <= s.size() && j + len <= t.size(); len++)
				if (len > ans.len && s.substr(i, len) == t.substr(j, len))
					ans = {i, j, len};
	*/
	return ans;
	
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
