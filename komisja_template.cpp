#include <iostream>

using namespace std;

typedef struct Node {
    int n;
    struct Node* next;
} Node;

enum color {
    white,
    gray,
    black
};

int count = 0;


void print (color* a, int n){
	for (int i = 0; i < n; i++)
		cout << a[i] << "    ";
	cout << endl;
}
 
bool find_cycle_from(bool* recStack, Node** graph, color* visited, int n, int x) {
    visited[x] = gray;
    recStack[x] = true; 
    Node* p = graph[x];
    while (p!= NULL){
	if (visited[p->n] == white && find_cycle_from(recStack, graph, visited, n, p->n))
		return true;
	else if (recStack[p->n])	
		return true;	
    	p = p->next;
    }
    visited[x] = black;
    recStack[x] = false;
    return false;
}

bool has_cycle(Node** graph, int n) {
    color visited[n];
    for (int i=0; i<n; i++) visited[i] = white;
    bool * recStack = new bool[n];
    for (int i = 0; i < n; i++)
	    recStack[i] = false;
    for(int i = 0; i<n; i++) {
        if (visited[i] == white) {
            if (find_cycle_from(recStack,graph, visited, n, i)) return true;
        }
    }
    return false;
}

int main() {
    int n, k;
    cin >> n;
    Node **graph = new Node*[n];
    cin >> k;
    for(int i=0; i<k; i++) {
        Node* tmp = new Node;
        int x, y;
        cin >> x;
        cin >> y;
        tmp->n = y;
        tmp->next = graph[x];
        graph[x] = tmp;
    }
    cout << (has_cycle(graph, n) ? "CYKL" : "OK") << endl;
}
