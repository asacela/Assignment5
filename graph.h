#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
using namespace std;

class Edge;

//Node
class Node {
public:
 Node(const string& elem):payload(elem),visited(false){
    adjacents = new vector<Edge* >();
  };
  ~Node() {};
  void   setVisited(bool v)        {visited = v;};
  bool    isVisited()              {return visited;};
  void   addEdge(Edge* e)    {

    adjacents->push_back(e);};
  int    degree()  const           {return adjacents->size();};
  string getPayload() const        {return payload;}
  vector<string>*  neighbors();
  vector<Edge* >*  adjacentsList()     {return adjacents;};
private:
  string        payload;
  bool          visited;
  vector<Edge* >* adjacents;
};


//Edge
class Edge {
public:
  Edge(Node* n, double w):node(n),weight(w){};
  ~Edge() {};
  void      setWeight(double w)  {weight=w;};
  Node*     getNode()   const    {return node;};
  double    getWeight() const    {return weight;};
private:
  Node*  node;
  double weight;
  friend class Node;
};


//Graph
class Graph {
public:
  Graph(bool directed):directed(directed){
    graph = new map<string,Node*>();
  };

  ~Graph() {
    delete graph;
   };

  //DO NOT CHANGE THE FOLLOWING METHODS
  void addNode(string node);
  void addEdge(string nid1 , string nid2, double w);
  void printGraph();

  //Homework
  bool IsThereTripletClique();
  double GetMinDistance(string city1,string city2);
  bool isGraphConnected();
  int LongestSimplePath();

  //Helper Functions
  void DFS(Node *s);
  double Dijkstra(Node*,Node*);
  pair<Node*,double>* findMin(list< pair<Node*,double>* >&);
  void generateTestGraph();
  string getRandString();

  
private:
  map<string,Node*>* graph;
  bool directed;
};
