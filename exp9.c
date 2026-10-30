#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Node {
    int key;
    int degree;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
} Node;


Node* createNode(int key);
Node* mergeBinomialTrees(Node* b1, Node* b2);
Node* unionBinomialHeaps(Node* h1, Node* h2);
Node* insert(Node* h, int key);
Node* findMin(Node* h);
Node* extractMin(Node* h);
Node* searchKey(Node* h, int key);
Node* decreaseKey(Node* h, int old_key, int new_key);
Node* deleteKey(Node* h, int key);
void printTree(Node* h);
void printHeap(Node* h);


Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}


Node* mergeBinomialTrees(Node* b1, Node* b2) {
    if (b1->key > b2->key) {
        Node* temp = b1;
        b1 = b2;
        b2 = temp;
    }
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}


Node* unionBinomialHeaps(Node* h1, Node* h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    Node* newHead = NULL;
    Node* tail = NULL;
    Node* i = h1;
    Node* j = h2;

    if (i->degree <= j->degree) {
        newHead = i;
        i = i->sibling;
    } else {
        newHead = j;
        j = j->sibling;
    }
    tail = newHead;

    while (i != NULL && j != NULL) {
        if (i->degree <= j->degree) {
            tail->sibling = i;
            i = i->sibling;
        } else {
            tail->sibling = j;
            j = j->sibling;
        }
        tail = tail->sibling;
    }

    if (i != NULL) tail->sibling = i;
    else tail->sibling = j;

    if (newHead == NULL) return NULL;

    Node* prev = NULL;
    Node* x = newHead;
    Node* next = x->sibling;

    while (next != NULL) {
        if ((x->degree != next->degree) || 
            (next->sibling != NULL && next->sibling->degree == x->degree)) {
            prev = x;
            x = next;
        } else {
            if (x->key <= next->key) {
                x->sibling = next->sibling;
                mergeBinomialTrees(x, next);
            } else {
                if (prev == NULL) {
                    newHead = next;
                } else {
                    prev->sibling = next;
                }
                mergeBinomialTrees(next, x);
                x = next;
            }
        }
        next = x->sibling;
    }
    return newHead;
}


Node* insert(Node* h, int key) {
    Node* temp = createNode(key);
    return unionBinomialHeaps(h, temp);
}


Node* findMin(Node* h) {
    if (h == NULL) return NULL;
    Node* minNode = h;
    Node* curr = h->sibling;
    int minVal = h->key;

    while (curr != NULL) {
        if (curr->key < minVal) {
            minVal = curr->key;
            minNode = curr;
        }
        curr = curr->sibling;
    }
    return minNode;
}


Node* extractMin(Node* h) {
    if (h == NULL) return NULL;

    Node* minPrev = NULL;
    Node* minNode = h;
    Node* curr = h;
    Node* prev = NULL;
    int minVal = h->key;

    while (curr != NULL) {
        if (curr->key < minVal) {
            minVal = curr->key;
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (minPrev == NULL) {
        h = minNode->sibling;
    } else {
        minPrev->sibling = minNode->sibling;
    }

    Node* childList = NULL;
    Node* child = minNode->child;
    while (child != NULL) {
        Node* nextChild = child->sibling;
        child->sibling = childList;
        child->parent = NULL;
        childList = child;
        child = nextChild;
    }

    free(minNode);
    return unionBinomialHeaps(h, childList);
}


Node* searchTree(Node* tree, int key) {
    if (tree == NULL) return NULL;
    if (tree->key == key) return tree;

    Node* res = searchTree(tree->child, key);
    if (res != NULL) return res;

    return searchTree(tree->sibling, key);
}


Node* searchKey(Node* h, int key) {
    Node* curr = h;
    while (curr != NULL) {
        if (curr->key == key) return curr;
        Node* res = searchTree(curr->child, key);
        if (res != NULL) return res;
        curr = curr->sibling;
    }
    return NULL;
}


Node* decreaseKey(Node* h, int old_key, int new_key) {
    Node* node = searchKey(h, old_key);
    if (node == NULL) {
        printf("Key %d not found in the heap.\n", old_key);
        return h;
    }
    if (new_key > node->key) {
        printf("Error: New key is greater than current key.\n");
        return h;
    }

    node->key = new_key;
    Node* curr = node;
    Node* parent = curr->parent;

    while (parent != NULL && curr->key < parent->key) {
        int temp = curr->key;
        curr->key = parent->key;
        parent->key = temp;

        curr = parent;
        parent = curr->parent;
    }
    printf("Key decreased successfully.\n");
    return h;
}


Node* deleteKey(Node* h, int key) {
    Node* node = searchKey(h, key);
    if (node == NULL) {
        printf("Key %d not found in the heap.\n", key);
        return h;
    }
    

    node->key = INT_MIN;
    Node* curr = node;
    Node* parent = curr->parent;

    while (parent != NULL && curr->key < parent->key) {
        int temp = curr->key;
        curr->key = parent->key;
        parent->key = temp;

        curr = parent;
        parent = curr->parent;
    }

    return extractMin(h);
}


void printTree(Node* h) {
    if (h == NULL) return;
    printf("(Key: %d, Deg: %d) ", h->key, h->degree);
    printTree(h->child);
}


void printHeap(Node* h) {
    if (h == NULL) {
        printf("Heap is empty.\n");
        return;
    }
    printf("--- Binomial Heap Roots ---\n");
    Node* curr = h;
    while (curr != NULL) {
        printf("Degree %d root -> ", curr->degree);
        printTree(curr);
        printf("\n");
        curr = curr->sibling;
    }
}


int main() {
    Node* heap1 = NULL;
    Node* heap2 = NULL;
    int choice, key, new_key, old_key;

    do {
        printf("\n=============================\n");
        printf("     BINOMIAL HEAP MENU      \n");
        printf("=============================\n");
        printf("1. Insert into Heap 1\n");
        printf("2. Find Minimum in Heap 1\n");
        printf("3. Extract Minimum from Heap 1\n");
        printf("4. Decrease Key in Heap 1\n");
        printf("5. Delete Key from Heap 1\n");
        printf("6. Display Heap 1\n");
        printf("7. Union Heap 1 and Heap 2\n");
        printf("8. Insert into Heap 2 (for Union test)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                heap1 = insert(heap1, key);
                printf("Inserted %d into Heap 1.\n", key);
                break;
            case 2: {
                Node* minNode = findMin(heap1);
                if (minNode != NULL)
                    printf("Minimum key in Heap 1 is: %d\n", minNode->key);
                else
                    printf("Heap 1 is empty.\n");
                break;
            }
            case 3: {
                Node* minNode = findMin(heap1);
                if (minNode != NULL) {
                    heap1 = extractMin(heap1);
                    printf("Extracted minimum successfully.\n");
                } else {
                    printf("Heap 1 is empty.\n");
                }
                break;
            }
            case 4:
                printf("Enter old key to decrease: ");
                scanf("%d", &old_key);
                printf("Enter new key value: ");
                scanf("%d", &new_key);
                heap1 = decreaseKey(heap1, old_key, new_key);
                break;
            case 5:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                heap1 = deleteKey(heap1, key);
                printf("Deleted key %d from Heap 1.\n", key);
                break;
            case 6:
                printHeap(heap1);
                break;
            case 7:
                heap1 = unionBinomialHeaps(heap1, heap2);
                heap2 = NULL; 
                printf("Heap 1 and Heap 2 successfully merged into Heap 1.\n");
                break;
            case 8:
                printf("Enter key to insert into Heap 2: ");
                scanf("%d", &key);
                heap2 = insert(heap2, key);
                printf("Inserted %d into Heap 2.\n", key);
                break;
            case 9:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}
