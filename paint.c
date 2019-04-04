#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point {
    int x, y;
} point;

typedef struct queue {
    int start, end, size;
    point **elements;
} queue;

queue *new_queue(int size);
void delete_queue(queue *q);
void put(queue *q, point *value);
point *get(queue *q);
bool is_empty(queue *q);

void fill(int **image, int n, int x, int y, int color);

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    int **image = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        image[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &image[i][j]);
        }
    }

    int x, y, color;
    for (int i = 0; i < k; i++) {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &color);
        fill(image, n, x, y, color);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
        free(image[i]);
    }
    free(image);
}

queue *new_queue(int size){
	queue * q = malloc(sizeof(queue));
	q->size = size;
	q->start = -1;
	q->end = -1;
	q->elements = malloc(sizeof(point*) * size);
	return q;
}

void delete_queue(queue *q){
	free(q);
}

void put(queue *q, point *value){
	if ((q->start == 0 && q->end == q->size - 1) || q->end == q->start - 1){
		printf("\nYou are silly.\n");
		return;
	}
	else{
		if(is_empty(q)){
			q->start++;
			q->end++;
			*(q->elements) = value;
		}
		else{
			if (q->end < q->size - 1){
				q->end++;
				*(q->elements + q->end) = value;
			}
			else{
				q->end = 0;
				*(q->elements) = value;
			}
		}
	}
}
point *get(queue *q){
	if(!is_empty(q)){
		point * n = *(q->elements + q->start);
		if (q->start == q->end){
			q->start = -1;
			q->end = -1;
		}
		else if (q->start < q->size - 1)
			q->start++;
		else q->start = 0;
		return n;
	}
	else
		printf("\nYou are silly.\n");
}
bool is_empty(queue *q){
	if (q->start == -1)
		return true;
	return false;
}

void fill(int **image, int n, int x, int y, int color) {
    queue *points = new_queue(n * n);
    point * p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    int old_color = image[x][y];
    put(points, p);
   while (!is_empty(points)) {
	   p = get(points);
	   int px = p->x, py = p->y;
	   if (image[px][py] == old_color){
		   image[px][py] = color;
	   	if (py - 1 >= 0) {
			point * temp = malloc(sizeof(point));
		   	temp->x = px;
		   	temp->y = py - 1;
		   	put(points, temp);
	   	}
	   	if (px - 1 >= 0){
			point * temp = malloc(sizeof(point));
		   	temp->x = px - 1;
		   	temp->y = py;
		   	put(points, temp);
	   	}	
	   	if (py + 1 < n){
			point * temp = malloc(sizeof(point));
		   	temp->x = px;
		   	temp->y = py + 1;
		   	put(points, temp);
	   	}
	   	if (px + 1 < n){
			point * temp = malloc(sizeof(point));
		   	temp-> x = px + 1;
		   	temp->y = py;
		   	put(points, temp);
	   	}
	   }
    }

   
    delete_queue(points);
}

