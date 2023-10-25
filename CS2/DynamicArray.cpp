//Nicolas Lovelace CS2 Fall 2021
#include <iostream>
using namespace std;

class DynamicArray{
	private:
		int capacity; //available spaces across the storage
		double **start; //storage of one or multiple dynamic arrays
		int *size; //array of sizes, corresponding to each segment
		bool segmented; //segmentation status
		int segs; //segments in the storage
		
		
	public:
		DynamicArray();
		void addElement(double num);
		void removeElement(double num);
		void segmentation(int x);
		void merge();
		void print();
};

DynamicArray::DynamicArray(){
	//non segmented dynamic array size 20
	start = new double*; //storage size 1 containing 1 array
	*start = new double[20]; //array at storage[0] size 20 containing 20 doubles
	size = new int;
	*size = 0; //size at [0] is 0
	capacity = 20;
	segmented = false;
	segs = 1;
}

void DynamicArray::addElement(double num){
	//add num to storage
	//to keep the elements evenly distrubuted i ended up merging the whole thing, adding it, then resegmenting it
	int segsN = segs; //saving this b/c merge function sets it back to 1
	if(segmented) {
	    merge();
	    segmented = true; //setting this true so the function at the end is activated
	}
	
	if(*size==capacity){
	    double *temp = new double[capacity*2];
	    capacity*=2; //increasing capacity
	    
	    for(int i=0; i<*size; i++){
	      temp[i] = start[0][i]; //copying data over to new array
	    }
	    delete []*start;
	    *start = temp; //array is back to normal
	}
	    
    start[0][(*size)++] = num; //adding num to the array and increasing total size
    
    if(segmented){
    	segmented = false; //setting false so the segmentation function will activate
    	segmentation(segsN); //resegmenting to original amount of segments
	}
}

void DynamicArray::removeElement(double num){
	//remove num from storage
	int segsN = segs; //saving for later again
	if(segmented) {
	    merge();
	   	segmented = true; //setting true to activate function at the end
	}
	int i;
  	for(i=0; i<*size; i++){
  		if(start[0][i]==num) break; //finding first iteration of num to be removed
  	}
  	if(i==*size) return;
  	for(int j=i; j<*size; j++){
      	start[0][j]=start[0][j+1]; //scooting over all elements on top of num to remove it
  	}
  	(*size)--; //decreasing total size
	
	if(*size<=capacity/2){
	    double *temp = new double[capacity/2];
	    capacity/=2; //decreasing capacity
	    
	    for(int i=0; i<*size; i++){
	      temp[i] = start[0][i]; //copying over
	    }
	    delete []*start;
	    *start = temp; //array is back to normal
	}
	
	if(segmented) {
    	segmented = false; //set to false to activate segmentation
    	segmentation(segsN); //segmenting to original segments
	}
}

void DynamicArray::segmentation(int x){
	//if not segmented, divide array into x smaller arrays
	if(!segmented){
		double *temp = new double[*size];
	    for(int i=0; i<*size; i++){
	      temp[i] = start[0][i]; //copying over the original array to a temporary place to call from
	    }
	    delete []*start;
	    delete []start; //deleting old stuff
	    
	    segs = x; //setting segments to given segments
	    start = new double*[segs]; //remaking start to contain segs number of segments
		
		//20/5 = 4 indeces per segment
		//20/3 = 6 indeces per segment/ 2 left over
		int indecesToArray = *size/x;
		if(*size%x !=0) indecesToArray++;

		//i*indecesToArray+j
		
		int side = *size; //saving this for later b/c size will be reset
		delete []size;
		size = new int[x];
		
		for(int i=0; i<x; i++){
			start[i] = new double[indecesToArray]; //removing -1 did nothing?
			int j;
			for(j=0; j<indecesToArray; j++){
				if(i*indecesToArray+j>=side) break;
				start[i][j] = temp[i*indecesToArray+j]; //copying original array to the different arrays
			}
			size[i] = j; //saving number of elements after j runs to get size for each segment
		}
		delete []temp;
		segmented = true; //storage is now segmented
	}
}

void DynamicArray::merge(){
	//if segmented, group all arrays used for storage in one large array
	if(segmented){
		//int indecesToArray = capacity/segs;
		//if(capacity%segs !=0) indecesToArray++;
		int tot = 0;
		for(int i=0; i<segs; i++){ //getting total size for later
			tot+=size[i];
		}
			
		double *temp = new double[capacity]; //temporary
		int counter = 0; //i had to use a counter, my formula kept messing up and i gave up on it
	    for(int i=0; i<segs; i++){
			for(int j=0; j<size[i]; j++){
				if(i*size[i]+j==tot) break;
				temp[counter++] = start[i][j]; //copy everything over to one array using two loops for a 2d array
			}
			delete []*(start+i); //delete each segment
		}
	    //delete []start; //these made my print statement stop working after using this function. i'm not sure why
	    //delete []size;
	    *size = tot; //setting everything right for a non segmented storage
	    segs = 1;
	    *start = temp;
		segmented = false; //no longer segmented
	}
}

void DynamicArray::print(){
	//capacity
	//number of arrays used for storage
	//size and elements of each array
	
	int tot = 0;
	for(int i=0; i<segs; i++){ //getting total size for later
		tot+=size[i];
	}
	
	cout << "capacity " << capacity << endl;
	cout << "arrays " << segs << endl;
	cout << "total size " << tot << endl;
	
	for(int i=0; i<segs; i++){
		cout << "size " << size[i] << endl;
		for(int j=0; j<size[i]; j++){
			cout << start[i][j] << " ";
		}
		cout << "\n";
	}
	
	cout << "\n";
	
}

int main(){
	DynamicArray bob;
	
	for(int i=0; i<25; i++){
		bob.addElement(i*2);
	}
	bob.print();
	bob.segmentation(3);
	bob.print();
	for(int i=0; i<10; i++){
		bob.addElement(i*2);
	}
	bob.print();
	for(int i=0; i<5; i++){
		bob.addElement(i*2);
	}
	bob.print();
	bob.addElement(200);
	bob.print();
	bob.removeElement(200);
	bob.print();
	
	return 0;
}
