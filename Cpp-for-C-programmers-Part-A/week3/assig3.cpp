/*
  Week 3   - by Bruce Geng

  Homework 2: "Implement Dijkstra's Algorithm"

  Implement a Monte Carlo simulation that calculates the average shortest path in a graph. 
  The graph can be generated using a pseudo-random number generator to produce edges and their costs. 
  The shortest path algorithm will be Dijkstra’s.
  
  Notes and Reminders:

  1. Write a set of constructors for declaring and initializing a graph. 
  2. An edge will have a positive cost that is its distance.
     Have a procedure that produces a randomly generated set of edges with positive distances.  

  Assume the graphs are undirected. The random graph procedure should have edge density as a parameter and distance range as a parameter. 
  So a graph whose density is 0.1 would have 10% of its edges picked at random and its edge distance would be selected at random from the distance range. 
  
  The procedure should run through all possible undirected edges, say (i,j) and place the edge in the graph if a random probability calculation is less than the density. 
  Compute for a set of randomly generated graphs an average shortest path.

  Turn in:  Printout of program, 200 words on what you learned, and output showing the average path length calculation. 
  Use densities: 20% and 40% on a graph of 50 nodes with a distance range of 1.0 to 10.0.   
  To get an average path length, compute the 49 paths: 1 to 2, 1 to 3, 1 to 4, …, 1 to 50. 
*/

#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<ctime>
#include<cstdlib>
using namespace std;

/* 
  ----------------------------------------------------------------
          Overload operator '<<' to print list<char>
  ----------------------------------------------------------------
*/
ostream &operator<<(ostream &output, list<char> L)
{
   list<char>::iterator i;
   for(i=L.begin(); i != L.end(); ++i)
     output << *i << " ";
   return output;
}



// INFINIT is used to represent no edge between two nodes 
const int INFINIT = 999999;


// convert node numbers into chars (from 0..51 to A..Za..z)
inline char convIntToChar(int n)
{
  if (n<26)
    return static_cast<char>('A'+n);
  else
    return static_cast<char>('a'+n-26);
}


// nodes definition
typedef struct strNode Node;
struct strNode
{
  int number;	
  int weight;	
  list<Node> edges;	
};


/*
  --------------------------------------------------------------------------
       Define Graph Class to represent a Graph through an adjacency list
  --------------------------------------------------------------------------
*/

class Graph
{
  public:
    Graph();   // constructor
    Graph(int numVert, int initVal); // constructor with two parameters (numerVertices, initialValue)

    char get_node_value(int x);
    void set_node_value(char x, char name);
    int get_edge_value(char x, char y);
    void set_edge_value(char x, char y, int value);

    bool adjacent(char x, char y);
    list<char> neighbors(char x);

    int V();
    int E();
    list<char> vertices();

    void show();
  
  private:
    int numV;			// no. of nodes of the Graph
    int numE;			// no. of edges of the Graph

    vector<char> nodeNames;	     // map node numbers into node names
    map<char, int> nodeNumbers;	 // map node names into node numbers
    list<Node> adjList;		       // adjacency list representing the Graph
};


// define constructor of Graph Class to create an empty graph
Graph::Graph()
{
  numV = 0;
  numE = 0;
  adjList.clear();
}

// define constructor of Graph Class to initialize number of nodes 
Graph::Graph(int numVert, int initVal = INFINIT)
{
  numV = numVert;  // create nodes and link it to default names (0..51 -> A..Za..z)
  numE = 0;
  nodeNames.resize(numVert);

  for (int x=0; x<numV; ++x)
  {  
    nodeNames[x] = convIntToChar(x);
    nodeNumbers[convIntToChar(x)]=x;
  }
  
  // create adjacency list with all nodes and empty edge list
  adjList.clear();
  for(int i=0; i<numVert; ++i)
  {
    Node newNode;
    newNode.number = i;
    newNode.weight = 0;
    newNode.edges.clear();
    adjList.push_back(newNode);
  }
}

// define the function to return node name linked to node number x
char Graph::get_node_value(int x)
{
  return nodeNames[x];
}

// change node name (from 'x' to 'name')
void Graph::set_node_value(char x, char name)
{
  int posX = nodeNumbers[x];	           // get the number of node 'x'
  nodeNames[posX] = name;	               // link node number to 'name'
  nodeNumbers[name]=posX;	               // link 'name' to node number
}

// return edge weight between 'x' and 'y' and return INFINITY if edge doesn't exist
int Graph::get_edge_value(char x, char y)
{
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==nodeNumbers[x])
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
	 if ((*j).number==nodeNumbers[y])
	   return (*j).weight; 
      }
  }
  return INFINIT;
}

// set edge weight between 'x' and 'y'
void Graph::set_edge_value(char x, char y, int value)
{
  bool found;

  // add 'y' in the list of 'x' neighbors (if doesn't exist) and set edge weight to value
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==nodeNumbers[x])
    {
      found = false;
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
	 if ((*j).number==nodeNumbers[y])
	 {  
	   (*j).weight=value;
	   found = true;
	 }
      }
      if (!found)
      {
        Node newNodeY;
	      newNodeY.number = nodeNumbers[y];
	      newNodeY.weight = value;
	      newNodeY.edges.clear();
	      (*i).edges.push_back(newNodeY);
      }
    }
  }
  
  // add 'x' in the list of 'y' neighbors (if doesn't exist) and set edge weight to value
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==nodeNumbers[y])
    {
      found = false;
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
	 if ((*j).number==nodeNumbers[x])
	 {  
	   (*j).weight=value;
	   found = true;
	 }
      }
      if (!found)
      { 
        Node newNodeX;
	      newNodeX.number = nodeNumbers[x];
	      newNodeX.weight = value;
	      newNodeX.edges.clear();
	      (*i).edges.push_back(newNodeX);
	      ++numE;	  	
      }
    }
  }
}

// return true if 'x' and 'y' are neighbors and false otherwise
bool Graph::adjacent(char x, char y)
{
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==nodeNumbers[x])
    {
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
	if ((*j).number==nodeNumbers[y])
	{  
	  return true;
	}
      }
    }
  }
  return false;
}

// return a list<char> containing the list of neighbors of 'x'
list<char> Graph::neighbors(char x)
{
  list<char> adjNodes;
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==nodeNumbers[x])
    {
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
	adjNodes.push_back(nodeNames[(*j).number]);
      }
    }
  }
  return adjNodes;
}
   
// return the number of nodes in the Graph
int Graph::V()
{
  return numV;
}

// return the number of edges in the Graph
int Graph::E()
{
  return numE;
}

// return a list<char> containing all nodes in the Graph
list<char> Graph::vertices()
{
  list<char> nodes;
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    nodes.push_back(nodeNames[(*i).number]);
  }
  return nodes;
}

// print out adjacency list representing the Graph
void Graph::show()
{
  cout << "  ";
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
    cout << " " << nodeNames[(*i).number];
  cout << endl;
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    cout << " " << nodeNames[(*i).number];
    int shift=0;
    for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
    {
      int walk=(*j).number-shift;
      for(int k=0; k<walk; ++k)
      {
	cout << " -";
	shift++;
      }
      cout << " " << (*j).weight;
      shift++;
    }
    while (shift<numV)
    {
      cout << " -";
      shift++;
    }
    cout << endl;
  }
}


/*
  -------------------------------------------------------------------------------------------
   Define NodeInfo to store information about nodes, paths and min dists in priority queue
  -------------------------------------------------------------------------------------------
*/
struct strNodeInfo
{
  char nodeName;	// node name
  int minDist;		// shortest path found to nodeName
  char through;		// node that precede nodeName in the shortest path
};

typedef struct strNodeInfo NodeInfo;

// compare NodeInfo by nodeName
bool compareNodeName(NodeInfo& n1, NodeInfo& n2)
{
  if (n1.nodeName < n2.nodeName) 
    return true;

  return false;
}

// compare NodeInfo by minDist
bool compareMinDist(NodeInfo& n1, NodeInfo& n2)
{
  if (n1.minDist < n2.minDist) 
    return true;

  return false;
}

// return true if two NodeInfo have the same nodeName and false otherwise
bool operator== (NodeInfo& n1, NodeInfo& n2)
{
  if (n1.nodeName == n2.nodeName) 
    return true;

  return false;
}


/*
  ------------------------------------------------------------------------------
      Define PriorityQueue Class to stores known information about node names, 
                                                 min distances and paths
      Ordered by min distances
  ------------------------------------------------------------------------------
*/

class PriorityQueue {
  public:
    PriorityQueue();
    void chgPriority(NodeInfo n);
    void minPriority();
    bool contains(NodeInfo n);
    bool isBetter(NodeInfo n);
    void insert(NodeInfo n);
    NodeInfo top();
    int size();
    
  private:
    list<NodeInfo> pq;		// List of known nodes/paths ordered by minDist
};

// define constructor of PriorityQueue Class and create an empty list of nodes
PriorityQueue::PriorityQueue()
{
  pq.clear();
}

// change information ('minDist' and 'through') of a node named 'n' in priority queue
void PriorityQueue::chgPriority(NodeInfo n)
{
  for(list<NodeInfo>::iterator i=pq.begin(); i!=pq.end(); ++i)
    if ((*i) == n)
    {
      (*i).minDist = n.minDist;
      (*i).through = n.through;
    }
  pq.sort(compareMinDist);
}

// remove the node with lower minDist from priority queue 
void PriorityQueue::minPriority()
{
  if (! pq.empty())
  {
    pq.pop_front();
  }
}

// return true if there is a node named 'n' in priority queue and false otherwise 
bool PriorityQueue::contains(NodeInfo n)
{
  for(list<NodeInfo>::iterator i=pq.begin(); i!=pq.end(); ++i)
    if ((*i).nodeName == n.nodeName)
      return true;
  return false;
}

// return true if node 'n' has a lower minDist than the node with the same name in the priority queue and false otherwise
bool PriorityQueue::isBetter(NodeInfo n)
{
  for(list<NodeInfo>::iterator i=pq.begin(); i!=pq.end(); ++i)
    if ((*i).nodeName == n.nodeName)
      if ((*i).minDist > n.minDist)
	return true;
  return false;
}

// insert node 'n' into priority queue
void PriorityQueue::insert(NodeInfo n)
{
  pq.push_back(n);
  pq.sort(compareMinDist);
}

// return the node with lower minDist in priority queue (without removing it from the queue))
NodeInfo PriorityQueue::top()
{
  NodeInfo n = {' ',0};
  if (! pq.empty())
  {
    list<NodeInfo>::iterator i=pq.begin();
    n.nodeName = (*i).nodeName;
    n.minDist = (*i).minDist;
    n.through = (*i).through;
  }
  return n;
}

// return the number of elements in the priority queue
int PriorityQueue::size()
{
  return pq.size();
}



/*
  ----------------------------------------------------------------------------
   Define ShortestPath Class 
   Implements Dijkstra's Algorithm to find shortest paths between two nodes
  ----------------------------------------------------------------------------
*/

class ShortestPath
{
  public:
    ShortestPath();
    ShortestPath(Graph g);
    list<char> path(char u, char w);
    int path_size(char u, char w);
  
  private:
    Graph graph;		// Graph used by Diajkstra's Algorithm
};

// define constructor of ShortestPath Class (do nothing)
ShortestPath::ShortestPath()
{
}

// define constructor of ShortestPath Class that stores Graph used by Dijkstra's Algorithm 
ShortestPath::ShortestPath(Graph g)
{
  graph = g;
}

// return a list<char> containing the list of nodes in the shortest path between 'u' and 'w'
list<char> ShortestPath::path(char u, char w)
{
  // initialize candidates list with all nodes
  list<char> candidates = graph.vertices(), desiredPath;
  list<NodeInfo> minPaths;
  PriorityQueue p;
  NodeInfo lastSelected, n;
     
  // calculate shortest path from 'u' to 'w' (Dijkstra's Algorithm)
  candidates.remove(u);			    // remove 'u' from candidates list
  lastSelected.nodeName = u;		// set 'u' as lastSelected
  lastSelected.minDist = 0;
  lastSelected.through = u;

  minPaths.push_back(lastSelected);	   // add 'u' to minPath list
  while ((!candidates.empty()) && (lastSelected.nodeName !=w))
  {
    // For each node in candidate list calculate the cost to reach that candidate through lastSelected 
    for(list<char>::iterator i=candidates.begin(); i != candidates.end(); ++i)
    {
      n.nodeName=*i;
      n.minDist=lastSelected.minDist+graph.get_edge_value(lastSelected.nodeName,*i);
      n.through=lastSelected.nodeName;
      if (!p.contains(n))	              // add candidate to priority queue if doesn't exist 
          p.insert(n);
      else
          if (p.isBetter(n))	          // update candidate minDist in priority queue if a better path was found
	           p.chgPriority(n);
    }
    lastSelected = p.top();			       // select the candidate with minDist from priority queue
    p.minPriority();				           // remove it from the priority queue
    minPaths.push_back(lastSelected);		// add the candidate with min distance to minPath list
    candidates.remove(lastSelected.nodeName);	// remove it from candidates list
  }
  
  // go backward from 'w' to 'u' adding nodes in that path to desiredPath list
  lastSelected=minPaths.back();
  desiredPath.push_front(lastSelected.nodeName);
  while(lastSelected.nodeName!=u)
  {
    for(list<NodeInfo>::iterator i=minPaths.begin(); i != minPaths.end(); ++i)
      if ((*i).nodeName==lastSelected.through)
      {
	lastSelected=(*i);
	desiredPath.push_front(lastSelected.nodeName);
      }
  }
  return desiredPath;
}

// return the size of the shortest path between 'u' and 'w'
int ShortestPath::path_size(char u, char w)
{
  int pathCost=0;
  list<char> sp;
  char current,next;
  
  // calculate the shortest path from 'u' to 'w' and then sum up edge weights in this path
  sp = path(u,w);
  current=sp.front();
  sp.pop_front();
  for(list<char>::iterator i=sp.begin(); i!=sp.end(); ++i)
  {
    next = (*i);
    pathCost += graph.get_edge_value(current,next);
    current = next;
  }
  return pathCost; 
}


/*
  -----------------------------------------------------------------
     Monte Carlo Class
     Used to generate random graphs and run simulations
  -----------------------------------------------------------------
*/

class MonteCarlo
{
  public:
    MonteCarlo();    // constructor
    Graph randomGraph(int vert, 
                      double density,
                      int minDistEdge,
                      int maxDistEdge);
    void run(Graph g);

};

// Define constructor of MonteCarlo Class to initializes the seed of random number generator
MonteCarlo::MonteCarlo()
{
  srand(time(NULL));
}

// Define the function 'randomGraph' that returns a random Graph
Graph MonteCarlo::randomGraph(int numVert,
                              double density,
                              int minDistEdge,
                              int maxDistEdge)
{
  int randDistEdge;
  char srcVert, dstVert;
  
  Graph g(numVert);

  for (int i=0; i<g.V(); ++i)
    for (int j=i+1; j<g.V(); ++j)
    {
      double p = ((static_cast<double>(rand())) / RAND_MAX);	// Generate random probability
      if (p < density)	                                      
      {
        randDistEdge = rand() % (maxDistEdge - minDistEdge) + minDistEdge; // Generate random edge weight 
	      srcVert = convIntToChar(i);
	      dstVert = convIntToChar(j);
	      g.set_edge_value(srcVert,dstVert,randDistEdge);
      }
    }
  
  return g;
}

// run a simulation finding the shortest paths in a given graph 
void MonteCarlo::run(Graph g)
{
  static int turn=0;
  
  cout << endl << "=== RUNNING SIMULATION No. " << ++turn << " ===" << endl;
  
  // Print out graph information
  double d = static_cast<double>(g.E())/((static_cast<double>(g.V())*static_cast<double>(g.V())-1)/2)*100;	// Calculate real density reached
  cout << "Vertices: " << g.V() << endl;
  cout << "Edges: " << g.E() << " (density: " << d << "%)" << endl;
  cout << "Graph: " << endl;
  g.show();

  // Print out shortest path information
  list<char> v = g.vertices();
  cout << endl << "Vertices: " << v << endl; 
  int reachVert=0, sumPathSize=0, avgPathSize=0;
  ShortestPath sp(g);
  for (list<char>::iterator i=++v.begin(); i != v.end(); ++i) 
  {
    char src = v.front();
    char dst = (*i);
    list<char> p = sp.path(src,dst);
    int ps = sp.path_size(src,dst);
    if (ps != INFINIT)
      cout << "ShortestPath (" << src << " to " << dst << "): " 
           << ps 
           << " -> " 
           << p 
           << endl;
    else
      cout << "ShortestPath (" << src << " to " << dst << "): " 
           << "** UNREACHABLE **" << endl;      
    if (ps!=INFINIT)
    {
      reachVert++;		// sum up reached nodes 
      sumPathSize += ps;	// sum up shortest paths found
    }
  }  
  
  // get average shortest path and print it out
  if (reachVert!=0)
    avgPathSize = sumPathSize / reachVert;	
  else
    avgPathSize = 0;
  cout << endl << "AVG ShortestPath Size (reachVert: " 
       << reachVert << " - sumPathSize: " 
       << sumPathSize << "): " << avgPathSize << endl;
}



/*
  ----------------------------------------------------
             Main Function
  ----------------------------------------------------
*/

int main()
{
  MonteCarlo simulation;
  Graph g;
  
  // create a graph with 50 nodes and density 20%
  g = simulation.randomGraph(50,0.2,1,10);
  simulation.run(g);

  // create a graph with 50 nodes and density 40% 
  g = simulation.randomGraph(50,0.4,1,10);
  simulation.run(g);
  
  return 0;  
}