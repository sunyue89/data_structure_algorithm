#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    
    // store as a vector string pointer to the hash buckets
    vector<string> *elems_;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
    
	//initilize string pointers in constructor
	elems_ = new vector<string>[bucket_count];

    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    bool FindHash(const string &s){

    	size_t idx = hash_func(s);

	for( auto s_hash : elems_[idx] ) {
	    if (s_hash == s){
	       	 return true;	
	    }	
    	}
	return false;

    }

    bool CheckHash(const size_t ind){

	if (ind >=0 && ind <=bucket_count -1 && elems_[ind].size() > 0){
       	     return true;	
  	}
	return false;

    }

    bool FindHash(const string &s, size_t &idx1, size_t &idx2){

    	idx1 = hash_func(s);

	for (vector<string> :: iterator it = elems_[idx1].begin(); it != elems_[idx1].end(); ++it){
	    if (*it == s){
		 idx2 = it - elems_[idx1].begin();
	       	 return true;	
	    }	
    	}
	idx2 = elems_[idx1].end()-elems_[idx1].begin();
	return false;

    }

 
    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
	return ;
    }

    void processQuery(const Query& query) {
	/*
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }*/
	if (query.type == "check") {
            // use reverse order, because we append strings to the end
	    if(CheckHash(query.ind)){ 
		    for (auto x:elems_[query.ind])
		    	std::cout << x << " ";
	    } 
            std::cout << "\n";
        } else {
	    size_t idx1, idx2;
            if (query.type == "find"){
                writeSearchResult(FindHash(query.s));
	    }else if (query.type == "add") {
		if(!FindHash(query.s,idx1,idx2)){
                    elems_[idx1].insert(elems_[idx1].begin(),query.s);
		}
            } else if (query.type == "del") {
		if(FindHash(query.s,idx1,idx2)){
		    elems_[idx1].erase(elems_[idx1].begin()+idx2);
		}
	    }
        }
	return ;
    }

    void processQueries() {
        int n;
        cin >> n;
	int i;
        for (i = 0; i < n; ++i){
	    //if(i == n-1) std::cout<<"debug1\n";
            processQuery(readQuery());
	    //if(i == n-1) std::cout<<"debug2\n";
	}
	return;
    }
/*
    ~QueryProcessor(){
	for(size_t i = 0; i<bucket_count; ++i)
	    delete elems_[i];
    }*/

};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
