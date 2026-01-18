#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node* node_ptr;

struct Node{
	int value;
	node_ptr left;
	node_ptr right;
	bool lthread;
	bool rthread;
};



node_ptr create_node(int value){
	node_ptr n = (node_ptr)malloc(sizeof(Node));
	if(!n){
		perror("Error: Memory Allocation Failed");
		exit(1);
	}

	n->value = value;
	n->left = NULL;
	n->right = NULL;
	n->lthread = false;
	n->rthread = false;

	return n;
}

void inorder_thread(node_ptr root , node_ptr* prev){
	if(!root) return;

	inorder_thread(root->left,prev);

	if(root->left==NULL){
		root->left = *prev;
		root->lthread = true;
	}
	if(*prev && (*prev)->right==NULL){
		(*prev)->right=root;
		(*prev)->rthread = true;   	
	}

	*prev = root;

	inorder_thread(root->right,prev);
}


void make_threaded(node_ptr root){
	node_ptr prev = NULL;
	inorder_thread(root,&prev);	
}

node_ptr leftmost(node_ptr n) {
    while (n && !n->lthread)
        n = n->left;
    return n;
}

void inorder_threaded(node_ptr root) {
    node_ptr curr = leftmost(root);

    while (curr) {
        printf("%d ", curr->value);

        if (curr->rthread)
            curr = curr->right;
        else
            curr = leftmost(curr->right);
    }
}

int main() {
    node_ptr root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(20);
    root->left->left = create_node(3);
    root->left->right = create_node(7);

    make_threaded(root);

    printf("Inorder traversal (threaded): ");
    inorder_threaded(root);
    printf("\n");

    return 0;
}