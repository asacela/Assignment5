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
        vector<Edge*>::iterator temp;
        if(it1 != adj->end()){
          temp = it1 + 1;
        }

        cout << "Checking these nodes: ";
        cout << (*it1)->getNode()->getPayload();
        if(temp != adj->end()){
          cout << (*temp)->getNode()->getPayload();
        }
        cout << endl;



        if(temp==adj->end()){
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


//start with this function, not since DFS not done
bool Graph::isGraphConnected(){

  cout << "Before DFS:" << endl;

  //iterate map to set all to false
  map<string,Node* >::iterator it;
  for (it=graph->begin(); it != graph->end();it++) {

    Node* n = (*it).second;
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

//do this one last
double Graph::GetMinDistance(string city1,string city2){
  Node* v1 = nullptr;
  Node* v2 = nullptr;
  map<string,Node*>::iterator it;
  for(it = graph->begin(); it != graph->end();++it){
    if(it->first == city1){
      v1 = it->second;
    }
    if(it->first == city2){
      v2 = it->second;
    }
  }
  return Dijkstra(v1,v2);
}

//use in Getmindistance
double Graph::Dijkstra(Node* v1,Node* v2){
  const int INF = 500000;
  map<string,Node*>::iterator it;
  vector< pair<Node*,double> > dist;
  list< pair<Node*,double>* > unvisited;


  int N = 0;
  // Populate "dist" vector and set all Nodes in graph to unvisited
  for(it = graph->begin(); it != graph->end(); ++it){
    // pair<node,minDistance>
    pair<Node*,double> vertice(it->second,INF);
    dist.push_back(vertice);

    it->second->setVisited(false);
    // Starting vertice has distance 0 and is visited
    if(it->second == v1){
      dist.at(N).first->setVisited(true);
      dist.at(N).second = 0;
    }
    ++N;
  }

  // Populate "unvisited" list
  pair<Node*,double>* data = dist.data();
  for(unsigned i = 0; i < dist.size(); ++i){
    unvisited.push_front(data);
    ++data;
  }

  // Till unvisited is empty
  while(!unvisited.empty()){
    // Find smallest
    pair<Node*,double>* curr = findMin(unvisited);
    curr->first->setVisited(true);

    list< pair<Node*,double>* >::iterator it1;
    it1 = find(unvisited.begin(), unvisited.end(), curr);
    if(it1 != unvisited.end()){
      unvisited.erase(it1);
    }

    // For each curr's adj nodes
    for(int i = 0; i < curr->first->degree(); ++i){
      if(!(curr->first->adjacentsList()->at(i)->getNode()->isVisited())){
        double edgeWeight = curr->first->adjacentsList()->at(i)->getWeight();
        double pathWeight = curr->second + edgeWeight;

        // Find current distance of "adjNode" (AKA "adjDistance")
        Node* adjNode = curr->first->adjacentsList()->at(i)->getNode();
        double adjDistance = INF;
        bool found = false;
        for(unsigned i = 0; i < dist.size() && !found; ++i){
          if(dist.at(i).first == adjNode){
            adjDistance = dist.at(i).second;
            found = true;
          }
        }

        // If pathWeight smaller than adjNode's current distance
        if(pathWeight < adjDistance){
          pair<Node*,double> adjVertice(adjNode,adjDistance);
          vector< pair<Node*,double> >::iterator it1;
          it1 = find(dist.begin(),dist.end(),adjVertice);
          it1->second = pathWeight;
        }

      }
    }
  }
  vector< pair<Node*,double> >::iterator it2;
  for(it2 = dist.begin(); it2 != dist.end(); ++it2){
    if(it2->first == v2){
      return it2->second;
    }
  }
  return INF;
}

pair<Node*,double>* Graph::findMin(list< pair<Node*,double>* >& List){
  list< pair<Node*,double>* >::iterator it;
  pair<Node*,double>* min = List.front();
  for(it = List.begin(); it != List.end(); ++it){
    if((*it)->second < min->second){
      min = *it;
    }
  }
  return min;
}



int main() {
  cout << "Graph Example 2.0\n";
  Graph g(false);

  g.addNode("a");
  g.addNode("b");
  g.addNode("c");
  //g.addNode("d");

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
  cout << endl;

  cout << "Triplet Clique: " << endl;
  if(g.IsThereTripletClique()){

    cout << "True" << endl;
  }
  else{

    cout << "False" << endl;
  }
  cout << endl;
  cout << g.GetMinDistance("a","c");

}
