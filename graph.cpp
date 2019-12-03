#include "graph.h"
#include <stack>

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const string ALPHA_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


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

        //cout << "Checking these nodes: ";
        //cout << (*it1)->getNode()->getPayload();
        if(temp != adj->end()){
          //cout << (*temp)->getNode()->getPayload();
        }
        //cout << endl;
        
        
        
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

//do this one last
double Graph::GetMinDistance(string city1,string city2){

  //Dijkstra goes here

  return 2.0;
}


//start with this function, not since DFS not done - Complexity O(n + m)
bool Graph::isGraphConnected(){

  //cout << "Before DFS:" << endl;

  //iterate map to set all to false
  map<string,Node* >::iterator it;
  for (it=graph->begin(); it != graph->end();it++) {

    Node* n = (*it).second;
    n->setVisited(false);
    //cout << n->getPayload();
    if(!n->isVisited()){
      //cout << " - not visited" << endl;
        
    }
   
  }

  //set source as first in map
  map<string,Node* >::iterator it1 = graph->begin();
  Node* s = it1->second;

  //DFS
  DFS(s);

  //cout << "After DFS:" << endl;

  //Check to see if any visited any node is false
  map<string,Node* >::iterator it_1;
  for (it_1=graph->begin(); it_1 != graph->end();it_1++) {

    Node* n = it_1->second;
    //cout << n->getPayload() << endl;
    if(!n->isVisited()){

        //cout << " - not visited" << endl;
        return false;
    }
  }

  return true;
}

int Graph::LongestSimplePath(){
  /*
  //Source Node
  map<string,Node* >::iterator iter_map = graph->begin();
  Node* s = iter_map->second;

  int current_len = 0;


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
        if(!((*it)->getNode()->isVisited())){
          dfs_Stack.push((*it)->getNode());
        }
      }
    }
  } */
  return 1;
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
        if(!((*it)->getNode()->isVisited())){ 
          dfs_Stack.push((*it)->getNode());
        }
      }
    }
  }
}

//use in Getmindistance
void Graph::Dijkstra(Node* startV){
  map<string,Node*>::iterator it;

  for(it = graph->begin(); it != graph->end();++it){
    //(*it)->setVisited(false); //commented out because gives compilation errors
  }


}

string Graph::getRandString(){
  
  string randomString = "";
  for(int i = 0; i < 10; ++i){

    randomString += ALPHA_CHARS[rand() % ALPHA_CHARS.length()];
  }
  return randomString;
}

//make a better test function
void Graph::generateTestGraph(){

  map<string,Node* >::iterator it;

  //finish 500 one

  for(int i = 0; i < 100; ++i){
    string randString = getRandString();
    addNode(randString);

  }

  for(int i = 0; i < 500; ++i){
      it = graph->begin();
      advance(it, rand() % 100);
      addEdge(it->first, getRandString(), 1);

  }

  for(int i = 0; i < 500; ++i){
      it = graph->begin();
      advance(it, rand() % 100);
      addEdge(it->first, getRandString(), 2);

  }

  for(int i = 0; i < 500; ++i){
      it = graph->begin();
      advance(it, rand() % 100);
      addEdge(it->first, getRandString(), 3);

  }

}




int main() {
  /*********************
    Given Test Harness
  **********************/
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
  cout << endl << endl;


  //isGraphConnected
  cout << "Graph is Connected: " << endl;
  if(g.isGraphConnected()){

    cout << "True" << endl;
  }
  else{

    cout << "False" << endl;
  }
  cout << endl << endl;

  //isTripletClique
  cout << "Triplet Clique: " << endl;
  if(g.IsThereTripletClique()){

    cout << "True" << endl;
  }
  else{

    cout << "False" << endl;
  }
  cout << endl << endl;

  /*********************
    Custom Test Harness
  **********************/
  cout << "Testing Graph:" << endl;
  Graph g2(false);
  int elapsedTime;

  g2.generateTestGraph();

  //isGraphConnected
  clock_t Start = clock();

  bool isConnected = g2.isGraphConnected();

  cout << "GraphConnected: " << endl;
  if(isConnected){

    cout << "True" << endl;
  }
  else{

    cout << "False" << endl;
  }

  clock_t End = clock();
  elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
  cout << "isGraphConnected Elapsed Time: " << elapsedTime << endl;

  //isTripletClique
  Start = clock();

  bool triplet = g2.IsThereTripletClique();

  cout << "Triplet Clique: " << endl;
  if(triplet){

    cout << "True" << endl;
  }
  else{

    cout << "False" << endl;
  }

  End = clock();
  elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
  cout << "isTripletClique Elapsed Time: " << elapsedTime << endl;



}
