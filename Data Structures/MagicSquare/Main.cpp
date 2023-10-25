//NICOLAS LOVELACE
//CS2413
//DR CHAO ZHAO
//PROJECT 1
//JAN 31, 2022

/*
	Magic Square Generator and Validator
*/

#include <iostream>
#include "MagicSquare.cpp"
using namespace std;

int main(){

	int one, two;
	
	do{
		cout << "Magic Square Program\nEnter the size of the square: ";
		cin >> two;
		
		while(two%2==0||two<3||two>9){
			cout << "\nPlease enter 3, 5, 7, or 9: ";
			cin >> two;
		}
		
		MagicSquare mymagic(two);
		mymagic.readData();
		if(mymagic.isMagicSquare()){
			cout << "Congratulations! It is a magic square." << endl;
		}
		else{
			cout << "It is not a magic square. We will generate one for you." << endl;
			mymagic.generateMagicSquare(); //rewrites the square to make it a magic square
		}
		
		cout << "Enter 1 to do it again. Enter any other number to quit: ";
		cin >> one;
	}while(one==1);
	
	return 0;
}
