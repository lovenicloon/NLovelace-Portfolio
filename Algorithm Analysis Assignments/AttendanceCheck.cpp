//----------------------------------------------------------------------------------------
// Programmer: Nicolas Lovelace
// Program: 1
// Date: 9/19/2023
// Course: Algorithm Analysis
// Description: This program creates the attendance report for a course using the original
// roster and the attendance log for two sessions.
//----------------------------------------------------------------------------------------


#include <iostream>
#include <string.h>
using namespace std;

int MAXSIZE = 20;

int main(){
	
	//Input lists
	string roster[MAXSIZE] = {"Bray", "Clark", "Compton", "Davis", "Long", "Moore", "Rios", "Tahah", "Thomas", "Wright"};
	string day1[MAXSIZE] = {"Rios", "Compton", "Thomas", "Clark", "Davis", "Estep", "Bray", "Long"};
	string day2[MAXSIZE] = {"Davis", "Long", "Ridge", "Bray", "Thomas", "Moore", "Clark", "Estep", "Underwood"};

	int attended[MAXSIZE]; //attendance count
	int late[MAXSIZE]; //late enrollment markers
	
	//Initializing attendance and late enrollment markers
	for(int i=0; i<MAXSIZE; i++){
		attended[i] = 0;
		late[i] = 0;
	}
	
	//I would potentially just put this in another loop if there were more days and use a 2D array for attendance lists
	
	for(int i=0; i<MAXSIZE; i++){ //sifting through day1
		if(day1[i].compare("")==0) //cutting off the loop if the day 1 attendane sheet is finished
			break;
		int j;
		for(j=0; j<MAXSIZE; j++){ //sifting through roster
			if(day1[i].compare(roster[j])==0){ //if day1 is in roster
				attended[j]+=1; //attended that day
				break;
			}
			if(roster[j].compare("")==0){ //if the j loop has made it to the end of the roster
				roster[j] = day1[i]; //add the student's name to the roster
				attended[j]+=1; //attended that day
				late[j] = 1; //add late enrollment marker
				break;
			}
		}
	}
	
	//Copy of day1 loop to do day2
	
	for(int i=0; i<MAXSIZE; i++){ //sifting through day2
		if(day2[i].compare("")==0) //cutting off the loop if the day2 attendance sheet is finished
			break;
		int j;
		for(j=0; j<MAXSIZE; j++){ //sifting through roster
			if(day2[i].compare(roster[j])==0){ //if day1 is in roster
				attended[j]+=1; //attended that day
				break;
			}
			if(roster[j].compare("")==0){ //if the j loop has made it to the end of the roster
				roster[j] = day2[i]; //add the student's name to the roster
				attended[j]+=1; //attended that day
				late[j] = 1; //add late enrollment marker
				break;
			}
		}
	}

	//Outputting results
	cout << "Name\t\tAttended" << endl;
	cout << "-------------------------------------------" << endl;
	for(int i=0; i<MAXSIZE; i++){
		if(roster[i].compare("")==0) break; //cutting off the loop if the roster is finished
		cout << roster[i] << "\t\t" << attended[i];
		if(late[i]==1)
			cout << " enrolled late";
		cout << endl;
	}
	
	return 0;
}
