#include <stdio.h>
#include <stdlib.h>

struct Node{
	int key;
	Node* left;
	Node* right;
	int height;
};

Node* makeNode(int key){
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left=NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

int height(Node* root){
	if(root==NULL){
		return 0;
	}
	else{
		return root->height;
	}
}

int max(int a,int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

int getBf(Node* root){
	if(root==NULL){
		return 0;
	}
	else{
		return height(root->left)-height(root->right);
	}
}

Node* rightRotate(Node* A){
	Node* B = A->left;
	A->left = B->right;
	B->right = A;
	
	A->height =  1 + max(height(A->left),height(A->right));
	B->height =  1 + max(height(B->left),height(B->right));
	
	return B;
}

Node* leftRotate(Node* A){
	Node* C = A->right;
	A->right = C->left;
	C->left = A;
	
	A->height = 1 + max(height(A->left),height(A->right));
	C->height = 1 + max(height(C->left),height(C->right));
	
	return C;
}

Node* getSuccessor(Node* root){
	Node* curr = root->right;
	while(curr->left!=NULL){
		curr= curr->left;
	}
	return curr;
}

Node* insert(Node* root, int key){
	if(root==NULL){
		return makeNode(key);
	}
	if(key < root->key){
		root->left = insert(root->left,key);
	}
	else if( key > root->key){
		root->right = insert(root->right,key);
	}
	return root;
	
	root->height =  1 + max(height(root->left),height(root->right));
	
	int bf = getBf(root);
	
	if(bf > 1 && key < root->left->key){
		rightRotate(root);
	}
	if(bf < -1 && key > root->right->key){
		leftRotate(root);
	}
	if(bf > 1 && key > root->left->key){
		root-> left = leftRotate(root->left);
		rightRotate(root);
	}
	if(bf < -1 && key < root->right->key){
		root->right = rightRotate(root->right);
		leftRotate(root);
	}
}

void view(Node* root){
	if(root!=NULL){
		printf("%d\n",root->key);
		view(root->left);
		view(root->right);
	}
}

Node* deleteNode(Node* root, int key){
	if(root==NULL){
		return root;
	}
	if(key < root->key){
		root->left = deleteNode(root->left,key);
	}
	else if(key > root->key){
		root->right = deleteNode(root->right,key);
	}
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		else if(root->left == NULL && root->right!=NULL){
			Node* temp = root->right;
			*root = *temp;
			free(temp);
		}
		else if(root->left != NULL && root->right==NULL){
			Node* temp = root->left;
			*root = *temp;
			free(temp);
		}
		else if(root->left != NULL && root->right != NULL){
			Node* successor = getSuccessor(root);
			root->key = successor->key;
			root->right = deleteNode(root->right,successor->key);
		}
	}
	if(root==NULL){
		return root;
	}
	root->height =  1 + max(height(root->left),height(root->right));
	int bf = getBf(root);
	if(bf>1 && getBf(root->left)>=0){
		return rightRotate(root);
	}
	if(bf>1 && getBf(root->left)<0){
		root->left =  leftRotate(root->left);
		return rightRotate(root);
	}
	if(bf<-1 && getBf(root->right)<=0){
		return leftRotate(root);
	}
	if(bf<-1 && getBf(root->right)>0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

int main(){
	Node* root=NULL;
	root = insert(root,9);
	root = insert(root,5);
	root = insert(root,10);
	root = insert(root,0);
	root = insert(root,6);
	root = insert(root,11);
	view(root);
	puts("");
	puts("");
	root= deleteNode(root,6);
	view(root);
	return 0;
}
