#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX_TEXT_LENGTH = 200;

int distance(char* a, int a_length, char* b, int b_length);

int main() {
    char* a = malloc(MAX_TEXT_LENGTH*sizeof(char));
    char* b = malloc(MAX_TEXT_LENGTH*sizeof(char));
    scanf("%[^\n]", a);
    scanf("%c\n", b); // reads \n
    scanf("%[^\n]", b);
    printf("%d\n", distance(a, strlen(a), b, strlen(b)));
}

int distance(char* a, int a_length, char* b, int b_length){
	int i = 0;
	int j = 0;
	int count = 0;
	int new_b_len = b_length;
	while (i < a_length && j < b_length){
		if (a[i] == b[j]){
			i++;
			j++;
		}
		else if (a[i + 1] == b[j]){
			count++;
			j++;
			i += 2;
			new_b_len++;
		}
		else if (a[i] == b[j + 1]){
			count++;
			j += 2;
			i++;
			new_b_len--;
		}
		else if (a[i] != b[j]){
			count++;
			i++;
			j++;
		}
	}	
	if (new_b_len < a_length)
		for(i = i; i < a_length; i++)
			if (a[i] != " ")
				count++;
	else if (new_b_len > a_length)
		for (j = j; j < b_length; j++)
			if (b[j] != " ")
				count++;
	return count;
}

