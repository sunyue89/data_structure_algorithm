#include <iostream>
#include <vector>

using namespace std;

class hash_comp{

	string text,pattern;
	const size_t P1 = 1000000007;
	const size_t P2 = 1000009;
	const size_t mul = 3;

	vector<long> h1;
	vector<long> h2;
	vector<long> h3;
	vector<long> h4;
	vector<unsigned long> x_pow1;
	vector<unsigned long> x_pow2;

public:
	hash_comp(string s, string t) : text(s), pattern(t){

		h1.resize(text.size()+1,0);
		h2.resize(text.size()+1,0);
		h3.resize(pattern.size()+1,0);
		h4.resize(pattern.size()+1,0);
		x_pow1.resize(pattern.size()+1,1);
		x_pow2.resize(pattern.size()+1,1);
		

		for(int i=1;i<=static_cast<int>(text.size());++i){
			h1[i] = ((mul*h1[i-1])%P1 + (text[i-1]-'a')%P1+P1)%P1;
			h2[i] = ((mul*h2[i-1])%P2 + (text[i-1]-'a')%P2+P2)%P2;
		}
		
		for(int i=1;i<=static_cast<int>(pattern.size());++i){
			h3[i] = ((mul*h3[i-1])%P1 + (pattern[i-1]-'a')%P1+P1)%P1;
			h4[i] = ((mul*h4[i-1])%P2 + (pattern[i-1]-'a')%P2+P2)%P2;
			x_pow1[i] = mulmod(mul,i,P1);
			x_pow2[i] = mulmod(mul,i,P2);
		}

	}

	unsigned long mulmod(int a, int b, int c){
		long x =1, y = a%c;
		while(b>0){
			if(b%2==1){
				x = (x*y)%c;
			}
			y=(y*y)%c;
			b /= 2;
		}
		return x;
	}


	bool substr_comp(const int a, const int b, const int l){
	
		long h1_al,h3_bl,h2_al,h4_bl;
		//unsigned long x_pow1 = mulmod(mul,l,P1);
		//unsigned long x_pow2 = mulmod(mul,l,P2);

		h1_al = (h1[a+l]%P1 - ((x_pow1[l])*h1[a])%P1+P1)%P1;
		h3_bl = (h3[b+l]%P1 - ((x_pow1[l])*h3[b])%P1+P1)%P1;
		h2_al = (h2[a+l]%P2 - ((x_pow2[l])*h2[a])%P2+P2)%P2;
		h4_bl = (h4[b+l]%P2 - ((x_pow2[l])*h4[b])%P2+P2)%P2;

		return (h1_al == h3_bl && h2_al == h4_bl);

	}

};

vector<int> solve(int k, const string &text, const string &pattern) {
	//construct the class, precompute all hashes
	hash_comp C(text,pattern);
	vector<int> pos;

	for(int i=0; i<=text.size()-pattern.size(); ++i){
		int lgth = 0;
		int lo = 0;

		for( int j =0; j<=k; ++j){

			lo = std::max(lo,j);
			int hi = pattern.size();

			//Each binary search shall push lgth towards the largest mismatch indx 	
			int tmp = lo;
			while(lo<=hi){
				lgth = (lo+hi)/2;
				//cout<<lo<<" "<<lgth<<" "<<hi<<endl;
				if(C.substr_comp(tmp+i,tmp,lgth-tmp)){
					lo = lgth+1;
				}else{
					hi = lgth-1;
				}
			
			}

			//cout<<lo<<" "<<lgth<<" "<<hi<<" "<<pattern.size()<<endl;
			if(lo>pattern.size()){
			        //cout<<"tst1"<<endl;	
				pos.push_back(i);
				break;
			}
		}
		//cout<<"tst2"<<endl;
	}

	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
