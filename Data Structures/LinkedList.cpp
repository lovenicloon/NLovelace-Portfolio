//NICOLAS LOVELACE
//CS2413
//DR CHAO ZHAO
//HW 5
//MAR 28, 2022

/*

	Creates a linked list and prints the linked list.

*/

#include <iostream>
using namespace std;

struct Node{
	int x;
	Node* next;
};

void insertNode(Node** head, Node* b){
	if(*head==NULL){
		*head = b; //create head if not already created
	}
	else{
		Node* temp = *head; //temp for head b/c it was brought in by reference
		while(temp->next!=NULL){
			temp=temp->next; //we know we are at the right position because next will be NULL
		}
		temp->next = b;
	}
}

void printList(Node* head){
	Node* temp = head;
	while(temp!=NULL){
		cout << temp->x << " "; //print x
		temp = temp->next; //move along
	}
}

int main(){
	Node *head = NULL;
	
	for(int i=0; i<20; i++){
		Node* temp = new Node;
		temp->x = i;
		temp->next = NULL;

		insertNode(&head, temp);
	}
	
	printList(head);
	return 0;
}
