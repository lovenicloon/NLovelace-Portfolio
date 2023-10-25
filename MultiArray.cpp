//Nicolas Lovelace CS2 Fall 2021
#include <iostream>
#include <cstdlib>
using namespace std;

class DynamicArray{
	private:
		int *start;
		int size;
		int capacity;	
	public:
		DynamicArray(int c=10){
			size=0;
			capacity=c;
			start=new int[capacity];
		}
		void addElement(int x);
		void removeElement(int x);
		void print(){
			cout<<"************************\n";
			cout<<"capacity: "<<capacity<<endl;
			cout<<"size:\t"<<size<<endl;
			for (int i=0; i<size; i++){
				cout<<*(start+i)<<"\t";
				if (i%5==4) cout<<endl;
			}
			cout<<endl;
		}	
		
		//i added these in
		int getSize(){
			return size;
		}
		int* getStart(){
			return start;
		}
};
void DynamicArray::addElement(int x){
	if (size==capacity){
		int *temp=new int[2*capacity];
		for (int i=0; i<size; i++){
			temp[i]=*(start+i);
		}
		capacity*=2;
		delete [] start;
		start=temp;
	}
	start[size++]=x;
}
void DynamicArray::removeElement(int x){
	int flag=0;
	int index;
	for (int i=0; i<size; i++){
		if (start[i]==x){
			flag=1;
			index=i;
			break;
		}
	}
	if (flag==1){
		for (int j=index; j<size-1; j++){
			start[j]=start[j+1];
		}
		size--;
	}
	if (size<=capacity/2){
		capacity/=2;
		int *temp;
		temp=new int[capacity];
		for (int i=0; i<size; i++){
			temp[i]=start[i];
		}
		delete [] start;
		start=temp;
	}
	
}

class MultiArray{
	private:
		DynamicArray **ptr;  
		int nbOfArrays;
		int size;
	public:
		MultiArray(int);
		MultiArray(const MultiArray&);
		void addElement(int x);
		void removeElement(int x);
		void print();
};

MultiArray::MultiArray(int n=5){    
	nbOfArrays=n;
	size=0;
	ptr=new DynamicArray*[nbOfArrays];
	for (int i=0;i<nbOfArrays;i++){
		ptr[i]=new DynamicArray;
	}
}
////////////////////////////////////////////////////////////////////////
MultiArray::MultiArray(const MultiArray& other){
	size = 0;
	nbOfArrays = other.nbOfArrays;
	ptr = new DynamicArray*[nbOfArrays]; //allocate new memory for ptr
	for (int i=0;i<nbOfArrays;i++){ //allocate new memory for the DynamicArrays in ptr
		ptr[i]=new DynamicArray;
	}
	for(int i=0; i<nbOfArrays; i++){
		for(int j=0; j<other.ptr[i]->getSize(); j++){ //i went and added the getSize() and getStart() functions
			addElement(other.ptr[i]->getStart()[j]);
			//i used addElement() so the capacities of the DynamicArrays would be updated appropriately
		}
	}
}
////////////////////////////////////////////////////////////////////////
void MultiArray::addElement(int x){
	int temp=1000/nbOfArrays;
	int index=x/temp;
	ptr[index][0].addElement(x);
	size++;
}

void MultiArray::removeElement(int x){
	int temp=1000/nbOfArrays;
	int index=x/temp;
	ptr[index][0].removeElement(x);
	size--;
}
void MultiArray::print(){   
	cout<<"**********************************\n";
	cout<<"**********************************\n";
	cout<<"The number of array is: "<<nbOfArrays<<endl;
	cout<<"The total size is: "<<size<<endl;
	for (int i=0; i<nbOfArrays; i++){
		ptr[i][0].print();
	}
}

int main(){
	MultiArray obj1(5);
	for (int i=0; i<55; i++){
		obj1.addElement(rand()%1000);
	}
	obj1.print();
	int temp1;
	MultiArray obj2(obj1);
	obj2.print();
	cout<<"Enter an element to be removed: "<<endl;
	cin>>temp1;
	obj2.removeElement(temp1);
	obj2.print();
	obj1.print();
	return 0;
}
