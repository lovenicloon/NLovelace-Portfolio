//Nicolas Lovelace CS2 Fall 2021
#include <iostream>
using namespace std;

void hanoiTower(int n, char start, char dest, char temp){
	if (n!=0){
		hanoiTower(n-1, start, temp, dest);
		cout<<"Move "<<n<<" from "<<start<<" to "<<dest<<endl;
		hanoiTower(n-1, temp, dest, start);
	}
}

int main(){
	hanoiTower(4, 'A', 'C', 'B');
	return 0;
}
