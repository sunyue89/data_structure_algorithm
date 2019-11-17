#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    int pos = 0;

    std::stack <Bracket> opening_brackets_stack;
    int position;
    for (position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
	    Bracket bot(next,position);
	    opening_brackets_stack.push(bot);
        }

        if (next == ')' || next == ']' || next == '}') {
		if (opening_brackets_stack.empty()){
		       if (pos==0)	pos = position+1;
		}else{
			Bracket top = opening_brackets_stack.top();
			if (!top.Matchc(next)&&pos==0) pos = position+1;
			opening_brackets_stack.pop();
		}
            // Process closing bracket, write your code here
        }

    }
    if(!opening_brackets_stack.empty()&&pos==0) pos=opening_brackets_stack.top().position+1;


    // Printing answer, write your code here
    if(pos>0){
    	cout<<pos<<endl;
    }else{
    	cout<<"Success"<<endl;
    }

    return 0;
}
