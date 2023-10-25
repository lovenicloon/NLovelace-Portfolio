//NICOLAS LOVELACE
//CS2413
//DR CHAO ZHAO
//PROJECT 1
//JAN 31, 2022

/*
	Magic Square Generator and Validator
*/

#include <iostream>
#include "MagicSquare.h"
using namespace std;

MagicSquare::MagicSquare(int x){
	square = new int*[x]; //allocate space for outer array
	
	for(int i=0; i<x; i++){
		square[i] = new int[x]; //allocate space for inner arrays
		for(int j=0; j<x; j++){
			square[i][j] = 0; //initializing all values to 0
		}
	}
	size = x; //set size
	magicConst = x*(x*x+1)/2; //magic square constant
}

void MagicSquare::readData(){
	cout << "Enter data row by row:" << endl;
	
	for(int i=0; i<size; i++){
		cout << "Row " << i+1 << ": ";
		for(int j=0; j<size; j++){
			cin >> square[i][j]; //takes in each member
		}
	}
}

void MagicSquare::printSquare(){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			cout << square[i][j] << " "; //normal space
			if(square[i][j]<10) cout << " "; //adding extra space for small numbers
		}
		cout << endl; //new row
	}
}

bool MagicSquare::isMagicSquare(){
	int sum;
	//sum each row
	for(int i=0; i++; i<size){
		sum = 0;
		for(int j=0; j++; j<size){
			sum+=square[i][j];
		}
		if(sum!=magicConst) return false;
	}
	
	//sum each column
	for(int i=0; i++; i<size){
		sum = 0;
		for(int j=0; j++; j<size){
			sum+=square[j][i];
		}
		if(sum!=magicConst) return false;
	}
	
	//sum diagonal
	sum = 0;
	for(int i=0; i<size; i++){
		sum+=square[i][i];
	}
	if(sum!=magicConst) return false;
	
	//sum diagonal 2
	sum = 0;
	for(int i = size-1, j=0; i>=0; j++, i--){
		sum+=square[i][j];
	}
	if(sum!=magicConst) return false;
	
	return true;
}

void MagicSquare::generateMagicSquare(){
	cout << "Previous square:" << endl;
	printSquare();
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			square[i][j] = 0; //clearing the square
		}
	}
	
	int num = 1;
	int i = 0; //starting pos for i
	int j = size/2; //starting pos for j
	while(num<=size*size){
		square[i][j] = num; //we start each loop with the right positions
		i--;
		j++;
		if(i==-1) i=size-1; //loop back if necessary
		if(j==size) j=0; //loop back if necessary
		if(square[i][j]!=0){ //if space is NOT free, we undo what we did and go to the correct position
			i++;
			if(i==size) i=0; //loop back if necessary
			i++;
			if(i==size) i=0; //this is here twice because adding 2 from size-1 isn't supposed to take us to 0, but rather 1
			j--;
			if(j==-1) j=size-1; //loop back if necessary
		}
		//if space was free, start the loop again with the positions previously obtained
		num++;
	}
	cout << "Generated square:" << endl;
	printSquare();
}
