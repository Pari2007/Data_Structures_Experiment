#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 50
#define MAX_NAME_LEN 30
// Structure for an adjacency list node (stores friend's user index)
struct AdjListNode {
int dest;
struct AdjListNode* next;
};
// Structure to represent a User
struct User {
char name[MAX_NAME_LEN];
int active; // 1 if user slot is occupied, 0 otherwise
struct AdjListNode* head;
};
// Structure to represent the Social Network Graph
struct SocialNetwork {
int capacity;
struct User users[MAX_USERS];
};
// Function to initialize the social network
void initNetwork(struct SocialNetwork* net, int capacity) {
net->capacity = capacity;
for (int i = 0; i < capacity; i++) {
net->users[i].active = 0;
net->users[i].head = NULL;
}
}
// Function to add a new user
void addUser(struct SocialNetwork* net, const char* name) {
// Check if user already exists
for (int i = 0; i < net->capacity; i++) {
if (net->users[i].active && strcmp(net->users[i].name, name) == 0) {
printf("Error: User '%s' already exists with ID %d.\n", name, i);
return;
}
}
// Find an empty slot
for (int i = 0; i < net->capacity; i++) {
if (!net->users[i].active) {
strcpy(net->users[i].name, name);
net->users[i].active = 1;
net->users[i].head = NULL;
printf("Success: User '%s' added successfully with ID %d.\n", name, i);
return;
}
}
printf("Error: Social network is full! Cannot add more users.\n");
}
// Helper function to check if a friendship already exists
int areFriends(struct SocialNetwork* net, int u1, int u2) {
struct AdjListNode* temp = net->users[u1].head;
while (temp != NULL) {
if (temp->dest == u2) return 1;
temp = temp->next;
}
return 0;
}
// Helper function to add a directed edge in adjacency list
void addDirectedEdge(struct SocialNetwork* net, int src, int dest) {
struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
newNode->dest = dest;
newNode->next = net->users[src].head;
net->users[src].head = newNode;
}
// Function to add a friendship (undirected edge)
void addFriendship(struct SocialNetwork* net, int u1, int u2) {
if (u1 < 0 || u1 >= net->capacity || !net->users[u1].active ||
u2 < 0 || u2 >= net->capacity || !net->users[u2].active) {
printf("Error: One or both user IDs are invalid or inactive.\n");
return;
}
if (u1 == u2) {
return;
printf("Error: A user cannot be friends with themselves.\n");
}
if (areFriends(net, u1, u2)) {
printf("Notice: %s and %s are already friends!\n", net->users[u1].name, net-
>users[u2].name);
return;
}
addDirectedEdge(net, u1, u2);
addDirectedEdge(net, u2, u1);
printf("Success: %s and %s are now connected as friends!\n", net->users[u1].name, net-
>users[u2].name);
}
// Helper function to remove a directed edge
void removeDirectedEdge(struct SocialNetwork* net, int src, int dest) {
struct AdjListNode *curr = net->users[src].head, *prev = NULL;
while (curr != NULL && curr->dest != dest) {
prev = curr;
curr = curr->next;
}
if (curr != NULL) {
if (prev == NULL) {
net->users[src].head = curr->next;
} else {
prev->next = curr->next;
}
free(curr);
}
}
// Function to remove a friendship
void removeFriendship(struct SocialNetwork* net, int u1, int u2) {
if (u1 < 0 || u1 >= net->capacity || !net->users[u1].active ||
u2 < 0 || u2 >= net->capacity || !net->users[u2].active) {
printf("Error: One or both user IDs are invalid or inactive.\n");
return;
}
if (!areFriends(net, u1, u2)) {
printf("Notice: %s and %s are not friends.\n", net->users[u1].name, net->users[u2].name);
return;
}
removeDirectedEdge(net, u1, u2);
removeDirectedEdge(net, u2, u1);
printf("Success: Friendship removed between %s and %s.\n", net->users[u1].name, net-
>users[u2].name);
}
// Function to show user connections and profile
void showUserConnections(struct SocialNetwork* net, int u) {
if (u < 0 || u >= net->capacity || !net->users[u].active) {
printf("Error: Invalid or inactive user ID.\n");
return;
}
printf("\n--- Profile & Connections for %s (ID: %d) ---\n", net->users[u].name, u);
struct AdjListNode* temp = net->users[u].head;
if (temp == NULL) {
printf("No friends yet.\n");
} else {
printf("Friends list:\n");
while (temp != NULL) {
int friendId = temp->dest;
printf(" - %s (ID: %d)\n", net->users[friendId].name, friendId);
temp = temp->next;
}
}
printf("---------------------------------------------\n");
}
// Function to find mutual friends between two users
void findMutualFriends(struct SocialNetwork* net, int u1, int u2) {
if (u1 < 0 || u1 >= net->capacity || !net->users[u1].active ||
u2 < 0 || u2 >= net->capacity || !net->users[u2].active) {
printf("Error: One or both user IDs are invalid or inactive.\n");
return;
}
printf("\n--- Mutual Friends between %s and %s ---\n", net->users[u1].name, net-
>users[u2].name);
int count = 0;
struct AdjListNode* p1 = net->users[u1].head;
while (p1 != NULL) {
int friend1 = p1->dest;
// Check if this friend is also in u2's friend list
struct AdjListNode* p2 = net->users[u2].head;
while (p2 != NULL) {
if (p2->dest == friend1) {
printf(" - %s (ID: %d)\n", net->users[friend1].name, friend1);
count++;
break;
}
p2 = p2->next;
}
p1 = p1->next;
}
}
if (count == 0) {
printf("No mutual friends found.\n");
printf("---------------------------------------------\n");
}
// Function to suggest connections (Friends of Friends)
void suggestConnections(struct SocialNetwork* net, int u) {
if (u < 0 || u >= net->capacity || !net->users[u].active) {
printf("Error: Invalid or inactive user ID.\n");
return;
}
int mutualCounts[MAX_USERS] = {0};
// For every friend of user u
struct AdjListNode* fNode = net->users[u].head;
while (fNode != NULL) {
int friendId = fNode->dest;
// Look at friends of this friend (friends of friends)
struct AdjListNode* fofNode = net->users[friendId].head;
while (fofNode != NULL) {
int fofId = fofNode->dest;
// Suggest only if fofId is not u, not already a direct friend of u, and is active
if (fofId != u && !areFriends(net, u, fofId)) {
mutualCounts[fofId]++;
}
fofNode = fofNode->next;
}
fNode = fNode->next;
}
printf("\n--- Connection Suggestions for %s ---\n", net->users[u].name);
int suggestionsFound = 0;
for (int i = 0; i < net->capacity; i++) {
if (net->users[i].active && mutualCounts[i] > 0) {
printf(" - %s (ID: %d) -> %d mutual friend(s)\n", net->users[i].name, i, mutualCounts[i]);
suggestionsFound = 1;
}
}
}
if (!suggestionsFound) {
printf("No connection suggestions available at this moment.\n");
printf("---------------------------------------\n");
}
// Function to display all registered users
void displayAllUsers(struct SocialNetwork* net) {
printf("\n=== Registered Users in Network ===\n");
int count = 0;
for (int i = 0; i < net->capacity; i++) {
if (net->users[i].active) {
printf("ID: %d | Name: %s\n", i, net->users[i].name);
count++;
}
}
if (count == 0) {
printf("No users registered yet.\n");
}
printf("===================================\n");
}
// Function to clean up memory
void freeNetwork(struct SocialNetwork* net) {
for (int i = 0; i < net->capacity; i++) {
struct AdjListNode* curr = net->users[i].head;
while (curr != NULL) {
struct AdjListNode* temp = curr;
curr = curr->next;
free(temp);
}
}
}
int main() {
struct SocialNetwork net;
initNetwork(&net, MAX_USERS);
int choice, u1, u2;
char name[MAX_NAME_LEN];
do {
printf("\n=== SOCIAL NETWORK MENU ===\n");
printf("1. Add User\n");
printf("2. Display All Users\n");
printf("3. Add Friend (Connect)\n");
printf("4. Remove Friend (Disconnect)\n");
printf("5. Show User Connections\n");
printf("6. Find Mutual Friends\n");
printf("7. Suggest Connections\n");
printf("8. Exit\n");
printf("Enter your choice (1-8): ");
if (scanf("%d", &choice) != 1) {
printf("Invalid input. Please enter a number.\n");
while (getchar() != '\n'); // clear buffer
continue;
}
switch (choice) {
case 1:
printf("Enter user name: ");
scanf("%s", name);
addUser(&net, name);
break;
case 2:
displayAllUsers(&net);
break;
case 3:
displayAllUsers(&net);
printf("Enter User ID 1: ");
scanf("%d", &u1);
printf("Enter User ID 2: ");
scanf("%d", &u2);
addFriendship(&net, u1, u2);
break;
case 4:
displayAllUsers(&net);
printf("Enter User ID 1: ");
scanf("%d", &u1);
printf("Enter User ID 2: ");
scanf("%d", &u2);
removeFriendship(&net, u1, u2);
break;
case 5:
displayAllUsers(&net);
printf("Enter User ID to view connections: ");
scanf("%d", &u1);
showUserConnections(&net, u1);
break;
case 6:
displayAllUsers(&net);
printf("Enter User ID 1: ");
scanf("%d", &u1);
printf("Enter User ID 2: ");
scanf("%d", &u2);
findMutualFriends(&net, u1, u2);
break;
case 7:
displayAllUsers(&net);
printf("Enter User ID for recommendations: ");
scanf("%d", &u1);
suggestConnections(&net, u1);
break;
case 8:
printf("Exiting program. Cleaning up memory...\n");
freeNetwork(&net);
break;
default:
printf("Invalid choice! Please choose between 1 and 8.\n");
}
} while (choice != 8);
return 0;
}
