//----------------------------------------------------------------------------------------
// Programmer: Nicolas Lovelace
// Program: 2
// Date: 10/17/2023
// Course: Algorithm Analysis
// Description: This program verifies a user's solution to a given crossword puzzle.
//----------------------------------------------------------------------------------------


#include <iostream>
#include <string.h>
using namespace std;

const int N = 14; //puzzle size
const int NUM_WORDS = 15; //words in columns and rows
string across[NUM_WORDS] =
 {"LOG", "TYLER", "SETH", "KARA", "NOAH", "AVONTAE", "PHI", "JARED",
 "AYUSHON", "THEY", "NICHOLAS", "MAIN", "NICOLAS", "CYRIL", "KESHAV"};
string down[NUM_WORDS] =
 {"USE", "NATHANIEL", "KINSEY", "LACE", "AXIS", "ODD", "CADE",
 "JOE", "MARK", "NATHAN", "GAS", "STEPHEN", "ERA", "GCD", "DYLAN"};


void printPuzzle(char pizzle[N][N]){ //prints the crossword puzzle
	int o = 1;
	cout << "     1  2  3  4  5  6  7  8  9 10 11 12 13 14" << endl;
	cout << "  +--------------------------------------------+" << endl;
	for(int i=0; i<N; i++){
		if(o<10) cout << " "; //adding an extra space for single digit numbers
		cout << o++ << "|  ";
		for(int j=0; j<N; j++){
			cout << pizzle[i][j] << "  ";
		}
		cout << "|" << endl;
	}
	cout << "  +--------------------------------------------+" << endl;
}

int stringMatching(string text, string pattern){ //copied the algorithm from class notes
	int end = text.size()-pattern.size();
	for(int i=0; i<end; i++){
		int j=i, k=0;
		while(text[j]==pattern[k]&&k<pattern.size()){
			j++;
			k++;
		}
		if(k==pattern.size())
			return i; //returns the position in the string the pattern was first found
	}
	return -1;
}

int lookAcross(char pizzle[N][N], string pattern){ //tries to find the pattern string on the rows
											//repeatedly calls stringMatching
											//returns row number (1...n)
	int position = -1;
	string convert[NUM_WORDS];
	
	for(int i=0; i<N; i++){
		for(int j=0; j<NUM_WORDS; j++){ //converting all entries into strings
			convert[i] += pizzle[i][j];
		}
	}
	for(int i=0; i<N; i++){
		if(stringMatching(convert[i], pattern)!=-1){
			position = i; //originally i assumed i would return what the stringMatching returns, but this is the correct solution
							//because the stringMatching would actually be the position opposite the one i needed
			break;
		}
	}
	
	return position;
}

int lookDown(char pizzle[N][N], string pattern){//tries to find the pattern string on the columns
											//repeatedly calls stringMatching
											//returns column number (1...n)
	int position = -1;
	string convert[NUM_WORDS];
	
	for(int i=0; i<N; i++){
		for(int j=0; j<NUM_WORDS; j++){ //converting all entries into strings
			convert[i] += pizzle[j][i]; //copied and pasted, except j and i are switched here!
		}
	}
	for(int i=0; i<N; i++){
		if(stringMatching(convert[i], pattern)!=-1){
			position = i;
			break;
		}
	}
	
	return position;
}

int main(){ //this method of output will show any missing words as well, indicated by a -1,
				//the puzzle matrix would just need to be replaced with a different one
	
	char puzzle[N][N] = {
	 {'U', '*', 'E', '*', 'L', 'O', 'G', '*', 'T', 'Y', 'L', 'E', 'R', '*'},
	 {'S', 'E', 'T', 'H', '*', '*', '*', 'C', '*', '*', '*', '*', '*', '*'},
	 {'E', '*', 'A', '*', 'K', 'A', 'R', 'A', '*', 'N', 'O', 'A', 'H', '*'},
	 {'*', 'N', '*', '*', 'I', '*', '*', 'D', '*', 'A', '*', '*', '*', 'G'},
	 {'*', 'A', 'V', 'O', 'N', 'T', 'A', 'E', '*', 'T', '*', 'S', '*', 'C'},
	 {'*', 'T', '*', '*', 'S', '*', 'X', '*', '*', 'H', '*', 'T', '*', 'D'},
	 {'P', 'H', 'I', '*', 'E', '*', 'I', '*', 'J', 'A', 'R', 'E', 'D', '*'},
	 {'*', 'A', '*', 'A', 'Y', 'U', 'S', 'H', 'O', 'N', '*', 'P', '*', 'D'},
	 {'*', 'N', '*', '*', '*', '*', '*', '*', 'E', '*', 'T', 'H', 'E', 'Y'},
	 {'N', 'I', 'C', 'H', 'O', 'L', 'A', 'S', '*', 'G', '*', 'E', '*', 'L'},
	 {'*', 'E', '*', '*', '*', 'A', '*', '*', 'M', 'A', 'I', 'N', '*', 'A'},
	 {'*', 'L', '*', 'N', 'I', 'C', 'O', 'L', 'A', 'S', '*', '*', 'E', 'N'},
	 {'*', '*', '*', '*', '*', 'E', 'D', '*', 'R', '*', '*', '*', 'R', '*'},
	 {'C', 'Y', 'R', 'I', 'L', '*', 'D', '*', 'K', 'E', 'S', 'H', 'A', 'V'}
	};
	
	bool accepted = true;	
	
	cout << "CROSSWORD PUZZLE" << endl;
	printPuzzle(puzzle);

	cout << "Across" << endl;
	for(int i=0; i<NUM_WORDS; i++){
		int tempA = lookAcross(puzzle, across[i]) + 1;
		if(tempA<10&&tempA>=0) cout << " "; // i tried to be more meticulous about the formatting this time!
		cout << tempA << ":" << across[i] << "\t";
		if(across[i].size()<5) //adding an extra tab if the word is short
			cout << "\t";
		if((i+1)%4==0) cout << endl; //making a row every 4 words
		if(tempA==-1) //if one of the words is not present, answer is not accepted
			accepted = false;
	}
	cout << endl;
	cout << "Down" << endl;
	for(int i=0; i<NUM_WORDS; i++){ //copy and pasted from above, but adjusted for down words
		int tempD = lookDown(puzzle, down[i]) + 1;
		if(tempD<10&&tempD>=0) cout << " ";
		cout << tempD << ":" << down[i] << "\t";
		if(down[i].size()<5)
			cout << "\t";
		if((i+1)%4==0) cout << endl;
		if(tempD==-1)
			accepted = false;
	}
	cout << endl;
	if(accepted) cout << "** Solution Accepted **" << endl;
	else cout << "**Solution Not Accepted **" << endl;
	return 0;
}
