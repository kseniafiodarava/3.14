#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Uncomment line with "#define DEBUG" if you want to see your hashtable.
// But rememeber to send only solutions with debug turned off!
// #define DEBUG 1 
#define MAX_CHARS 30

typedef unsigned int uint;

typedef struct Node {
	char text[MAX_CHARS];
	struct Node *next;
} Node;

uint hashfunc(const char* txt);

void add_to_hashtable(Node** hashtable, int n, const char* txt);
	// use strcpy() for copying strings

bool check_if_exists(Node** hashtable, int n, const char* txt);

void free_memory(Node** hashtable, int n);

void debug_print_hashtable(Node** hashtable, int n) {
	#ifdef DEBUG
		Node* ptr;	
		for (int i = 0; i < n; i++) {
			printf("%d: ", i);
			ptr = hashtable[i];
			while (ptr != NULL) {
				printf("%s | ", ptr->text);
				ptr = ptr->next;
			}
			printf("\n");
		}
	#endif
}

int main() {
    int Z;
    scanf("%d", &Z);

	while (Z--) {
		int n, k;
		char tmp[MAX_CHARS];

        scanf("%d", &n);
        scanf("%d", &k);

		Node** hashtable = (Node**)calloc(n, sizeof(Node*));

		for (int i = 0; i < n; i++)
			hashtable[i] = NULL;

		for (int i = 0; i < n; i++) {
			scanf("%s", tmp);
			add_to_hashtable(hashtable, n, tmp);
		}

		debug_print_hashtable(hashtable, n);

		for (int i = 0; i < k; i++) {
			scanf("%s", tmp);
			if (check_if_exists(hashtable, n, tmp)) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
		free_memory(hashtable, n);
	}
}

uint hashfunc(const char* txt){
	int i = 0;
	uint n = 0;
	while (txt[i]){
		n += txt[i];
		i++;
	}
	n *= i;
	return n;
}

void add_to_hashtable(Node** hashtable, int n, const char* txt){
	int i = hashfunc(txt) % n;
	Node * p = malloc(sizeof(Node));
	p->next = NULL;
	strcpy(p->text, txt);
	if (hashtable[i] == NULL)
		hashtable[i] = p;
	else{
		Node * q = hashtable[i];
		while (q->next != NULL) 
			q = q->next;
		q->next = p;
	}
}

bool check_if_exists(Node** hashtable, int n, const char* txt){
	int i = hashfunc(txt) % n;
	Node * p = hashtable[i];
	while (p != NULL){
		if (strcmp(txt, p->text) == 0) 
			return true;
		p = p->next;
	}
	return false;
}


void free_memory(Node** hashtable, int n){
	for (int i = 0; i < n; i++){
		Node * p = hashtable[i];
		Node * q;
		while (p != NULL){
			q = p->next;
			free(p);
			p = q;
		}
	}
}

