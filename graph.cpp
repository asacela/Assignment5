#include "graph.h"
#include <stack>
#include <algorithm>


 vector<string>* Node::neighbors() {
   vector<string>* vec = new vector<string>();
   vector<Edge*>::iterator it;
   for(it=adjacents->begin();it!=adjacents->end();it++) {
     vec->push_back((*it)->getNode()->getPayload());
   }
   return vec;
 }


 void Graph::addNode(string name) {
    Node* node = new Node(name);
    graph->insert(pair<string,Node*>(name,node));
 }

 void Graph::addEdge(string k1, string k2, double w=1.0) {
   map<string,Node* >::iterator it1,it2;
   it1 = graph->find(k1);
   it2 = graph->find(k2);

   //Check both nodes exists using the map
   if (it1 != graph->end() && it2 != graph->end()) {
      Node* n1 = (*it1).second;
      Node* n2 = (*it2).second;
      //Create the edge and add it to the adjacents
      Edge* e = new Edge(n2,w);
      n1->addEdge(e);
      //Undirected graph: we add the reverse or back edge
      if (!directed) {
        Edge* be = new Edge(n1,w);
        n2->addEdge(be);
      }
   }
 }


void Graph::printGraph() {
   //Iterate each node
  map<string,Node* >::iterator it;
  for (it=graph->begin(); it != graph->end();it++) {

    Node* n = it->second;
    cout << n->getPayload() << "[";
    
    //Iterate the neighboors
    vector<string>* neigh  = n->neighbors(); 
    vector<string>::iterator itn;
    for(itn=neigh->begin();itn!=neigh->end();itn++) {
       cout << (*itn) << " ";
    }
    cout << "]" << endl;
  }
}

//TODO: redo & check neighbors of vertex to see if they are connected
bool Graph::IsThereTripletClique(){

  //if undirected, count nodes in row
  if(!directed){

    map<string,Node* >::iterator iter_map;
    for (iter_map=graph->begin(); iter_map != graph->end();iter_map++) {

      Node* n = iter_map->second;
      vector<Edge* >* adj = n->adjacentsList();

      for(vector<Edge*>::iterator it1=adj->begin();it1!=adj->end();it1++) {

        vector<Edge*>::iterator it2;
        vector<Edge*>::iterator temp = it1 + 1;
        
        if((it1+1)!=adj->end()){
        }
        else{

          vector<Edge* >* adj2 = (*temp)->getNode()->adjacentsList();
          it2 = find(adj2->begin(), adj2->end(), (*it1));
        }
        if(*it2 == *it1){ 
          
          return true;
        }
      }
    }
  }
  return false;
}

//do this one last
double Graph::GetMinDistance(string city1,string city2){

  Dijkstra();

  return 2.0;
}


//start with this function, not since DFS not done
bool Graph::isGraphConnected(){

  cout << "Before DFS:" << endl;

  //iterate map to set all to false
  map<string,Node* >::iterator it;
  for (it=graph->begin(); it != graph->end();it++) {

    Node* n = it->second;
    n->setVisited(false);
    cout << n->getPayload();
    if(!n->isVisited()){
      cout << " - not visited" << endl;
        
    }
   
  }

  //set source as first in map
  map<string,Node* >::iterator it1 = graph->begin();
  Node* s = it1->second;

  //DFS
  DFS(s);

  cout << "After DFS:" << endl;

  //Check to see if any visited any node is false
  map<string,Node* >::iterator it_1;
  for (it_1=graph->begin(); it_1 != graph->end();it_1++) {

    Node* n = it_1->second;
    cout << n->getPayload() << endl;
    if(!n->isVisited()){

        cout << " - not visited" << endl;
        return false;
    }
  }

  return true;
}


//helper functions

//use in graphConnected
void Graph::DFS(Node *s){

  stack<Node*> dfs_Stack;

  dfs_Stack.push(s);

  while(!dfs_Stack.empty()){

    Node* current = dfs_Stack.top();
    dfs_Stack.pop();

    if(!current->isVisited()){

      current->setVisited(true);
      vector<Edge* >* adj = current->adjacentsList();
      vector<Edge*>::iterator it;
      for(it=adj->begin();it!=adj->end();it++) {

        dfs_Stack.push((*it)->getNode());
      }
    }
  } 
}

//use in Getmindistance
void Graph::Dijkstra(){


}


int main() {
  cout << "Graph Example 2.0\n";
  Graph g(false);
  
  g.addNode("a");
  g.addNode("b");
  g.addNode("c");
  g.addNode("d");

  g.addEdge("a","b",10);
  g.addEdge("b","c",5);
  g.addEdge("c","a",9);


  g.printGraph();

  cout << "Graph is Connected: " << endl;
  if(g.isGraphConnected()){

    cout << "True" << endl;
  }
  else{

    cout << "False" << endl;
  }


}


