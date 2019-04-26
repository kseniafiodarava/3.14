#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Uncomment line with "#define DEBUG" if you want to see your hashtable.
// But rememeber to send only solutions with debug turned off!
// #define DEBUG 1 

#define MAX_CHARS 31

typedef unsigned int uint;

typedef enum states {
	EMPTY = 0,
	OCCUPIED = 1,
	STH_WAS_HERE = 2
} states;

typedef struct Slot {
	char name[MAX_CHARS];
	char phone[MAX_CHARS];
	states state;
} Slot;

uint hashfunc(const char* name);

void add_to_hashtable(Slot** hashtable, int n, const char* name, const char* phone);

char* get_number(Slot** hashtable, int n, const char* name);

void remove_from_hashtable(Slot** hashtable, int n, const char* name);

void free_memory(Slot** hashtable, int n);

void debug_print_hashtable(Slot** hashtable, int n) {
	#ifdef DEBUG
		for (int i = 0; i < n; i++) {
			printf("%d: [%d] %s\n", i, hashtable[i]->state, hashtable[i]->name);
		}
		printf("\n");
	#endif
}

int main() {
    int Z;
    scanf("%d", &Z);

	while (Z--) {
		int n, k;
		char op;
		char tmp_name[MAX_CHARS], tmp_phone[MAX_CHARS];

        scanf("%d", &n);
        scanf("%d", &k);
		int size = n * 3;

		Slot** hashtable = (Slot**)calloc(size, sizeof(Slot*));

		for (int i = 0; i < size; i++) {
			hashtable[i] = (Slot*) malloc(sizeof(Slot));
			hashtable[i]->state = EMPTY;
		}

		for (int i = 0; i < k; i++) {
			do { scanf("%c", &op); } while(isspace(op));
			switch(op) {
				case 'a':
                    scanf("%s", tmp_name);
                    scanf("%s", tmp_phone);
					add_to_hashtable(hashtable, size, tmp_name, tmp_phone);
					break;
				case 'r':
                    scanf("%s", tmp_name);
					remove_from_hashtable(hashtable, size, tmp_name);
					break;
				case 'g':
                    scanf("%s", tmp_name);
					char* num = get_number(hashtable, size, tmp_name);
					printf("%s\n", num ? num : "");
					break;
			}
			debug_print_hashtable(hashtable, size);
		}
		free_memory(hashtable, size);
	}
}

uint hashfunc(const char* name){
	int i = 0;
        uint n = 0;
        while (name[i]){
                n += name[i];
                i++;
        }
        n *= i;
        return n;
}
	

void add_to_hashtable(Slot** hashtable, int n, const char* name, const char* phone) {
        uint hash = hashfunc(name) % n;
        while (hashtable[hash]->state == OCCUPIED)
        	hash++;
        hashtable[hash]->state = OCCUPIED;
        strcpy(hashtable[hash]->name, name);
        strcpy(hashtable[hash]->phone, phone);
}

char* get_number(Slot** hashtable, int n, const char* name) {
        if (n == 0) return NULL;
        uint hash = hashfunc(name) % n;
	while (hash < n && strcmp(hashtable[hash]->name, name) != 0)
		hash++;
	if (hash < n)
		return hashtable[hash]->phone;
	return "[empty]";
}

void remove_from_hashtable(Slot** hashtable, int n, const char* name) {
        uint hash = hashfunc(name) % n;
	while (hash < n && strcmp(hashtable[hash]->name, name) != 0)
		hash++;
	if (hash < n){
		strcpy(hashtable[hash]->name, "");
		strcpy(hashtable[hash]->phone, "");
        	hashtable[hash]->state = STH_WAS_HERE;	
	}
}


void free_memory(Slot** hashtable, int n) {
        for (int i = 0; i < n; i++) {
                free(hashtable[i]);
        }
        free(hashtable);
}

