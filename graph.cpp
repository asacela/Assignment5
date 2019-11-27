#include "graph.h"
#include <stack>


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

    Node* n = (*it).second;
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

//This is wrong
//TODO: redo & check neighbors of vertex to see if they are connected
bool Graph::IsThereTripletClique(){

  //if undirected, count nodes in row
  if(!directed){

    int element_count = 0;
    map<string,Node* >::iterator it;
    for (it=graph->begin(); it != graph->end();it++) {

      Node* n = (*it).second;
      vector<string>* neigh  = n->neighbors(); 
      vector<string>::iterator itn;

      for(itn=neigh->begin();itn!=neigh->end();itn++) {
       
        element_count += 1;
      }

      if(element_count == 3){

        return true;
      }
    }
  }
  else if(directed){

    //if directed is needed, implement here
  }
  

  return false;
}

//do this one last
double Graph::GetMinDistance(string city1,string city2){



  return 2.0;
}


//start with this function, not since DFS not done
bool Graph::isGraphConnected(){

  
  DFS(graph->begin());

  map<string,Node* >::iterator it;
  for (it=graph->begin(); it != graph->end();it++) {

    Node* n = (*it).second;
    vector<string>* neigh  = n->neighbors(); 
    vector<string>::iterator itn;

    for(itn=neigh->begin();itn!=neigh->end();itn++) {
     
      if(!it->isVisited()){

        return false;
      }
    }
  }

  return true;
}




//helper functions - need to define & stuff

//use in graphConnected
void Graph::DFS(Node s){

  stack<Node s> dfs_Stack;

  dfs_Stack.push_back(s);

  while(!dfs_Stack.empty()){

    Node current = dfs_Stack.top();
    dfs_Stack.pop();

    if(current.isVisited()){

      current.setVisited(true);
      vector<Edge*>* adjacentsList = n->neighbors(); 


    }
  }

  

}

//use in Getmindistance
void Graph::Dijkstra(){

}

//come up with function to create a adjacency vector

void Graph::CreateNodeTable(){

  map<string,Node* >::iterator it;
  for (it=graph->begin(); it != graph->end();it++) {

    

  }
}


int main() {
  cout << "Graph Example 2.0\n";
  Graph g(false);
  
  g.addNode("a");
  g.addNode("b");
  g.addNode("c");

  g.addEdge("a","b",10);
  g.addEdge("b","c",5);
  g.addEdge("c","a",9);


  g.printGraph();

}


