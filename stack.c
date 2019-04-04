#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct stack {
    int* elements;
    int top;
    int max_size;
} stack;

void push(stack* s, int n);
int pop(stack* s);
bool is_empty(stack* s);
stack* new_stack(int size);
void delete_stack(stack* s);
    
int main() {
    int size;
    scanf("%d", &size);
    stack* s = new_stack(size);
    int temp;

    for (int i = 0; i < size; i++){
	scanf("%d", &temp);
        push(s, temp);
    }
    for (int i = 0; i < size; i++)
	printf("%d\n", pop(s));

    delete_stack(s);
}

stack* new_stack(int size){
	int* arr = malloc(sizeof(int) * size);
	stack* s = malloc(sizeof(stack));
	s->elements = arr;
	s->top = -1;
	s->max_size = size;
	return s;
}

void push(stack * s, int n){
	if (s->top == s->max_size - 1){
		printf("\nYou are silly.\n");
		return;
	}
	else{
		s->top++;
		*(s->elements + s->top) = n;
	}
}

int pop (stack * s){
	if (s->top < 0){
		printf("\nYou are silly.\n");
		return INT_MIN;
	}
	else{
		int n = *(s->elements + s->top);
		s->top--;
		return n;
	}
}	

bool is_empty(stack * s){
	if (s->top < 0) return true;
	return false;
}

void delete_stack(stack * s){
	free(s);
}
