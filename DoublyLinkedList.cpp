//Nicolas Lovelace CS2 Fall 2021
#include <iostream>
using namespace std;

class DNode {
private:
	int data;
	DNode* next, * previous;
public:
	DNode(int d = 0, DNode* n = NULL, DNode* p = NULL) {
		data = d;
		next = n;
		previous = p;
	}
	int getData() {
		return data;
	}
	void setData(int x) {
		data = x;
	}
	DNode* getNext() {
		return next;
	}
	void setNext(DNode* x) {
		next = x;
	}
	DNode* getPrevious() {
		return previous;
	}
	void setPrevious(DNode* x) {
		previous = x;
	}
};

class CDLList {
private:
	DNode* first, * last;
	int size;
public:
	CDLList() {
		first = last = NULL;
		size = 0;
	}
	DNode* getFirst() {
		return first;
	}
	void setFirst(DNode* x) {
		first = x;
	}
	DNode* getLast() {
		return last;
	}
	void setLast(DNode* x) {
		last = x;
	}
	int getSize() {
		return size;
	}
	void setSize(int x) {
		size = x;
	}
	void addFront(int x);
	void addRear(int x);
	void removeFront();
	void removeRear();
	void print();
};

void CDLList::addFront(int x) {
	if (size == 0) {
		first = new DNode(x); //creating first node
		first->setNext(first); //making node point to itself
		first->setPrevious(first);
		last = first; //setting last and first equal, because there is one member and both are the same member
	}
	else {
		first = new DNode(x, first, last); //creating a new node containing x, in front of old first and behind last
		first->getNext()->setPrevious(first); //setting old first's previous pointer to the new first
		last->setNext(first); //connecting last and new first
	}
	size++;
}
void CDLList::addRear(int x) {
	if (size == 0) {
		first = new DNode(x); //creating first node
		first->setNext(first); //making node point to itself
		first->setPrevious(first);
		last = first; //setting last and first equal, because there is one member and both are the same member
	}
	else {
		last = new DNode(x, first, last); //creating a new node containing x, in behind old last and before last
		last->getPrevious()->setNext(last); //setting old last's next pointer to the new last
		first->setPrevious(last); //connecting first and new last
	}
	size++;
}
void CDLList::removeFront() {
	first = first->getNext(); //new first is second element
	last->setNext(first); //connect to new first
	first->setPrevious(last); //write over old first
	size--;
}
void CDLList::removeRear() {
	last = last->getPrevious(); //new last is second to last element
	last->setNext(first); //connect to new last
	first->setPrevious(last); //write over old last
	size--;
}
void CDLList::print() {
	DNode* temp = first;
	for (int i = 0; i < size; i++) {
		cout << temp->getData() << " ";
		temp = temp->getNext();
	}
	cout << endl;
}

int main() {
	CDLList Obj1;
	for(int i = 0; i < 10; i++) {
		Obj1.addFront(i * 20);
		Obj1.addRear(i * 100 + 11);
	}
	Obj1.print();
	Obj1.removeFront();
	Obj1.print();
	Obj1.removeRear();
	Obj1.print();
	return 0;
}
