//NICOLAS LOVELACE
//CS2413
//DR CHAO ZHAO
//HW 4
//MAR 1, 2022

/*

	Converts an infix expression into a postfix expression and evaluates it

*/

#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

template <typename T> //template class for stacks
class Stack{
	private:
		T* stacc;
	public:
		int size;
		Stack(){
			stacc = new T[20]; //i didnt care to make it dynamic for this project
			size = 0;
		}
		T pop(){
			if(size==0){
				cout << "Stack is empty" << endl;
        return 0; //returning 0 seemed pretty universal
			}
			return stacc[--size];
		}
		T top(){
			if(size==0) return 0;
			return stacc[size-1];
		}
		void append(T x){
			if(size==99){
				cout << "Stack is full" << endl;
				return;
			}
			stacc[size++] = x;
		}
};

string conVert(string orig){
	string post = "";
	Stack<char> stak;
	for(int i=0; i<orig.size(); i++){
		if(isdigit(orig[i])){ //checks for digits first
			post+=orig[i];
			while(isdigit(orig[i+1])){ //checking for double+ digit numbers
				post+=orig[++i];
			}
			post+=" "; //adding a space to identify the end of a number
		}
		else if(orig[i] == '+' || orig[i] == '-'){
			if(stak.top() == '+'||stak.top() == '-'){ //priorities
				post+=stak.pop();
				stak.append(orig[i]);
			}
			else if(stak.top() == '*'||stak.top() == '/'){ //high priority
				while(stak.top() == '*'||stak.top() == '/')
					post+=stak.pop();
				stak.append(orig[i]);
			}
			else if(stak.size == 0 || stak.top() == '(' || stak.top() == '[' || stak.top() == '{')
				stak.append(orig[i]); //catch all, basically
		}
		else if(orig[i] == '*' || orig[i] == '/'){
			stak.append(orig[i]);
		}
		else if(orig[i]=='(' || orig[i]=='[' || orig[i]=='{'){
			stak.append(orig[i]);
		}
		else if(orig[i]==')' || orig[i]==']' || orig[i]=='}'){
			while(stak.top()!='(' && stak.top()!='[' && stak.top()!='{'){ //pop until the open bracket is found
				post+=stak.pop();
			}
			stak.pop(); //pop one last time
		}
		else
			continue;
	}
  while(stak.size>0){
		post+=stak.pop(); //check if anything is in the stack and pop it all
	}
	return post;
}

double eVal(string post){
	double ans = 0;
	Stack<double> stak;
	string temp = "";
	double temp2 = 0;
	for(int i=0; i<post.size(); i++){
		if(isdigit(post[i])){
			temp+=post[i];
			while(post[i+1]!=' '){
				temp+=post[++i];
			}
    	  	i++; //this addition seemed to be key in keeping the program working
			stringstream bee(temp);
			bee >> temp2;
			stak.append(temp2);
			temp ="";
		}
		else{
			double a = 0, b = 0;
			a = stak.pop();
			b = stak.pop();
			switch(post[i]){
				case '+': 
					stak.append(a+b);
					break;
				case '-': 
					stak.append(b-a); //i had to switch these to keep the signs right
					break;
				case '*': 
					stak.append(a*b);
					break;
				case '/': 
					stak.append(b/a); //had to switch these as well
					break;
			}	
		}
	}
  return stak.top();
}

int main(){
	string infix, postfix;
	int bruh;
	do{
		cout << "Enter infix: ";
		cin >> infix;
		postfix = conVert(infix);
		cout << postfix << " equals " << eVal(postfix) << endl;
		cout << "Enter 0 to stop. 1 to continue." << endl;
		cin >> bruh;
	}while(bruh == 1);
	
	return 0;
}
