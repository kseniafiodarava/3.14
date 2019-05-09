#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node *left, *right, *parent;
    int value;
} node;


node* create_node(int val); 
void delete_tree(node* root);
void insert (node* root, node* to_insert);
void print_in_order(node* root);

int main() {
    int n;
    scanf("%d", &n);
    node* root = NULL;
    int val;

    if (n-- > 0) {
        scanf("%d", &val);
        root = create_node(val);
    }
    while (n-- > 0) {
        scanf("%d", &val);
        insert(root, create_node(val));
    }

    print_in_order(root);

    delete_tree(root);
}

node* create_node(int val){
	node * p = malloc(sizeof(node));
	p->value = val;
	p->left = NULL;
	p->right = NULL;
	p->parent = NULL;
	return p;
}

void delete_tree(node* root){
	if (root == NULL) return;
	else {
		delete_tree(root->right);
		delete_tree(root->left);
	}
	free(root);
}

void insert (node* root, node* to_insert){
	node* p = root;
	node* q = NULL;
	while (p != NULL){
		q = p;
		if (to_insert->value < p->value)
			p = p->left;
		else
			p = p->right;
	}
	to_insert->parent = q;
	if (q == NULL)
		root = to_insert;
	else if (to_insert->value < q->value)
		q->left = to_insert;
	else 
		q->right = to_insert;
}

void print_in_order(node* root){
	if (root == NULL) return;
	print_in_order(root->left);
	printf("%d\n", root->value);
	print_in_order(root->right);
}

