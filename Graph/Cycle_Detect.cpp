#include <iostream>
using namespace std;
#include <list>

class Graph {

  list<int> *l;
  int V;

  public:
    Graph(int V){
      this->V = V;
      l = new list<int>[V];
    }

  void addEdge(int x, int y, bool directed = true){
    l[x].push_back(y);
    // if(!directed) { // uncomment line 18 & 20 if you want to make it directed
       l[y].push_back(x);
    // }
  }

  bool cycle_helper(int node, bool *visited, int parent){
    visited[node] = true;
    for(auto nbr: l[node]){
      // two cases
      if(!visited[nbr]){
        // go and recursively visit the the nbr
        bool cycle_found = cycle_helper(nbr, visited, node);
        if(cycle_found){
          return true;
        }
      }
      // nbr is visited but nbr should not be euqual to parent.
      else if (nbr != parent){
        return true;
      }
    }
    return false;
  }

  bool contains_cycle(){
    // Check for cycle in directed graph
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++){
        visited[i] = false;
    }
    return cycle_helper(0, visited, -1);
  }
};

int main(){
  Graph g(5);

  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 4);
  g.addEdge(4, 0); // Comment this line and it'll not have a cycle

  if (g.contains_cycle()) {
    cout << "Yes undirected graph contains cycle";
  }
  else {
    cout << "Doesn't contain cycle";
  }
  return 0;
}