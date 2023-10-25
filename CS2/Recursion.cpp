//Nicolas Lovelace CS2 Fall 2021
#include <iostream>
using namespace std;

int count11(int arr[], int index, int len){
	if (index!=len){
		if (arr[index]==11){
			return 1+count11(arr, index+1, len);
		}else{
			return count11(arr, index+1, len);
		}
	}else{
		return 0;
	}
}

int array220(int arr[], int index, int len){
	if (index==len-1){
		//stopping case
		return 0;
	}else{
		//recursive case
		if (arr[index]*10==arr[index+1]){
			return 1;
		}else{
			return array220(arr, index+1, len);
		}	
	}
}
bool groupSum(int arr[], int index, int len, int sum){
	if (index==len-1){
		 if (sum==0){
		 	return true;
		 }else{
		 	if (sum==arr[index]){
		 		return true;
			 }else{
			 	return false;
			 }
		 }
	}else{
		return groupSum(arr, index+1, len, sum-arr[index])||groupSum(arr, index+1,len,sum);
	}
}
int main(){
	int myArray[]={11, 3, 5, 8, 11, 9, 11, 11, 89};
	cout<<"We have "<<count11(myArray, 0, 9)<< " elevens"<<endl;
	cout<<array220(myArray, 0, 9)<<endl;
	cout<<groupSum(myArray,0,9, 33)<<endl;
}
