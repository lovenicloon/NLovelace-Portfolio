//Nicolas Lovelace
//SYS PROG PROJECT 2
//10/03/22
//Convert user-entered IPv4 address to network byte order in binary format and decimal value

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

string conVert(string orig){ //converts IP into the binary string
  string bin = " 00000000 00000000 00000000 00000000"; //setting up binary string, leaving space in front to keep the 9 pattern
  int nums[4]; //storing the 4 numbers in the IP
  int o = 0; //tracking length of number
  int n = 0; //tracking which number we're on
  for(int i=0; i<orig.length(); i++){ //extracting the decimal numbers
    if(orig[i]=='.'||i==orig.length()-1){
      nums[n] = stoi(orig.substr(i-o, i));
      n++;
      o=0;
    }
    else
      o++;
  }
  for(int i=3; i>=0; i--){ //loading the numbers into the binary string, starting from the back
    int a = (i+1)*9-1; //setting the position to the start of each binary section
    int b = nums[i];
    while(b>0){ //converting
      if(b%2==1)
        bin[a] = '1';
      else
        bin[a] = '0';
      b/=2;
      a--;
    }
  }
  return bin;
}

double toDec(string bin){
  double dec = 0; //storing the result
  int p = 0; //storing binary position/exponent
  int i = bin.length()-1; //starting at the back of the binary string
  for(; i>=0; i--){
    if(bin[i]=='1'){
      dec+=pow(2,p); //adding the value of the position if indicated
    }
    if(bin[i]!=' ') p++; //don't want to count the spaces as binary positions
  }
  return dec;
}

int main(){ //running the program/output
  char x;
  string IP;
  string bi;
  do{
    cout << "Enter an IP v4 address: " << endl;
    cin >> IP;
    bi = conVert(IP);
    cout << endl;
    cout << "IP: " << IP << endl;
    cout << "Binary:" << bi << endl;
    cout << "Decimal: " << setprecision(0) << fixed << toDec(bi) << endl;
    
    cout << "Run again? y/n" << endl;
    cin >> x;
  }while(x=='y');
  cout << "Goodbye." << endl;
}
