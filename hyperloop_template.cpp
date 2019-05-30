#include <iostream>

using namespace std;

typedef struct Node {
    int n;
    struct Node* next;
} Node;

void print(int* components, int n){
        cout << "components:  ";
        for (int i = 0; i < n; i++)
                cout << components[i] << "    ";
        cout << endl;
}


void dfs(Node** graph, int* components, int n, int i, int component_no) {
    components[i] = component_no;
    Node* p = graph[i];
    while (p != NULL){
	    if (components[p->n] != component_no){
		    components[p->n] = component_no;
		    dfs(graph, components, n, p->n, component_no);
	    }
	    p = p->next;
    }
}

int* count_components(Node** graph, int n) {
    int* components = new int[n];
    for(int i=0; i<n; i++) components[i] = -1;
    int counter = 0;
    for (int i = 0; i < n; i++)
	    if (components[i] == -1){
		counter++;
		dfs(graph, components, n, i, counter);
	    }
    return components;
}

int main() {
    int n, k, p;
    cin >> n;
    Node **graph = new Node*[n];
    cin >> k;
    cin >> p;
    for (int i=0; i<k; i++) {
        Node *tmp1 = new Node, *tmp2 = new Node;
        int x, y;
        cin >> x;
        cin >> y;
        tmp1->n = y;
        tmp1->next = graph[x];
        graph[x] = tmp1;
        tmp2->n = x;
        tmp2->next = graph[y];
        graph[y] = tmp2;
    }
    int* components = count_components(graph, n);
    for (int i=0; i<p; i++) {
        int x, y;
        cin >> x;
        cin >> y;
        cout << (components[x] == components[y] ? "TAK" : "NIE") << endl;
    }
}
