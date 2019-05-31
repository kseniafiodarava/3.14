#include <iostream>
#include <stack>


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
 
bool find_cycle_from(Node** graph, color* visited, int n, int x) {
    stack<int> st;
    st.push(x);
    bool* recStack = new bool[n];
    for (int i = 0; i < n; i++)
	    recStack[i] = false;
    Node* p;
    int it;
    while (!st.empty()){
	        it = st.top();
		st.pop();
		p = graph[it];
		visited[it] = gray;
		recStack[it] = true;
		while (p != NULL){
			if (visited[p->n] == white)
				st.push(p->n);
			else if (recStack[p->n]){
				delete [] recStack;	
				return true;	
			}
    			p = p->next;
		}
    }
    visited[it] = black;
    recStack[it] = false;
    delete [] recStack;
    return false;
}

bool has_cycle(Node** graph, int n) {
    color visited[n];
    for (int i=0; i<n; i++) visited[i] = white;
    for(int i = 0; i<n; i++) {
        if (visited[i] == white) {
            if (find_cycle_from(graph, visited, n, i)) return true;
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
