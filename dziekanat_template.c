#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char MAX_NAME_SIZE = 30;

typedef struct node {
    struct node *left, *right, *parent;
    int number;
    char* name;
} node;

node* create_node(int number, char* name);
void delete_tree(node* root);
node* insert (node* root, node* to_insert);
node* find (node* root, int number);
node* delete(node* root, int number);
node* successor(node* x);
node* tree_min(node* t);

int main() {
    int n, r, f;
    scanf("%d", &n);
    scanf("%d", &r);
    scanf("%d", &f);

    node* root = NULL;
    int number;
    char* name = malloc(MAX_NAME_SIZE*sizeof(char));

    while (n-- > 0) {
        scanf("%d", &number);
        scanf("%s", name);
        root = insert(root, create_node(number, name));
    }

    while (r-- > 0) {
        scanf("%d", &number);
        root = delete(root, number);
    }

    while (f-- > 0) {
        scanf("%d", &number);
        node* x = find(root, number);
        printf("%s\n", x == NULL ? "NOTFOUND" : x->name);
    }

    delete_tree(root);
    free(name);
}

node* create_node(int number, char* name){
        node * p = malloc(sizeof(node));
        p->number = number;
	p->name = name;
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

node* insert (node* root, node* to_insert){
        node* p = root;
        node* q = NULL;
        while (p != NULL){
                q = p;
                if (to_insert->number < p->number)
                        p = p->left;
                else
                        p = p->right;
        }
        to_insert->parent = q;
        if (q == NULL)
                root = to_insert;
        else if (to_insert->number < q->number)
                q->left = to_insert;
        else
                q->right = to_insert;
	return root;
}

node* find (node* root, int number){
	if (root == NULL || root->number == number)
		return root;
	if (root->number < number)
		return find(root->left, number);
	else 
		return find(root->right, number);
}

node* delete(node* root, int number){
	node* z = find(root, number);
	if (z == NULL)
		return root;
	node* y;
	node* x;
	if (z->left == NULL || z->right == NULL)
		y = z;
	else
		y = successor(z);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y != z){
		z->name = y->name;
		z->number = y->number;
	}
	free(y);
	return root;
}

node* successor(node* x){
	if (x->right != NULL)
		return tree_min(x->right);
	node* y = x->parent;
	while (y != NULL && x == y->right){
		x = y;
		y = y->parent;
	}
	return y;
}

node* tree_min(node* t){
	node* x = t;
	while (x->left != NULL)
		x = x->left;
	return x;
}



