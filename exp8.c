#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct ChainNode {
    int key;
    struct ChainNode* next;
} ChainNode;

ChainNode* chainTable[TABLE_SIZE];

void initChainTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        chainTable[i] = NULL;
    }
}

void insertChain(int key) {
    int index = key % TABLE_SIZE;
    ChainNode* newNode = (ChainNode*)malloc(sizeof(ChainNode));
    newNode->key = key;
    newNode->next = chainTable[index];
    chainTable[index] = newNode;
    printf("Inserted %d at chain index %d\n", key, index);
}

void searchChain(int key) {
    int index = key % TABLE_SIZE;
    ChainNode* temp = chainTable[index];
    int pos = 0;
    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key %d found at chain index %d (position %d)\n", key, index, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Key %d not found.\n", key);
}

void displayChain() {
    printf("\n--- Separate Chaining Hash Table ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        ChainNode* temp = chainTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}



int openTable[TABLE_SIZE];

void initOpenTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        openTable[i] = -1; 
    }
}


void insertLinear(int key) {
    int hash = key % TABLE_SIZE;
    int index;
    for (int i = 0; i < TABLE_SIZE; i++) {
        index = (hash + i) % TABLE_SIZE;
        if (openTable[index] == -1) {
            openTable[index] = key;
            printf("Inserted %d at index %d using Linear Probing\n", key, index);
            return;
        }
    }
    printf("Hash Table is Full!\n");
}

void searchLinear(int key) {
    int hash = key % TABLE_SIZE;
    int index;
    for (int i = 0; i < TABLE_SIZE; i++) {
        index = (hash + i) % TABLE_SIZE;
        if (openTable[index] == -1) break; // Slot empty, key not present
        if (openTable[index] == key) {
            printf("Key %d found at index %d (Linear Probing)\n", key, index);
            return;
        }
    }
    printf("Key %d not found.\n", key);
}


void insertQuadratic(int key) {
    int hash = key % TABLE_SIZE;
    int index;
    for (int i = 0; i < TABLE_SIZE; i++) {
        index = (hash + i * i) % TABLE_SIZE;
        if (openTable[index] == -1) {
            openTable[index] = key;
            printf("Inserted %d at index %d using Quadratic Probing\n", key, index);
            return;
        }
    }
    printf("Hash Table is Full or probe sequence cycled!\n");
}

void searchQuadratic(int key) {
    int hash = key % TABLE_SIZE;
    int index;
    for (int i = 0; i < TABLE_SIZE; i++) {
        index = (hash + i * i) % TABLE_SIZE;
        if (openTable[index] == -1) break;
        if (openTable[index] == key) {
            printf("Key %d found at index %d (Quadratic Probing)\n", key, index);
            return;
        }
    }
    printf("Key %d not found.\n", key);
}

int hash2(int key) {
    int R = 7; 
    return R - (key % R);
}

void insertDouble(int key) {
    int hash1 = key % TABLE_SIZE;
    int stepSize = hash2(key);
    int index;
    for (int i = 0; i < TABLE_SIZE; i++) {
        index = (hash1 + i * stepSize) % TABLE_SIZE;
        if (openTable[index] == -1) {
            openTable[index] = key;
            printf("Inserted %d at index %d using Double Hashing\n", key, index);
            return;
        }
    }
    printf("Hash Table is Full!\n");
}

void searchDouble(int key) {
    int hash1 = key % TABLE_SIZE;
    int stepSize = hash2(key);
    int index;
    for (int i = 0; i < TABLE_SIZE; i++) {
        index = (hash1 + i * stepSize) % TABLE_SIZE;
        if (openTable[index] == -1) break;
        if (openTable[index] == key) {
            printf("Key %d found at index %d (Double Hashing)\n", key, index);
            return;
        }
    }
    printf("Key %d not found.\n", key);
}

void displayOpenTable() {
    printf("\n--- Open Addressing Hash Table ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (openTable[i] == -1)
            printf("Index %d: [EMPTY]\n", i);
        else
            printf("Index %d: %d\n", i, openTable[i]);
    }
}



int main() {
    int methodChoice, opChoice, key;

    do {
        printf("\n========================================\n");
        printf("      HASH TABLE IMPLEMENTATION       \n");
        printf("========================================\n");
        printf("Select Collision Resolution Technique:\n");
        printf("1. Separate Chaining\n");
        printf("2. Linear Probing\n");
        printf("3. Quadratic Probing\n");
        printf("4. Double Hashing\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &methodChoice) != 1) break;
        if (methodChoice == 5) break;


        initChainTable();
        initOpenTable();

        do {
            printf("\n--- OPERATIONS MENU ---\n");
            printf("1. Insert Key\n");
            printf("2. Search Key\n");
            printf("3. Display Table\n");
            printf("4. Switch Technique / Back to Main Menu\n");
            printf("Enter your operation choice: ");
            scanf("%d", &opChoice);

            switch (opChoice) {
                case 1:
                    printf("Enter key to insert: ");
                    scanf("%d", &key);
                    if (methodChoice == 1) insertChain(key);
                    else if (methodChoice == 2) insertLinear(key);
                    else if (methodChoice == 3) insertQuadratic(key);
                    else if (methodChoice == 4) insertDouble(key);
                    break;
                case 2:
                    printf("Enter key to search: ");
                    scanf("%d", &key);
                    if (methodChoice == 1) searchChain(key);
                    else if (methodChoice == 2) searchLinear(key);
                    else if (methodChoice == 3) searchQuadratic(key);
                    else if (methodChoice == 4) searchDouble(key);
                    break;
                case 3:
                    if (methodChoice == 1) displayChain();
                    else displayOpenTable();
                    break;
                case 4:
                    printf("Switching technique...\n");
                    break;
                default:
                    printf("Invalid operation choice!\n");
            }
        } while (opChoice != 4);

    } while (methodChoice != 5);

    printf("Exiting program.\n");
    return 0;
}
