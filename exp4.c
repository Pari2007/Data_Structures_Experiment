#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
} Node;


Node* createNode(int val);
void insertAtBeginning(Node** head, int val);
void insertAtEnd(Node** head, int val);
void insertAtPosition(Node** head, int val, int pos);
void deleteFromBeginning(Node** head);
void deleteFromEnd(Node** head);
void deleteFromPosition(Node** head, int pos);
void search(Node* head, int key);
int countNodes(Node* head);
void reverse(Node** head);
void display(Node* head);


int main() {
    Node* head = NULL;
    int choice, val, pos;

    while (1) {

        printf("     SINGLY LINKED LIST MENU (enter choices 1-11 for desired operations)   \n");
        printf(" 1. Insert at Beginning\n");
        printf(" 2. Insert at End\n");
        printf(" 3. Insert at Specific Position\n");
        printf(" 4. Delete from Beginning\n");
        printf(" 5. Delete from End\n");
        printf(" 6. Delete from Specific Position\n");
        printf(" 7. Search Element\n");
        printf(" 8. Count Nodes\n");
        printf(" 9. Reverse List\n");
        printf("10. Display List\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
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
                printf("Enter element to search: ");
                scanf("%d", &val);
                search(head, val);
                break;
            case 8:
                printf("Total nodes: %d\n", countNodes(head));
                break;
            case 9:
                reverse(&head);
                break;
            case 10:
                display(head);
                break;
            case 11:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}


Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

=
void insertAtBeginning(Node** head, int val) {
    Node* newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at the beginning.\n", val);
}

=
void insertAtEnd(Node** head, int val) {
    Node* newNode = createNode(val);
    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d as head node.\n", val);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at the end.\n", val);
}


void insertAtPosition(Node** head, int val, int pos) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 1) {
        insertAtBeginning(head, val);
        return;
    }
    Node* temp = *head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds!\n");
        return;
    }
    Node* newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", val, pos);
}


void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    printf("Deleted %d from the beginning.\n", temp->data);
    free(temp);
}


void deleteFromEnd(Node** head) {
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
    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    printf("Deleted %d from the end.\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}


void deleteFromPosition(Node** head, int pos) {
    if (*head == NULL) {
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
    Node* temp = *head;
    for (int i = 1; i < pos - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Position out of bounds!\n");
        return;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    printf("Deleted %d from position %d.\n", nodeToDelete->data, pos);
    free(nodeToDelete);
}


void search(Node* head, int key) {
    Node* temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("Element %d found at position %d.\n", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Element %d not found in the list.\n", key);
}


int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}


void reverse(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    printf("List reversed successfully.\n");
}

void display(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

    *head = NULL;
}
