#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solver {
	string s;
	const size_t P1 = 1000000007;
	const size_t P2 = 10000009;
	const size_t mul = 9;
	vector<long long> h1;
	vector<long long> h2;
	
public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
		h1.resize(s.size()+1,0);
	        h2.resize(s.size()+1,0);	
		for(int i=1;i<=static_cast<int>(s.size());++i){
			h1[i] = ((mul*h1[i-1])%P1 + s[i-1]%P1+P1)%P1;
			h2[i] = ((mul*h2[i-1])%P2 + s[i-1]%P2+P2)%P2;
		}
	}
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
	bool ask(int a, int b, int l) {
		/*
		unordered_set<string> myset = {s.substr(a, l)};
		return ( myset.find(s.substr(b, l)) != myset.end() );*/
		long long h1_al,h1_bl,h2_al,h2_bl;
		unsigned long long x_pow1 = mulmod(mul,l,P1);
		unsigned long long x_pow2 = mulmod(mul,l,P2);

			
		h1_al = (h1[a+l]%P1 - ((x_pow1)*h1[a])%P1+P1)%P1;
		h1_bl = (h1[b+l]%P1 - ((x_pow1)*h1[b])%P1+P1)%P1;
		h2_al = (h2[a+l]%P2 - ((x_pow2)*h2[a])%P2+P2)%P2;
		h2_bl = (h2[b+l]%P2 - ((x_pow2)*h2[b])%P2+P2)%P2;
		return (h1_al == h1_bl && h2_al == h2_bl);
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
