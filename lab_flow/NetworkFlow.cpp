/**
* @file NetworkFlow.cpp
* CS 225: Data Structures
*/

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
  return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  for (Vertex v: g_.getVertices()) {
    flow_.insertVertex(v);
    residual_.insertVertex(v);
  }

  for (Vertex v: g_.getVertices()) {
      for (Vertex adj_v: g_.getAdjacent(v)) {
        flow_.insertEdge(v, adj_v);
        flow_.setEdgeWeight(v, adj_v, 0);
        residual_.insertEdge(v, adj_v);
        residual_.setEdgeWeight(v, adj_v, g_.getEdge(v, adj_v).getWeight());
        residual_.insertEdge(adj_v, v);
        residual_.setEdgeWeight(adj_v, v, 0);
      }
    }
    // add back edges to residual and set their weights to 0

  maxFlow_ = 0;
}

/**
* findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
*  This version is the helper function.
*
* @param source  The starting (current) vertex
* @param sink    The destination vertex
* @param path    The vertices in the path
* @param visited A set of vertices we have visited
*/

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

    if (visited.count(source) != 0)
    return false;
    visited.insert(source);

    if (source == sink) {
      return true;
    }

    vector<Vertex> adjs = residual_.getAdjacent(source);
    for(auto it = adjs.begin(); it != adjs.end(); it++) {
      if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
        path.push_back(*it);
        if (findAugmentingPath(*it,sink,path,visited))
        return true;
        else {
          path.pop_back();
        }
      }
    }

    return false;
  }

  /**
  * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
  *  This version is the main function.  It initializes a set to keep track of visited vertices.
  *
  * @param source The starting (current) vertex
  * @param sink   The destination vertex
  * @param path   The vertices in the path
  */

  bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
    std::set<Vertex> visited;
    path.clear();
    path.push_back(source);
    return findAugmentingPath(source,sink,path,visited);
  }

  /**
  * pathCapacity - Determine the capacity of a path in the residual graph.
  *
  * @param path   The vertices in the path
  */

  int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
    // YOUR CODE HERE
    int minimum = residual_.getEdgeWeight(path[0],path[1]);
  for (int i =1; i < (int) path.size()-1;i++) {
    if(residual_.getEdgeWeight(path[i], path[i+1]) <minimum) {
      minimum = residual_.getEdgeWeight(path[i], path[i+1]);
    }
  }
  return minimum;
  }

  /**
  * calculuateFlow - Determine the capacity of a path in the residual graph.
  * Sets the member function `maxFlow_` to be the flow, and updates the
  * residual graph and flow graph according to the algorithm.
  *
  * @return The network flow graph.
  */

  const Graph & NetworkFlow::calculateFlow() {
    // YOUR CODE HERE
    vector<Vertex> p;
    while(findAugmentingPath(source_, sink_, p)) {
      int min = pathCapacity(p);
      maxFlow_ += min;
      for (unsigned i = 0; i < p.size()-1; i++) {
        int first = residual_.getEdgeWeight(p[i],p[i+1]);
        int first_reverse = residual_.getEdgeWeight(p[i+1],p[i]);
        residual_.setEdgeWeight(p[i],p[i+1], first - min);
        residual_.setEdgeWeight(p[i+1],p[i], first_reverse+ min);
      }
    }

    return flow_;
  }

  int NetworkFlow::getMaxFlow() const {
    return maxFlow_;
  }

  const Graph & NetworkFlow::getGraph() const {
    return g_;
  }

  const Graph & NetworkFlow::getFlowGraph() const {
    return flow_;
  }

  const Graph & NetworkFlow::getResidualGraph() const {
    return residual_;
  }
