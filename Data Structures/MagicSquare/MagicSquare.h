//NICOLAS LOVELACE
//CS2413
//DR CHAO ZHAO
//PROJECT 1
//JAN 31, 2022

/*
	Magic Square Generator and Validator
*/

#ifndef MagicSquare_H
#define MagicSquare_H

class MagicSquare{
	private:
		int **square;
		int size;
		int magicConst;
	public:
		MagicSquare(int);
		void readData();
		void printSquare();
		bool isMagicSquare();
		void generateMagicSquare();
};

#endif
