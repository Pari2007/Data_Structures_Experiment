#include <stdio.h>
#include <stdlib.h>
struct BSTNode
{
	int data;
	struct BSTNode *left;
	struct BSTNode *right;
};


struct BSTNode * createBST(struct BSTNode *root,int item);
void Inorder(struct BSTNode *root);
void preOrder(struct BSTNode *root);
void postOrder(struct BSTNode *root);
struct BSTNode* searchNode(struct BSTNode *root, int target);

int main(){
struct BSTNode *root = NULL;
int choice,element,target;
struct BSTNode *searchResult = NULL;
	
	while(1)
	{
	printf("\nEnter 1-5 to perform Operations in Binary Search Trees\n (1) Insertion \n (2) InOrder Traversal \n (3) PostOrder Traversal \n (4) PreOrder Traversal \n (5) Searching \n (6) Clear BST\n Your Choice: ");	
	scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the element to be inserted: ");
				scanf("%d",&element);	
				root = createBST(root,element);
				break;
			case 2:
				printf("Inorder Traversal");
				InOrder(root);
				break;
			case 3:
				printf("Postorder Traversal");
				postOrder(root);
				break;
			case 4:
				printf("Preorder Traversal");
				preOrder(root);
				break;
			case 5:
				printf("Enter the element to be searched: ");
				scanf("%d",&target);	
				searchResult = searchNode(root,target);
				if(searchResult==NULL){
					printf("Element not found in BST \n");
				}
				else{
					printf("Element found in BST \n" );
				}
				break;
			case 6:
				root = NULL;
				printf("BST has been cleared");
			}
	
	}
return 0;	
}


struct BSTNode * createBST(struct BSTNode *root,int item)
{
	if(root == NULL)
	{
	root = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	root->data = item;
	root->left = NULL;
	root->right = NULL;
	return root;
	}
	else
	{
		if(item == root->data)
		{
			printf("Duplicate element not allowed.\n");
		}
		else if(item < root->data)
		{
			root->left = createBST(root->left,item);
		}
		else if(item > root->data)
		{
			root->right = createBST(root->right,item);		
		}
		return root;
	}
}

void postOrder(struct BSTNode *root){
	if(root!= NULL){
		postOrder(root->left);
		postOrder( root->right);
		printf("\n");
		printf("%d", root->data);
		printf("\n");
	}
}

void InOrder(struct BSTNode *root){
	if(root!= NULL){

		InOrder( root->left);
		printf("\n");
		printf("%d", root->data);
		printf("\n");
		InOrder( root->right);
		
	}

}
void preOrder(struct BSTNode *root){
	if(root!= NULL){
		printf("\n");
		printf("%d", root->data);
		printf("\n");
		preOrder(root->left);
		preOrder(root->right);

	}
}
struct BSTNode* searchNode(struct BSTNode *root, int target){
	if(root == NULL || root -> data == target){
		return root;
				printf("\n");
	}
	else if(root->data < target){
		return searchNode(root->right,target);
				printf("\n");
	}
	return searchNode(root->left,target);
			printf("\n");
	
}

