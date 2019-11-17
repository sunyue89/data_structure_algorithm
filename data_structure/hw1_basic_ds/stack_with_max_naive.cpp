#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    vector<int> aux_stack; //creat a aux stack that only tracks incoming element that is max 

  public:

    void Push(int value) {
       

	if(stack.size()==0){
		aux_stack.push_back(value);
	}
	else{
		if(value >= aux_stack.back()) aux_stack.push_back(value);
	}

	stack.push_back(value);
	
    }

    void Pop() {
        assert(stack.size());
	int ele = stack.back();
        stack.pop_back();

	assert(aux_stack.size());
	if (ele == aux_stack.back()) aux_stack.pop_back();
    }

    int Max() const {
	return aux_stack.back();
	/*
        assert(stack.size());
        return *max_element(stack.begin(), stack.end());*/
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
