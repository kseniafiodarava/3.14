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

typedef enum entry_type {number, add, subtract, multiply, divide} entry_type;

entry_type parse(char* raw);
void do_add(stack* s);
void do_subtract(stack* s);
void do_multiply(stack* s);
void do_divide(stack* s);
int read_and_calculate(int operands_count, int max_entry_size);
int get_num(char a[]);
int pow(int a, int b);

int main() {
    int operands_count, max_entry_size;
    scanf("%d", &operands_count);
    scanf("%d", &max_entry_size);
    printf("%d\n", read_and_calculate(operands_count, max_entry_size));
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


entry_type parse(char* raw) {
    if (raw[0] == '+') return add;
    if (raw[0] == '-') return subtract;
    if (raw[0] == '*') return multiply;
    if (raw[0] == '/') return divide;
    return number;
}

int read_and_calculate(int operands_count, int max_entry_size) {
    stack* operands = new_stack(operands_count);
    char* entry = malloc((max_entry_size+1)*sizeof(char));
    int k = 0;
    int n;
    while(k < operands_count) {
        for(int i=0; i<max_entry_size; i++) entry[i] = '\0';
        scanf("%s", entry);
        entry_type t = parse(entry);
	switch(t){
		case add:
			do_add(operands);
			break;
		case subtract:
			do_subtract(operands);
			break;
		case multiply:
			do_multiply(operands);
			break;
		case divide:
			do_divide(operands);
			break;
		case number:
			n = get_num(entry);
			push(operands, n);
			break;
	}
	k++;
    }

    int result = pop(operands);

    delete_stack(operands);
    free(entry);
    return result;
}

void do_add(stack * s){
	int a = pop(s);
	int b = pop(s);
	push(s, a + b);
}

void do_subtract(stack * s){
	int a = pop(s);
	int b = pop(s);
	push(s, b - a);
}

void do_multiply(stack * s){
	int a = pop(s);
	int b = pop(s);
	push(s, a * b);
}

void do_divide(stack * s){
	int a = pop(s);
	int b = pop(s);
	push(s, b / a);
}

int get_num(char * a){
	int dig = 0;
        int i = 0;
        while (a[i] != ' ' && a[i] != '\0'){
         	i++;
                dig++;
        }
        int d = dig - 1;
	int n = 0;
        for (int i = 0; i < dig; i++){
        	n += (a[i] - 48) * pow(10, d);
                d--;
        }
        return n;
}

int pow(int a, int b){
	int res = 1;
	for (int i = 0; i < b; i++)
		res *= a;
	return res;
}
