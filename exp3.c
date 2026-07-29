#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

int max = 5;
int val;
int choice;
int front = -1;
int rear = -1;
int i;
int queue[SIZE];

int enqueue();
int dequeue();
int display();

int main(){

	while(1){	
	printf("Queue Implementation Using Array Enter (1) to (4) for operations,Enter \n(1) Enqueue an element, \n(2) Dequeue an element, \n(3) Display the contents of the queue\n (4) Exit the program\n Your Choice: ");
	scanf("%d", &choice);

	
	switch(choice){
		case 1 :
			enqueue();
			break;
		case 2:
			dequeue();
			break;
		case 3:
			display();
			break;
		case 4:
			exit(0);
		default:
			printf("Invalid Choice\n\n");
	}
}


	
	return 0;
}

int enqueue(){

	if(front == (rear + 1) % SIZE){
		printf("Queue Overflow\n\n");
		return 0;
	} 
	 if(front == -1){
		front = 0;
}

		printf("Enter the element to be enqueued: ");
		scanf("%d", &val);
		
		rear = (rear+1)%SIZE;
		queue[rear] = val;	
		printf("Element enqueued is %d\n\n", queue[rear]);
	
}


int dequeue(){

	if(front == -1){
		printf("Queue Underflow\n\n");
	}
	else{

	printf("The element dequeued is %d\n\n", queue[front]);
	if(front==rear)
	{
		front =-1;
		rear = -1;
	}
	else
	{
		front = (front+1)%SIZE;
	}
		
	}
}


int display(){

	if(front == -1){
		printf("Queue is empty\n");
	}
	else{
		i = front;
		printf("Queue elements are :\n ");
		while(1){
			printf("\n%d\n", queue[i]);
			if(i==rear){
				break;
			}
			i = (i+1)%SIZE;
		}
	}
}
