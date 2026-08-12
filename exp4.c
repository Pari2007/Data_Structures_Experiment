#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
}Node;


struct Node* createNode(int val);
void insertAtBeginning(struct Node** head, int val);
void insertAtEnd(struct Node** head, int val);
void insertAtPosition(struct Node** head, int val, int pos);
void deleteFromBeginning(struct Node** head);
void deleteFromEnd(struct Node** head);
void deleteFromPosition(struct Node** head, int pos);
void display(struct Node* head);


int main() {
    struct Node* head = NULL;
    int choice, val, pos;

    while (1) {

        printf(" SINGLY LINKED LIST MENU (enter choices 1-8 for desired operations)   \n");
        printf(" 1. Insert at Beginning\n");
        printf(" 2. Insert at End\n");
        printf(" 3. Insert at Specific Position\n");
        printf(" 4. Delete from Beginning\n");
        printf(" 5. Delete from End\n");
        printf(" 6. Delete from Specific Position\n");
        printf(" 7. Display List\n");
        printf(" 8. Exit\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insertAtBeginning(&head, val);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                insertAtEnd(&head, val);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &val);
                printf("Enter position: ");
                scanf("%d", &pos);
                insertAtPosition(&head, val, pos);
                break;
            case 4:
                deleteFromBeginning(&head);
                break;
            case 5:
                deleteFromEnd(&head);
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteFromPosition(&head, pos);
                break;
            case 7:
                display(head);
                break;
            case 8:
                printf("Exiting program\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}


void insertAtBeginning(struct Node** head, int val) {
    struct Node* newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at the beginning.\n", val);
}


void insertAtEnd(struct Node** head, int val) {
    struct Node* newNode = createNode(val);
    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d as head node.\n", val);
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at the end.\n", val);
}


void insertAtPosition(struct Node** head, int val, int pos) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 1) {
        insertAtBeginning(head, val);
        return;
    }
    struct Node* temp = *head;
    int i;
    for (i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds!\n");
        return;
    }
    struct Node* newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", val, pos);
}


void deleteFromBeginning(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    printf("Deleted %d from the beginning.\n", temp->data);
    free(temp);
}


void deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    if ((*head)->next == NULL) {
        printf("Deleted %d from the end.\n", (*head)->data);
        free(*head);
        *head = NULL;
        return;
    }
    struct Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    printf("Deleted %d from the end.\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}


void deleteFromPosition(struct Node** head, int pos) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 1) {
        deleteFromBeginning(head);
        return;
    }
    struct Node* temp = *head;
    int i;
    for (i = 1; i < pos - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Position out of bounds!\n");
        return;
    }
    struct Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    printf("Deleted %d from position %d.\n", nodeToDelete->data, pos);
    free(nodeToDelete);
}


void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
